//
//  fork.cpp
//  thread-filosofi
//
//  Created by Francesco Argentieri on 24/08/16.
//  Copyright © 2016 Francesco Argentieri. All rights reserved.
//

#include "fork.hpp"

Fork::Fork(unsigned int numfork) {
  m_fork = numfork;
  m_state = forkstate::FREE;
}

void Fork::acquireFork() { m_state = forkstate::INUSE; }

void Fork::relaseFork() { m_state = forkstate::FREE; }

forkstate Fork::getStateFork() { return m_state; }
