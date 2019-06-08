//
//  fork.hpp
//  thread-filosofi
//
//  Created by Francesco Argentieri on 24/08/16.
//  Copyright © 2016 Francesco Argentieri. All rights reserved.
//

#ifndef FORK_HPP
#define FORK_HPP

enum class forkstate { FREE, INUSE };

class Fork {
 public:
  Fork(unsigned int numfork);
  void acquireFork();
  void getFork();
  void relaseFork();
  forkstate getStateFork();

 private:
  int m_fork;
  forkstate m_state;
};

#endif  // FORK_HPP
