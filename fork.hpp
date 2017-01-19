//
//  fork.hpp
//  thread-filosofi
//
//  Created by Francesco Argentieri on 24/08/16.
//  Copyright © 2016 Francesco Argentieri. All rights reserved.
//

#ifndef fork_hpp
#define fork_hpp

#include <stdio.h>
#include <iostream>

enum Fork_STATE {FREE, INUSE};

class Fork
{
public:
    Fork(int p_fork);
    void setForkState();
    void getFork();
    void relaseFork();
    Fork_STATE getStateFork()   {return _forkState;};

private:
    int _fork;
    Fork_STATE _forkState;
};

#endif /* fork_hpp */
