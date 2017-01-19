#include <iostream>
#include <cstdlib>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <time.h>
#include "TimeMeter.hh"
#include "Philo.hpp"
#include "fork.hpp"

using namespace std ;

#define N_PHILOSOPHES 5
#define LEFT_FORK(N)  (N)
#define RIGHT_FORK(N) (((N)+1) % N_PHILOSOPHES )

std::mutex                  mutex_var ;
std::condition_variable     cond_var ;

Philosopher*    Philosopher[N_PHILOSOPHES]{nullptr};
Fork*           forchetta[] {nullptr};

void philosopher( int n )
{
    {
        //barrier for wait a go signal
        std::unique_lock<std::mutex> lock(mutex_var) ;
        cout << "Philosopher "<<Philosopher[n]->getNumber(n)<< " is waiting to start\n" ;
        cond_var.wait(lock);
        cout << "Philosopher "<< Philosopher[n]->getNumber(n) << " is started\n" ;
    }
    
    while ( true ) { //infinity loop
        //thinking
        Philosopher[n]->thinking();
        cout << "Philosopher " << Philosopher[n]->getNumber(n) << " is THINKING\n" ;
        std::chrono::milliseconds duration(500);
        std::this_thread::sleep_for(duration);
        
        // enter in the critical section
        mutex_var.lock();
        // possible deadlock
        Philosopher[n]->SetLeftFork(forchetta[LEFT_FORK(n)]);
        cout << "Philosopher " << Philosopher[n]->getNumber(n) << " acquired the left fork!\n" ;
        if (forchetta[RIGHT_FORK(n)]->getStateFork() == FREE)
        {
            Philosopher[n]->SetRightFork(forchetta[RIGHT_FORK(n)]);
            cout << "Philosopher " << Philosopher[n]->getNumber(n) << " acquired the right fork!\n" ;
            Philosopher[n]->setCanEat(forchetta[LEFT_FORK(n)], forchetta[RIGHT_FORK(n)]);
        }
        else
        {
            cout << "Philosopher " << Philosopher[n]->getNumber(n) << " waiting for the right fork!\n" ;
            Philosopher[n]->ReleaseLeftFork(forchetta[RIGHT_FORK(n)]);
        }
        
        // eating
        if(Philosopher[n]->getCanEat())
        {
            Philosopher[n]->eating();
            cout << "Philosopher " << Philosopher[n]->getNumber(n) << " is EATING\n" ;
            std::chrono::milliseconds duration1( 1000 );
            std::this_thread::sleep_for( duration1 );
            // enter in the critical section
            Philosopher[n]->ReleaseLeftFork(forchetta[LEFT_FORK(n)]);
            cout << "Philosopher " << n << " drop the right fork!\n" ;
            Philosopher[n]->ReleaseRightFork(forchetta[RIGHT_FORK(n)]);
            cout << "Philosopher " << n << " drop the left fork!\n" ;
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
        cout << endl;
        cout << "Time Eat:      ";
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
    for(long i = 0 ; i < N_PHILOSOPHES ; ++i )
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
