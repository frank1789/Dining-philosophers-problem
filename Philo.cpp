//
//  Philo.cpp
//  thread-filosofi
//
//  Created by Francesco Argentieri on 07/08/16.
//  Copyright © 2016 Francesco Argentieri. All rights reserved.
//

#include "Philo.hpp"
#include "fork.hpp"

Philosopher::Philosopher()
{
    _state_philosopher = SLEEP;
    _num_think = 0;
    _num_sleep = 0;
    _num_eat   = 0;
    _allFork   = false;
}

void Philosopher::thinking()
{
    //change status of philosophe
    _state_philosopher = THINK;
    //update the action
    _num_think++;
}

void Philosopher::eating()
{
    //change status of philosophe
    _state_philosopher = EAT;
    //update the action
    _num_eat++;
}

void Philosopher::sleeping()
{
    //change status of philosophe
    _state_philosopher = SLEEP;
    //update the action
    _num_sleep++;
}

Philosopher_STATE Philosopher::GetPhilosopherState() {return _state_philosopher;}

int Philosopher::getNumber(int p_n) {return p_n;}

void Philosopher::SetLeftFork(Fork *fork)
{
    fork->setForkState();
}
void Philosopher::SetRightFork(Fork *fork)
{
    fork->setForkState();
}
void Philosopher::ReleaseLeftFork(Fork *fork)
{
    fork->relaseFork();
}
void Philosopher::ReleaseRightFork(Fork *fork)
{
    fork->relaseFork();
}

void Philosopher::setCanEat(Fork *forkSX, Fork *forkDX)
{
    if(forkSX->getStateFork() == INUSE && forkDX->getStateFork() == INUSE) _allFork = true;
    else _allFork = false;
}

bool Philosopher::getCanEat() {return _allFork;}

