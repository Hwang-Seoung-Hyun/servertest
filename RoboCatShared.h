#ifndef _ROBOCATSHARED_H_
#define _ROBOCATSHARED_H_

#pragma once
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX


typedef int socklen_t;
//typedef char* receiveBufer_t;
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <netdb.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
//typedef void* receiveBufer_t;
typedef int SOCKET;
const int NO_ERROR = 0;
const int INVALID_SOCKET = -1;
const int WSAECONNRESET = ECONNRESET;
const int WSAEWOULDBLOCK = EAGAIN;
const int SOCKET_ERROR = -1;
#endif


#include "memory"

#include "vector"
#include "unordered_map"
#include "string"
#include "list"
#include "queue"
#include "deque"
#include "unordered_set"
#include "cassert"

using std::shared_ptr;
using std::unique_ptr;
using std::vector;
using std::queue;
using std::list;
using std::deque;
using std::unordered_map;
using std::string;
using std::unordered_set;

class RoboCat;
class GameObject;
#include <Windows.h>
#include <WinSock2.h>
#include <Ws2tcpip.h>
//#include "StringUtils.h"
#include "SocketAddress.h"
//#include "SocketAddressFactory.h"
#include"TCPSocket.h"
#include"UDPSocket.h"
//#include"SocketUtil.h"

namespace StringUtils
{
	string GetCommandLineArg(int inIndex);

	string Sprintf(const char* inFormat, ...);

	void	Log(const char* inFormat);
	void	Log(const char* inFormat, ...);
}

#define LOG( ... ) StringUtils::Log( __VA_ARGS__ );


#endif // !_ROBOCATSHARED_H_