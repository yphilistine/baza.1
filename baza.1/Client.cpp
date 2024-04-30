/*#include "stdafx.h"
#pragma warning(suppress : 4996)
#pragma comment(lib, "Ws2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <winsock2.h>
#include <ws2tcpip.h>


#define  SERVER_PORT     5555
#define  SERVER_NAME    "127.0.0.1"
#define  BUFLEN          512

int  writeToServer(int fd);
int  readFromServer(int fd);


int  main(int argc, char** argv)
{
   
    const char* serverName;
    serverName = (argc < 2) ? "127.0.0.1" : argv[1];
    printf("connecting to %s\n", serverName);

    int err;
    int sock;
    struct sockaddr_in server_addr;
    struct hostent* hostinfo;

    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup failed\n");
        return -1;
    }

    // �������� ���������� � ������� �� ��� DNS �����
    // ��� �������� ������� IP ������.
    hostinfo = gethostbyname(serverName);
    char sss[256];
    printf("host %s\n", inet_ntop(AF_INET, hostinfo->h_addr, sss, 256));
    if (hostinfo == NULL) {
        fprintf(stderr, "Unknown host %s.\n", SERVER_NAME);
        exit(EXIT_FAILURE);
    }
    // ����� ���� �� ������������ GetAddrInfo()

    // ��������� �������� ��������� ��� ������������
    // ������������� ��� ������������ ����������
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr = *(struct in_addr*)hostinfo->h_addr;

    // ������ ������� ������� IP ������
    //unsigned int iaddr;
    //inet_pton(AF_INET, serverName, &iaddr);
    //server_addr.sin_addr.s_addr = iaddr;


    // ������� TCP �����.
    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Client: socket was not created");
        exit(EXIT_FAILURE);
    }

    // ������������� ���������� � ��������
    err = connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if (err < 0) {
        perror("Client:  connect failure");
        exit(EXIT_FAILURE);
    }
    fprintf(stdout, "Connection is ready\n");

    // ������������ �������
    while (1) {
        if (writeToServer(sock) < 0) break;
        if (readFromServer(sock) < 0) break;
    }
    fprintf(stdout, "The end\n");

    // ��������� socket
    closesocket(sock);
    WSACleanup();
    exit(EXIT_SUCCESS);
}



int  writeToServer(int fd)
{
    int   nbytes;
    char  buf[BUFLEN];

    fprintf(stdout, "Send to server > ");
    if (fgets(buf, BUFLEN, stdin) == nullptr) {
        printf("error\n");
    }
    buf[strlen(buf) - 1] = 0;

    nbytes = send(fd, buf, strlen(buf) + 1, 0);
    printf("send %d bytes\n", nbytes);
    //if (nbytes<0) { perror("write"); return -1; } // �� �������� � win socket
    if (strstr(buf, "stop")) return -1;
    return 0;
}


int  readFromServer(int fd)
{
    int   nbytes;
    char  buf[BUFLEN];

    nbytes = recv(fd, buf, BUFLEN, 0);
    if (nbytes < 0) {
        // ������ ������
        perror("read");
        return -1;
    }
    else if (nbytes == 0) {
        // ��� ������ ��� ������
        fprintf(stderr, "Client: no message\n");
    }
    else {
        // ����� ������� ��������
        fprintf(stdout, "Server's replay: %s\n", buf);
    }
    return 0;
}*/
