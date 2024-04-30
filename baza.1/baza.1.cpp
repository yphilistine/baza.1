#include "base.h"
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <cstdio>
#include <stdio.h>
#include <random>

#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>

#pragma warning(disable: 4996)

SOCKET Connections[100];
int Counter = 0;

using namespace std;

void ClientHandler(int index) {
	int msg_size;
	setlocale(LC_ALL, "Russian");
	client_data cl;
	while (true) {
		recv(Connections[index], (char*)&msg_size, sizeof(int), NULL);
		char* msg = new char[msg_size + 1];
		msg[msg_size] = '\0';
		recv(Connections[index], msg, msg_size, NULL);
		for (int i = 0; i < Counter; i++) {
			if (i != index) {
				continue;
			}
			//client_data cl, cl1;
			FILE* out = fopen("out2.txt", "w");
			FILE* in1 = fopen("in.txt", "w");
			//cout << msg_size;
			for (int i = 0; i < msg_size; i++) {
				fprintf(in1, "%c", msg[i]);
			}
			fclose(in1);
			FILE* in = fopen("in.txt", "r");
			cl.imput(cl, out, in);
			fclose(in);
			fclose(out);
			ifstream out1("out2.txt");
			string msg1 = ""; string msg2 = "";
			while (getline(out1, msg1))
			{
				msg2.append(msg1); msg2.append("\n");
			}
			out1.close();
			
			int msg_size = msg2.size();
			send(Connections[i], (char*)&msg_size, sizeof(int), NULL);
			send(Connections[i], msg2.c_str(), msg_size, NULL);
			
		}
		delete[] msg;
	}
}

int main(int argc, char* argv[]) {

	
	//WSAStartup
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0) {
		std::cout << "Error" << std::endl;
		exit(1);
	}

	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1111);
	addr.sin_family = AF_INET;

	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
	listen(sListen, SOMAXCONN);

	SOCKET newConnection;
	for (int i = 0; i < 100; i++) {
		newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);

		if (newConnection == 0) {
			std::cout << "Error #2\n";
		}
		else {
			std::cout << "Client Connected!\n";
			std::string msg = "Initiate imput.\n";
			int msg_size = msg.size();
			send(newConnection, (char*)&msg_size, sizeof(int), NULL);
			send(newConnection, msg.c_str(), msg_size, NULL);

			Connections[i] = newConnection;
			Counter++;
			CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandler, (LPVOID)(i), NULL, NULL);
		}
	}


	system("pause");
	return 0;
}
/*
int main()
{
    setlocale(LC_ALL, "Russian");
    int n,i;
    client_data clients;
    printf("Размер базы данных: ");
    cin >> n;
    cout << "\n";

    clients.generate_base(n);
    clients.print_base();
    //clients.print_base_file("out");
    cout << "next base.........................................................................\n"; cout << "\n\n";

    //clients.getlen();
    clients.delete_cl(3);
    clients.print_base();
    //clients.print_base_file("out");
    cout << "0()next base.........................................................................\n"; cout << "\n\n";

    int arr1[3] = { 29,9,2004 };
    int arr11[3] = { 1,1,2000 };
    vector<double> prod1 = { 95699.55, 120499.99 };
    double avg1 = (95699.55 + 120499.99) / 2;
    double sum1 = 95699.55 + 120499.99;
    vector<double> prod11 = { 95699.55, 120499.99,501000.9 };

    //clients.getlen();
    clients.edit_cl(5,"Морозов","Андрей","Александрович",arr1,79175294117,prod1);
    clients.edit_cl(6, "Жепчанов", "Константин", "Холович", arr1, 79175554678, prod1);
    clients.edit_cl("Жепчанов", "Константин", "Холович","Штольц","Александр","Владимирович", arr1, 79175554678, prod11);
    clients.delete_cl("Жепчанов", "Константин", "Холович"); 
    clients.print_base();

    cout << "1()next base.........................................................................\n"; cout << "\n\n";

    (clients.correct()).print_base_file("out2.txt");
    clients.sortby_date();
    clients.print_base();
    clients.print_base_file("out");

    cout << "2()next base.........................................................................\n"; cout << "\n\n";

    client_data oldclients;
    oldclients = clients.select_(arr1,avg1,sum1,79175294117);
    //oldclients.print_base_file("out2.txt");
    oldclients.print_base();

    cout << "3()imput section.........................................................................\n"; //cout << "\n\n";
    cout << "..................................................................................\n"; cout << "\n\n";
    client_data cl;
    cl.imput(clients);
    return 0;
}*/
//out select(1.1.2000, 24.12.2022 / )()()()(200000,1000000)()