#include<iostream>
#include<WinSock2.h>
#include<Windows.h>
#include"UDPSocket.h"
#include"TCPSocket.h"
#pragma comment (lib,"ws2_32.lib") // 윈속 라이브러리 링크
#include"SocketUtil.h"
#include"MemoryStream.h"
#define BUFFERSIZE 1024
using namespace std;
int serverPort = 44425;
char myAddress[30] = "192.168.0.17";/*"192.168.50.175"*/;
void UDPrecv();
void TCPrecv();
void RobocatRecv(RoboCat* outRobo);
int main(void) {
	/////////////////////////////
	///Socket 라이브러리 시작////
	/////////////////////////////
	int a;
	WSADATA wsaData;
	if ((a = WSAStartup(MAKEWORD(2, 2), &wsaData)) != 0) {
		fprintf(stderr, "Socket Library open error\n");
		return -1;
	}
	//TCPrecv();
	RoboCat r;
	RobocatRecv(&r);
	
	//SocketAddress test1();
	//test1.GetSize();

	//////////////////////////
	///Socket 라이브러리 끝///
	//////////////////////////
	WSACleanup();
	return 0;


}
void UDPrecv() {
	SOCKET s = socket(AF_INET, SOCK_DGRAM, 0);
	UDPSocketPtr myserver(new UDPSocket(s));
	char myAddress[30] = "127.0.0.1";
	SocketAddress serverAddr(myAddress, 61557);
	SocketAddress clientAddr;
	char buf[100];
	int isbind = myserver->Bind(serverAddr);
	if (isbind == -1) {
		cout << "bind wrong\n";
	}
	while (true)
	{
		int recvsize = myserver->receiveFrom(buf, 30, clientAddr);

		if (recvsize > 0) {
			buf[strlen(buf)] = '\0';
			cout << buf << "\n";
		}
	}
}
void TCPrecv() {
	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
	TCPSocketPtr listenSocket = SocketUtil::createTCPSocket(INET);
	
	SocketAddress serverAddr(myAddress, serverPort);
	SocketAddress clientAddr;
	unordered_map< TCPSocketPtr, SocketAddress> addressOfSocket;
	char buf[100];
	int isbind = listenSocket->Bind(serverAddr);
	if (isbind == -1) {
		cout << "bind wrong\n";
	}
	
		cout << "wait connect client\n\n";
		int isListen = listenSocket->Listen(32);
		if (isListen < 0)
			return;
		cout << "Listen...\n\n";
		vector<TCPSocketPtr> readBlockSock;
		vector<TCPSocketPtr> readableSock;
		readBlockSock.push_back(listenSocket);
		while (true)
		{
			SocketUtil::Select(&readBlockSock, &readableSock, nullptr, nullptr, nullptr
				, nullptr);
			for (TCPSocketPtr& mysocket : readableSock) {
				if (mysocket == listenSocket) {
					TCPSocketPtr connectSock = mysocket->Accept(clientAddr);
					if (connectSock == nullptr)
						return;
					cout << "success connect!\n\n";
					readBlockSock.push_back(connectSock);
					addressOfSocket.insert_or_assign(connectSock, clientAddr);
					
				}
				else {
					int recvsize = mysocket->Receive(buf, 30);
					if (recvsize > 0) {
						buf[recvsize] = '\0';
						SocketAddress connectAddress = addressOfSocket[mysocket];
						cout << "receive from " << connectAddress.getAddress() << "\n";
						
						cout << buf << "\n";
					}
				}
			}
			

			
		}
}

void RobocatRecv(RoboCat* outRobo) {
	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
	TCPSocketPtr listenSocket = SocketUtil::createTCPSocket(INET);

	SocketAddress serverAddr(myAddress, serverPort);
	SocketAddress clientAddr;
	unordered_map< TCPSocketPtr, SocketAddress> addressOfSocket;
	char buf[100];
	int isbind = listenSocket->Bind(serverAddr);
	if (isbind == -1) {
		cout << "bind wrong\n";
	}

	cout << "wait connect client\n\n";
	int isListen = listenSocket->Listen(32);
	if (isListen < 0)
		return;
	cout << "Listen...\n\n";
	vector<TCPSocketPtr> readBlockSock;
	vector<TCPSocketPtr> readableSock;
	readBlockSock.push_back(listenSocket);
	while (true)
	{
		SocketUtil::Select(&readBlockSock, &readableSock, nullptr, nullptr, nullptr
			, nullptr);
		for (TCPSocketPtr& mysocket : readableSock) {
			if (mysocket == listenSocket) {
				TCPSocketPtr connectSock = mysocket->Accept(clientAddr);
				if (connectSock == nullptr)
					return;
				cout << "success connect!\n\n";
				readBlockSock.push_back(connectSock);
				addressOfSocket.insert_or_assign(connectSock, clientAddr);

			}
			else {
				char*tBuffer = static_cast<char*>(malloc(sizeof(char) * 4096));
				size_t recvSize=mysocket->Receive(tBuffer, 4096);
				if (recvSize > 0) {
					InputMemoryStream inputStream(tBuffer, static_cast<uint32_t>(recvSize));
					outRobo->Read(inputStream);
				}
			}
		}



	}
}