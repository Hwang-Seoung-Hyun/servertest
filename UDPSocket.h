#pragma once
#include"SocketAddress.h"
//#include"SocketUtil.h"
#pragma comment (lib,"ws2_32.lib") // ���� ���̺귯�� ��ũ
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

int UDPSocket::receiveFrom(void* inToReceive, int inMaxLength, SocketAddress& outFromAddress)
{
	int fromLength = outFromAddress.GetSize();

	int readByteCount = recvfrom(mSocket,
		static_cast<char*>(inToReceive),
		inMaxLength,
		0, &outFromAddress.mSockAddr, &fromLength);
	if (readByteCount >= 0)
	{
		return readByteCount;
	}
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