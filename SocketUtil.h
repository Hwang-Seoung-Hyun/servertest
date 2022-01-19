#ifndef _SOCKETUTIL_H_
#define _SOCKETUTIL_H_
enum SocketAddressFamily {
	INET=AF_INET,
	INET6=AF_INET6
};
class SocketUtil {
public:
	static UDPSocketPtr createUDPSocket(SocketAddressFamily inFamily);
	static TCPSocketPtr createTCPSocket(SocketAddressFamily inFamily);
	static int Select(const vector<TCPSocketPtr>* inReadSet, vector<TCPSocketPtr>*outReadSet,
		const vector<TCPSocketPtr>* inWriteSet, vector<TCPSocketPtr>* outWriteSet,
		const vector<TCPSocketPtr>* inExpectSet, vector<TCPSocketPtr>* outExpectSet);
private:
	static fd_set* FillSetFromVector(fd_set &outSet, const vector<TCPSocketPtr>* inSockets, int& ioNaxNfds);
	static void FillVectorFromSet(vector<TCPSocketPtr>*outSocket, const vector<TCPSocketPtr>*inSocket, const fd_set&inSet);
};
UDPSocketPtr SocketUtil::createUDPSocket(SocketAddressFamily inFamily) {
	SOCKET s = socket(inFamily, SOCK_DGRAM, 0);
	if (s != INVALID_SOCKET)
		return UDPSocketPtr(new UDPSocket(s));
	return nullptr;
}

TCPSocketPtr SocketUtil::createTCPSocket(SocketAddressFamily inFamily) {
	SOCKET s = socket(inFamily, SOCK_STREAM, 0);
	if (s != INVALID_SOCKET)
		return TCPSocketPtr(new TCPSocket(s));
	return nullptr;
}

fd_set* SocketUtil::FillSetFromVector(fd_set &outSet, const vector<TCPSocketPtr>* inSockets, int& ioNaxNfds) {
	if (inSockets) {
		FD_ZERO(&outSet);
		for (const TCPSocketPtr& socket : *inSockets) {
			FD_SET(socket->mSocket, &outSet);
		}
		return &outSet;
	}
	else {
		return nullptr;
	}
}
void SocketUtil::FillVectorFromSet(vector< TCPSocketPtr >* outSockets,
	const vector< TCPSocketPtr >* inSockets, const fd_set& inSet) 
{
	if (inSockets&&outSockets) {
		outSockets->clear();
		for (const TCPSocketPtr& socket : *inSockets) {
			if (FD_ISSET(socket->mSocket, &inSet)) {
				outSockets->push_back(socket);
			}
		}
	}
}
int SocketUtil::Select(const vector<TCPSocketPtr>* inReadSet, vector<TCPSocketPtr>*outReadSet,
	const vector<TCPSocketPtr>* inWriteSet, vector<TCPSocketPtr>* outWriteSet,
	const vector<TCPSocketPtr>* inExceptSet, vector<TCPSocketPtr>* outExceptSet) {
	fd_set read, write, except;

	int nfds = 0;

	fd_set *readPtr = FillSetFromVector(read, inReadSet, nfds);
	fd_set *writePtr = FillSetFromVector(write, inWriteSet, nfds);
	fd_set *exceptPtr = FillSetFromVector(except, inExceptSet, nfds);

	int toRet = select(nfds + 1, readPtr, writePtr, exceptPtr, nullptr);

	if (toRet > 0)
	{
		FillVectorFromSet(outReadSet, inReadSet, read);
		FillVectorFromSet(outWriteSet, inWriteSet, write);
		FillVectorFromSet(outExceptSet, inExceptSet, except);
	}
	return toRet;
}

#endif // !_SOCKETUTIL_H_
