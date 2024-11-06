//  WebLoom Framework
//  Copyright (C) 2024 WebLoom Framework contributors
//  Released under LGPL 3.0 license (see LICENSE)
#ifndef SOCKETDEFINITIONS_H_
#define SOCKETDEFINITIONS_H_
#include "core/Platform.h"

#if (WEBLOOM_PLATFORM == WEBLOOM_PLATFORM_WINDOWS_MSVC)
# include <winsock2.h>

typedef int socklen_t;

#else
# include <unistd.h>         // For close()
# include <arpa/inet.h>      // For inet_pton()
# include <sys/socket.h>     // For socket functions
# include <netinet/in.h>     // For sockaddr_in

# define SOCKET int

# define closesocket        close

# define INVALID_SOCKET      -1
# define SOCKET_ERROR        -1

#endif

#endif  //  SOCKETDEFINITIONS_H_
