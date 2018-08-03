#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <string>
using namespace std;

#pragma comment(lib,"ws2_32.lib")
int main() {
	WORD vVersionRequested = MAKEWORD(2, 2);

	//Ӧ�ó����dllֻ����һ�γɹ���WASStartup()����֮����ܵ��ý�һ����Windows Sockets API������
	WSADATA data;
	if (WSAStartup(vVersionRequested, &data) != 0) {
		cout << "��ʼ��WSAʧ��";
		return 0;
	}

	SOCKET sClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sClient == INVALID_SOCKET) {
		cout << "invalid socket!";
		return 0;
	}

	sockaddr_in serAddr;


	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(1234);
	//C4996	'inet_addr': Use inet_pton() or InetPton() instead or define _WINSOCK_DEPRECATED_NO_WARNINGS to disable deprecated API warnings	TCPClient
	inet_pton(AF_INET, "127.0.0.1", &serAddr.sin_addr);
	/*serAddr.sin_addr.S_un.S_addr = inet_pton(AF_INET,"127.0.0.1",)*/
	if (connect(sClient, (sockaddr*)&serAddr, sizeof(serAddr)) == SOCKET_ERROR) {
		cout << "connect error!";
		closesocket(sClient);
		return 0;
	}
	//char * sendData = "��ã�TCP����ˣ����ǿͻ���!\n";
	string sendData = "hello";
	send(sClient, sendData.c_str(), strlen(sendData.c_str()), 0);
	char recData[255];
	int ret = recv(sClient, recData, 255, 0);
	if (ret > 0) {
		recData[ret] = 0x00;
		cout << recData;
	}
	sendData = "boy";
	//send(sClient, str.c_str(), strlen(str.c_str()), 0);
	closesocket(sClient);
	WSACleanup();

	return 0;
}