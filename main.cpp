#include <time.h>

#include <condition_variable>
#include <cstdlib>
#include <iostream>
#include <mutex>
#include <thread>
//#include "TimeMeter.hh"
#include <memory>

#include "Philo.hpp"
#include "fork.hpp"

using namespace std;

std::mutex mutex_var;
std::condition_variable cond_var;

constexpr unsigned int N_PHILOSOPHES = 5;
auto LEFT_FORK = [](unsigned int N) { return N; };
auto RIGHT_FORK = [](unsigned int N) { return ((N + 1) % N_PHILOSOPHES); };

auto print_status = [](const unsigned int& n, const std::string& message) {
  std::cout << "Philosopher " << n << " " << message << "\n";
};

void philosopher(unsigned int n, Philosopher* Philosopher, Fork* forchetta) {
  {
    // barrier for wait a go signal
    std::unique_lock<std::mutex> lock(mutex_var);
    print_status(n, "is waiting to start");
    cond_var.wait(lock);
    print_status(n, "is started");
  }

  while (true) {  // infinity loop
    // thinking
    Philosopher[n].thinking();
    print_status(n, "is THINKING");
    std::chrono::milliseconds duration(500);
    std::this_thread::sleep_for(duration);

    // enter in the critical section
    mutex_var.lock();
    // possible deadlock
    Philosopher[n].SetLeftFork(&forchetta[LEFT_FORK(n)]);
    print_status(n, "acquired the left fork!");
    if (forchetta[LEFT_FORK(n)].getStateFork() == forkstate::INUSE) {
      Philosopher[n].SetRightFork(&forchetta[RIGHT_FORK(n)]);
      print_status(n, "acquired the right fork!");
      Philosopher[n].setCanEat(&forchetta[LEFT_FORK(n)],
                               &forchetta[RIGHT_FORK(n)]);
      if (Philosopher[n].getCanEat() == false) {
        print_status(n, " waiting for the right fork!\n");
        Philosopher[n].ReleaseLeftFork(&forchetta[LEFT_FORK(n)]);
        Philosopher[n].ReleaseRightFork(&forchetta[RIGHT_FORK(n)]);
        print_status(n, " then release fork!\n");
      }
    }

    // eating
    if (Philosopher[n].getCanEat()) {
      Philosopher[n].eating();
      print_status(n, "is EATING");
      std::chrono::milliseconds duration1(1000);
      std::this_thread::sleep_for(duration1);
      // enter in the critical section
      Philosopher[n].ReleaseLeftFork(&forchetta[LEFT_FORK(n)]);
      print_status(n, "drop the right fork!");
      Philosopher[n].ReleaseRightFork(&forchetta[RIGHT_FORK(n)]);
      print_status(n, "drop the left fork!");
    }
    mutex_var.unlock();  // exit from the critical section

    // sleeping
    Philosopher[n].sleeping();
    print_status(n, "is SLEEPING\n");
    std::chrono::milliseconds duration2(1500);
    std::this_thread::sleep_for(duration2);
  }
}

void monitor(Philosopher* Philosopher, Fork* forchetta) {
  while (true) { /* ciclo infinito */
    std::chrono::milliseconds duration(1000);
    std::this_thread::sleep_for(duration);
    // enter in the critical section
    cout << "\nPhilosophes:  ";
    for (unsigned int i = 0; i < N_PHILOSOPHES; ++i) {
      switch (Philosopher[i].GetPhilosopherState()) {
        case action::THINK:
          cout << " T";
          break;  // think
        case action::EAT:
          cout << " E";
          break;  // eat
        case action::SLEEP:
          cout << " S";
          break;  // sleep
        default:
          throw "Error";
      }
    }
    std::cout << "\nForks:        ";
    for (unsigned int i = 0; i < N_PHILOSOPHES; ++i) {
      switch (forchetta[i].getStateFork()) {
        case forkstate::FREE:
          cout << " F";
          break;
        case forkstate::INUSE:
          cout << " U";
          break;
        default:
          throw "Error";
      }
    }

    // Print the number philosophes eat
    std::cout << "\nTime Eat:      ";
    for (unsigned int i = 0; i < N_PHILOSOPHES; ++i) {
      std::cout << Philosopher[i].getEat() << " ";
    }
    // Print the number philosophes sleep
    std::cout << endl;
    std::cout << "Time Sleep:    ";
    for (unsigned int i = 0; i < N_PHILOSOPHES; ++i) {
      std::cout << Philosopher[i].getSleep() << " ";
    }
    // Print the number philosophes think
    std::cout << std::endl;
    std::cout << "Time Think:    ";
    for (unsigned int i = 0; i < N_PHILOSOPHES; ++i) {
      std::cout << Philosopher[i].getThink() << " ";
    }
    std::cout << std::endl << std::endl;
  }
}

int main() {
  //  Philosopher* Philosopher[N_PHILOSOPHES]{nullptr};
  //  Fork* forchetta[N_PHILOSOPHES]{nullptr};
  auto phil = std::make_unique<Philosopher[]>(N_PHILOSOPHES);
  auto forchetta = std::make_unique<Fork[]>(N_PHILOSOPHES);

  //  for (unsigned int i = 0; i < N_PHILOSOPHES; i++) {
  //    forchetta[i] = new class Fork();
  //    Philosopher[i] = new class Philosopher();
  //  }

  // create threads for philosophes
  for (unsigned int i = 0; i < N_PHILOSOPHES; ++i) {
    cout << "Create the philosopher " << i << "\n";
    std::thread(philosopher, i, phil.get(), forchetta.get()).detach();
    std::chrono::milliseconds duration(1000);
    std::this_thread::sleep_for(duration);
  }

  // create threads for monitor
  std::thread(monitor, phil.get(), forchetta.get()).detach();
  std::chrono::seconds duration(10);
  std::this_thread::sleep_for(duration);

  // start philosopher
  cond_var.notify_all();

  std::chrono::seconds duration1(60);
  std::this_thread::sleep_for(duration1);

  // erase the dynamic memory
  //  for (unsigned int i = 0; i < N_PHILOSOPHES; ++i) {
  //    delete forchetta[i];
  //    delete Philosopher[i];
  //  }

  return 0;
}
