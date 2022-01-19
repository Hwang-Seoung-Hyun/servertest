#include<iostream>
#include<WinSock2.h>
#include<Windows.h>
#include"UDPSocket.h"
#include"TCPSocket.h"
#pragma comment (lib,"ws2_32.lib") // ���� ���̺귯�� ��ũ
//#include"SocketAddress.h"
#define BUFFERSIZE 1024
using namespace std;

void UDPrecv();
void TCPrecv();
int main(void) {
	/////////////////////////////
	///Socket ���̺귯�� ����////
	/////////////////////////////
	int a;
	WSADATA wsaData;
	if ((a = WSAStartup(MAKEWORD(2, 2), &wsaData)) != 0) {
		fprintf(stderr, "Socket Library open error\n");
		return -1;
	}
	TCPrecv();
	
	
	//SocketAddress test1();
	//test1.GetSize();

	//////////////////////////
	///Socket ���̺귯�� ��///
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
	TCPSocketPtr myserver(new TCPSocket(s));
	char myAddress[30] = "127.0.0.1";
	SocketAddress serverAddr(myAddress, 44425);
	SocketAddress clientAddr;
	char buf[100];
	int isbind = myserver->Bind(serverAddr);
	if (isbind == -1) {
		cout << "bind wrong\n";
	}
	
		cout << "wait connect client\n\n";
		int isListen = myserver->Listen(32);
		if (isListen < 0)
			return;
		cout << "Listen...\n\n"; 
		TCPSocketPtr connectSock = myserver->Accept(clientAddr);
		if (connectSock == nullptr)
			return;
		cout << "success connect!\n\n";
	while (true)
	{
		int recvsize = connectSock->Receive(buf, 30);
		if (recvsize > 0) {
			buf[strlen(buf)] = '\0';
			cout << buf << "\n";
		}
	}
}