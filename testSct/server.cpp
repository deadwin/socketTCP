#include <iostream>
#include <WinSock2.h>
using namespace std;

#pragma  comment(lib,"ws2_32.lib")
int main() {
	WORD wVersionRequested = MAKEWORD(2, 2);

	WSADATA wsaData;

	if (WSAStartup(wVersionRequested, &wsaData) != 0) {
		return 0;
	}

	SOCKET slisten = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (slisten == INVALID_SOCKET) {
		cout << "socket error!";
		return 0;
	}

	sockaddr_in sin;

	sin.sin_family = AF_INET;
	sin.sin_port = htons(1234);
	sin.sin_addr.S_un.S_addr = INADDR_ANY;

	if (bind(slisten, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR) {
		cout << "bind error";
	}

	if (listen(slisten, 5) == SOCKET_ERROR) {
		cout << "listen error";
		return 0;
	}

	//循环接收数据
	SOCKET sClient;
	sockaddr_in remoteAddr;
	int nAddrlen = sizeof(remoteAddr);
	char revData[255];

	while (true) {
		cout << "等待连接..." << endl;
		//如果已完成连接队列为空，线程进入阻塞睡眠状态
		sClient = accept(slisten, (sockaddr *)&remoteAddr, &nAddrlen);
		if (sClient == INVALID_SOCKET) {
			cout << "accept error !";
			continue;
		}
		cout << "接收到一个连接：" << inet_ntoa(remoteAddr.sin_addr)<<endl;

		//接收数据
		int ret = recv(sClient, revData, 255, 0); //0表示连接已中止，-1表示发生错误。
		if (ret > 0) {
			revData[ret] = 0x00;
			cout << revData;
		}
		char* sendData = "你好，TCP客户端\n";
		send(sClient, sendData, strlen(sendData), 0);
		closesocket(sClient);

	}
	closesocket(slisten);
	WSACleanup();
	return 0;
}