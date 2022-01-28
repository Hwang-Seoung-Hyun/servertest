#pragma once
#ifndef _ADDRESSOFSOCKET_H_
#define _ADDRESSOFSOCKET_H_
class AddressOfSocket {
public:
	AddressOfSocket(SocketAddress inSocketAddress, TCPSocketPtr inTCPSocketPtr) :
		mSocketAddress(inSocketAddress), mTCPSocketPtr(inTCPSocketPtr) {};
	char* getAddress() {
		return inet_ntoa(mSocketAddress.GetAsSockAddrIn);
	}
private:
	SocketAddress mSocketAddress;
	TCPSocketPtr mTCPSocketPtr;
	
  

};
#endif // !_ADDRESSOFSOCKET_H_
