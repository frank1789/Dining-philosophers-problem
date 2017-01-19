//
//  fork.cpp
//  thread-filosofi
//
//  Created by Francesco Argentieri on 24/08/16.
//  Copyright © 2016 Francesco Argentieri. All rights reserved.
//

#include "fork.hpp"

Fork::Fork(int p_fork)
{
    _fork = p_fork;
    _forkState = FREE;
}

void Fork::setForkState()
{
    _forkState = INUSE;
}

void Fork::relaseFork()
{
    _forkState = FREE;
}
