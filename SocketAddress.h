#pragma once
#pragma comment (lib,"ws2_32.lib") // 윈속 라이브러리 링크
using namespace std;
//#include"UDPSocket.h"
class SocketAddress {
public:
	SocketAddress() {};
	SocketAddress(uint32_t inAddress, uint16_t inPort) {
		GetAsSockAddrIn()->sin_family = AF_INET;
		GetAsSockAddrIn()->sin_addr.S_un.S_addr = htonl(inAddress);
		GetAsSockAddrIn()->sin_port = htons(inPort);
	}
	SocketAddress(char* inAddress, uint16_t inPort) {
		GetAsSockAddrIn()->sin_family = AF_INET;
		GetAsSockAddrIn()->sin_addr.S_un.S_addr = inet_addr(inAddress);
		GetAsSockAddrIn()->sin_port = htons(inPort);
	}
	SocketAddress(const sockaddr& inSockAddr) {
		memcpy(&mSockAddr, &inSockAddr, sizeof(sockaddr));

	}
	size_t GetSize() const { return sizeof(sockaddr); };
	
private:
	friend class UDPSocket;
	friend class TCPSocket;
	sockaddr mSockAddr;
	sockaddr_in* GetAsSockAddrIn() {
		return reinterpret_cast<sockaddr_in*>(&mSockAddr);
	}
	
};
using SocketAddressPtr = std::shared_ptr<SocketAddress>;