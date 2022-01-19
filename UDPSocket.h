#pragma once
#ifndef _UDPSOCKET_H_
#define _UDPSOCKET_H_

#include "RoboCatShared.h"
#pragma comment (lib,"ws2_32.lib") // 윈속 라이브러리 링크
using namespace std;

class UDPSocket {
public:
	~UDPSocket();
	int Bind(const SocketAddress& inToAddress);
	int sendTo(const void* inData, int inLen, const SocketAddress& into);
	int receiveFrom(void* inBuffer, int inLen, SocketAddress& outfrom);

	UDPSocket(SOCKET inSocket) :mSocket(inSocket) {};
private:
	friend class SocketUtil;
	friend class SocketAddress;

	SOCKET mSocket;
};
using UDPSocketPtr = shared_ptr<UDPSocket>;


int UDPSocket::Bind(const SocketAddress&inBindAddress) {
	int err = bind(mSocket, &inBindAddress.mSockAddr, inBindAddress.GetSize());
	if (err == 0)
		return NO_ERROR;
	else
		return -1;
	//SocketUtil::ReportError(L"UDPSocket::Bind");
	//return -SocketUtil::GetLastError;
}

int UDPSocket::sendTo(const void* inData, int inLen, const SocketAddress& inTo) {
	int byteSentCount = sendto(mSocket, static_cast<const char*>(inData), inLen, 0, &inTo.mSockAddr, inTo.GetSize());
	if (byteSentCount > 0) {//no error
		return byteSentCount;
	}
	else//error
		return -1;

	//SocketUtil::ReportError(L"UDPSocket::sendTo);
	//return -SocketUtil::GetLastError;
}

int UDPSocket::receiveFrom(void* inBuffer, int inLen, SocketAddress& outfrom) {
	int fromsize = outfrom.GetSize();
	int byteReceiveCount = recvfrom(mSocket, static_cast<char*>(inBuffer), inLen, 0, &outfrom.mSockAddr, &fromsize);
	if (byteReceiveCount > 0)//no error
		return byteReceiveCount;
	else//error
		return -1;

	//SocketUtil::ReportError(L"UDPSocket::receiveFrom);
	//return -SocketUtil::GetLastError;
}

UDPSocket::~UDPSocket() {
	closesocket(mSocket);
}

//shared_ptr<UDPSocket> UDPSocket::CreateUDPSocket(SocketAddressFamily inFamily) {

//}
#endif // !_UDPSOCKET_H

