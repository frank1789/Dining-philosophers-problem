//
//  Philo.hpp
//  thread-filosofi
//
//  Created by Francesco Argentieri on 07/08/16.
//  Copyright © 2016 Francesco Argentieri. All rights reserved.
//

#ifndef Philo_hpp
#define Philo_hpp

#include <stdio.h>
#include <iostream>
#include "fork.hpp"

enum Philosopher_STATE {THINK, EAT, SLEEP};

class Philosopher
{
private:
    int _number_philosopher;
    int _num_eat;
    int _num_sleep;
    int _num_think;
    bool _allFork;
    Philosopher_STATE _state_philosopher;
    
public:
    Philosopher();
    //Philosopher activity
    void thinking();
    void eating();
    void sleeping();
    Philosopher_STATE GetPhilosopherState();
    int getEat() {return _num_eat;};
    int getSleep() {return _num_sleep;};
    int getThink() {return _num_think;};
    void setCanEat(Fork *forkSX, Fork *forkDX);
    bool getCanEat();
    //fork interaction
    void SetLeftFork(Fork *fork);
    void SetRightFork(Fork *fork);
    void ReleaseLeftFork(Fork *fork);
    void ReleaseRightFork(Fork *fork);
    int  getNumber(int p_n);
};

#endif /* Philo_hpp */
