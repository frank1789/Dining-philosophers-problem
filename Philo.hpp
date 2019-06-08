//
//  Philo.hpp
//  thread-filosofi
//
//  Created by Francesco Argentieri on 07/08/16.
//  Copyright © 2016 Francesco Argentieri. All rights reserved.
//

#ifndef PHILOSOPHER_HPP
#define PHILOSOPHER_HPP

#include "fork.hpp"

enum class action {THINK, EAT, SLEEP};

class Philosopher
{
public:
    Philosopher();
    //Philosopher activity
    void thinking();
    void eating();
    void sleeping();
    action GetPhilosopherState();
    unsigned int getEat();
    unsigned int getSleep();
    unsigned int getThink();
    void setCanEat(Fork *forkSX, Fork *forkDX);
    bool getCanEat();
    //fork interaction
    void SetLeftFork(Fork *fork);
    void SetRightFork(Fork *fork);
    void ReleaseLeftFork(Fork *fork);
    void ReleaseRightFork(Fork *fork);
    int  getNumber(int num);
    private:
    unsigned int m_num_eat;
    unsigned int m_num_sleep;
    unsigned int m_num_think;
    bool m_allFork;
    action m_state;
};

#endif // PHILOSOPHER_HPP
