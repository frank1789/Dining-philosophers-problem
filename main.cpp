#include <iostream>
#include <cstdlib>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <time.h>
#include "TimeMeter.hh"
#include "Philo.hpp"
#include "fork.hpp"

std::mutex mutex_var;
std::condition_variable cond_var;

constexpr unsigned int N_PHILOSOPHES = 5;
constexpr unsigned int LEFT_FORK(unsigned int N) { return N; }
constexpr unsigned int RIGHT_FORK(unsigned int N) {
  return ((N + 1) % N_PHILOSOPHES);
}

auto print_status = [](const unsigned int &n, const std::string &message) {
std::condition_variable     cond_var ;

Philosopher*    Philosopher[N_PHILOSOPHES]{nullptr};
Fork*           forchetta[] {nullptr};

void philosopher( int n )
{
    {
        //barrier for wait a go signal
    print_status(n, "is waiting to start");
        cout << "Philosopher "<<Philosopher[n]->getNumber(n)<< " is waiting to start\n" ;
        cond_var.wait(lock);
    print_status(n, "is started");
    }
    
    while ( true ) { //infinity loop
        //thinking
        Philosopher[n]->thinking();
    print_status(n, "is THINKING");
        std::chrono::milliseconds duration(500);
        std::this_thread::sleep_for(duration);
        
        // enter in the critical section
        mutex_var.lock();
        // possible deadlock
        Philosopher[n]->SetLeftFork(forchetta[LEFT_FORK(n)]);
    print_status(n, "acquired the left fork!");
        if (forchetta[RIGHT_FORK(n)]->getStateFork() == FREE)
        {
      print_status(n, "acquired the right fork!");
            cout << "Philosopher " << Philosopher[n]->getNumber(n) << " acquired the right fork!\n" ;
            Philosopher[n]->setCanEat(forchetta[LEFT_FORK(n)], forchetta[RIGHT_FORK(n)]);
      print_status(n, "waiting for the right fork!");
        else
        {
            cout << "Philosopher " << Philosopher[n]->getNumber(n) << " waiting for the right fork!\n" ;
            Philosopher[n]->ReleaseLeftFork(forchetta[RIGHT_FORK(n)]);
        }
        
        // eating
        if(Philosopher[n]->getCanEat())
        {
      print_status(n, "is Eating");
            cout << "Philosopher " << Philosopher[n]->getNumber(n) << " is EATING\n" ;
            std::chrono::milliseconds duration1( 1000 );
            std::this_thread::sleep_for( duration1 );
            // enter in the critical section
            Philosopher[n]->ReleaseLeftFork(forchetta[LEFT_FORK(n)]);
      print_status(n, "drop the right fork!");
            Philosopher[n]->ReleaseRightFork(forchetta[RIGHT_FORK(n)]);
      print_status(n, "drop the left fork!");
            mutex_var.unlock() ; // exit from the critical section
        }
    
        // sleeping
        Philosopher[n]->sleeping();
        cout << "Philosopher " <<Philosopher[n]->getNumber(n) << " is SLEEPING\n" ;
        std::chrono::milliseconds duration2( 1500 );
        std::this_thread::sleep_for( duration2 );
    }
}

void monitor()
{
    while (true) { /* ciclo infinito */
        std::chrono::milliseconds duration(1000);
        std::this_thread::sleep_for(duration);
        // enter in the critical section
        cout << "\nPhilosophes:  ";
        for (int i = 0; i < N_PHILOSOPHES; ++i) {
            switch (Philosopher[i]->GetPhilosopherState()) {
                case THINK:  cout << " T"; break; // think
                case EAT:    cout << " E"; break; // eat
                case SLEEP:  cout << " S"; break; // sleep
            }
        }
        cout << "\nForks:        ";
        for (int i = 0; i < N_PHILOSOPHES; ++i) {
            switch (forchetta[i]->getStateFork()) {
                case FREE:  cout << " F"; break;
                case INUSE: cout << " U"; break;
            }
        }
        
        //Print the number philosophes eat
  std::vector<Philosopher> vec_philosopher(N_PHILOSOPHES, Philosopher());
  std::vector<Fork> vec_fork (N_PHILOSOPHES - 1, Fork());
        for (int i = 0; i < N_PHILOSOPHES; ++i) {
            cout << Philosopher[i]->getEat() << " ";
        }
        //Print the number philosophes sleep
        cout << endl;
        cout << "Time Sleep:    ";
        for (int i = 0; i < N_PHILOSOPHES; ++i) {
            cout << Philosopher[i]->getSleep() << " ";
        }
        //Print the number philosophes think
        cout << endl;
        cout << "Time Think:    ";
        for (int i = 0; i < N_PHILOSOPHES; ++i) {
            cout << Philosopher[i]->getThink() << " ";
        }
        cout << endl << endl;
    }
}

int main( int argc, char *argv[] )
{
    for(int i; i < N_PHILOSOPHES; i++)
    {
        forchetta[i] = new class Fork(i);
        Philosopher[i] = new class Philosopher();
    }

    // create threads for philosophes
  for (unsigned int i = 0; i < N_PHILOSOPHES; ++i) {
    {
        cout << "Create the philosopher " << i << "\n" ;
        std::thread(philosopher, i).detach() ;
        std::chrono::milliseconds duration(1000);
        std::this_thread::sleep_for(duration);
    }
    
    // create threads for monitor
    std::thread(monitor).detach() ;
    std::chrono::seconds duration(10);
    std::this_thread::sleep_for(duration);
    
    // start philosopher
    cond_var.notify_all();
    
    std::chrono::seconds duration1( 60 );
    std::this_thread::sleep_for(duration1);
  
    //erase the diynamic memory
    for(int i; i < N_PHILOSOPHES; i++)
    {
        delete forchetta[i] ;
        delete Philosopher[i] ;
    }
    
    return 0 ;
}
