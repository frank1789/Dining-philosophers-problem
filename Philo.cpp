//
//  Philo.cpp
//  thread-filosofi
//
//  Created by Francesco Argentieri on 07/08/16.
//  Copyright © 2016 Francesco Argentieri. All rights reserved.
//

#include "Philo.hpp"
#include "fork.hpp"

Philosopher::Philosopher() : m_num_think(0), m_num_sleep(0), m_num_eat(0) {
  m_state = action::SLEEP;
  m_allFork = false;
}

void Philosopher::thinking() {
  // change status of philosophe
  m_state = action::THINK;
  // update the action
  m_num_think++;
}

void Philosopher::eating() {
  // change status of philosophe
  m_state = action::EAT;
  // update the action
  m_num_eat++;
}

void Philosopher::sleeping() {
  // change status of philosophe
  m_state = action::SLEEP;
  // update the action
  m_num_sleep++;
}

action Philosopher::GetPhilosopherState() { return m_state; }

int Philosopher::getNumber(int num) { return num; }

void Philosopher::SetLeftFork(Fork *fork) { fork->acquireFork(); }

void Philosopher::SetRightFork(Fork *fork) { fork->acquireFork(); }

void Philosopher::ReleaseLeftFork(Fork *fork) { fork->relaseFork(); }

void Philosopher::ReleaseRightFork(Fork *fork) { fork->relaseFork(); }

void Philosopher::setCanEat(Fork *forkSX, Fork *forkDX) {
  if (forkSX->getStateFork() == forkstate::INUSE &&
      forkDX->getStateFork() == forkstate::INUSE)
    m_allFork = true;
  else
    m_allFork = false;
}

bool Philosopher::getCanEat() { return m_allFork; }

unsigned int Philosopher::getEat() { return m_num_eat; }

unsigned int Philosopher::getSleep() { return m_num_sleep; }

unsigned int Philosopher::getThink() { return m_num_think; }
