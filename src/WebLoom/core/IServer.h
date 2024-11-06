//  WebLoom Framework
//  Copyright (C) 2024 WebLoom Framework contributors
//  Released under LGPL 3.0 license (see LICENSE)
#ifndef CORE_ISERVER_H_
#define CORE_ISERVER_H_

namespace webloom::core {

using NetworkPort = unsigned int;


class IServer {
 public:
    virtual void Run() = 0;

    virtual void RequestShutdown() = 0;

 protected:
    virtual void ServerLoop() = 0;
};

}   // namespace webloom::core

#endif  // CORE_ISERVER_H_
