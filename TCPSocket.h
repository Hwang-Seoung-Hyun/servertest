#ifndef _TCPSOCKET_H_
#define _TCPSOCKET_H_
#pragma once
#include"RoboCatShared.h"
class TCPSocket;
using TCPSocketPtr = shared_ptr<TCPSocket>;
class TCPSocket {
public:
	~TCPSocket();
	int Connet(const SocketAddress& inAddress);
	int Bind(const SocketAddress& inToAddress);
	int Listen(int inBackLog = 32);
	TCPSocketPtr Accept(SocketAddress& inFromAddress);
	int Send(const void* inData, int inLen);
	int Receive(void* inBuffer, int inLen);
	int setNonBlockingMode(bool isNonBlocking);
	
private:
	TCPSocket(SOCKET inSocket) :mSocket(inSocket) {};
	friend class SocketUtil;
	SOCKET mSocket;

};
int TCPSocket::Bind(const SocketAddress& inToAddress) {
	int err = bind(mSocket, &inToAddress.mSockAddr, inToAddress.GetSize());
	if (err == 0)
		return NO_ERROR;
	else
		return -1;
	//SocketUtil::ReportError(L"TCPSocket::Bind");
	//return -SocketUtil::GetLastError;
}

int TCPSocket::Connet(const SocketAddress& inAddress) {
	int err = connect(mSocket, &inAddress.mSockAddr, inAddress.GetSize());
	if (err == 0)
		return NO_ERROR;
	else
		return -1;
	//SocketUtil::ReportError(L"TCPSocket::Connect");
	//return -SocketUtil::GetLastError;
}

int TCPSocket::Listen(int inBackLog) {
	int err = listen(mSocket, inBackLog);
	if (err == 0)
		return NO_ERROR;
	else
		return -1;
	//SocketUtil::ReportError(L"TCPSocket::Listen");
	//return -SocketUtil::GetLastError;
}

TCPSocketPtr TCPSocket::Accept(SocketAddress& inFromAddress) {
	int a = inFromAddress.GetSize();
	SOCKET newSocket = accept(mSocket, &inFromAddress.mSockAddr, &a);//inFromAddress에 송신자 주소 채워짐
	if (newSocket != INVALID_SOCKET) {
		return TCPSocketPtr(new TCPSocket(newSocket));
	}
	else {

		return nullptr;
	}
}

int TCPSocket::Send(const void* inData, int inLen) {
	int byteCount = send(mSocket, static_cast<const char*>(inData), inLen, 0);
	if (byteCount >= 0) {
		return byteCount;
	}
	else//error
		return -1;

	//SocketUtil::ReportError("TCPSocket::Send");
	//return -SocketUtil::GetLastError();
}
int TCPSocket::Receive(void* inBuffer, int inLen) {
	int recvByte = recv(mSocket, static_cast<char*>(inBuffer), inLen, 0);
	if (recvByte >= 0) {
		return recvByte;
	}
	else//error
		return -1;

	//SocketUtil::ReportError("TCPSocket::Receive");
	//return -SocketUtil::GetLastError();
}
int TCPSocket::setNonBlockingMode(bool isNonBlocking) {
	u_long a = isNonBlocking ? 1 : 0;
	int result = ioctlsocket(mSocket, FIONBIO, &a);
	if (result != SOCKET_ERROR)
		return NO_ERROR;
	return -1;
}
TCPSocket::~TCPSocket() {
	closesocket(mSocket);
}
#endif // !_TCPSOCKET_H_
