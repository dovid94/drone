// to run the server write "C:\\MinGW\\bin\\g++.exe server.cpp -lws2_32"
// and then "./{file_name.exe}", and only then run the flight simulater.
#ifndef SERVER_H_
#define SERVER_H_


#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include "database.h"
using namespace std;


// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

#define DEFAULT_BUFLEN 512
// #define DEFAULT_PORT "5400"

class Server
{
    public:
    void open(vector<string> msg);
};

#endif