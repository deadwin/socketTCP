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

	//ѭ����������
	SOCKET sClient;
	sockaddr_in remoteAddr;
	int nAddrlen = sizeof(remoteAddr);
	char revData[255];

	while (true) {
		cout << "�ȴ�����..." << endl;
		//�����������Ӷ���Ϊ�գ��߳̽�������˯��״̬
		sClient = accept(slisten, (sockaddr *)&remoteAddr, &nAddrlen);
		if (sClient == INVALID_SOCKET) {
			cout << "accept error !";
			continue;
		}
		cout << "���յ�һ�����ӣ�" << inet_ntoa(remoteAddr.sin_addr)<<endl;

		//��������
		int ret = recv(sClient, revData, 255, 0); //0��ʾ��������ֹ��-1��ʾ��������
		if (ret > 0) {
			revData[ret] = 0x00;
			cout << revData;
		}
		char* sendData = "��ã�TCP�ͻ���\n";
		send(sClient, sendData, strlen(sendData), 0);
		closesocket(sClient);

	}
	closesocket(slisten);
	WSACleanup();
	return 0;
}