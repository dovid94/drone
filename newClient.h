#ifndef NEWCLIENT_H_
#define NEWCLIENT_H_

#define WIN32_LEAN_AND_MEAN

#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <queue>
#include "docommand.h"
using namespace std;

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "5402"
#define IP_ADDRESS "127.0.0.1"

class Client: public DoCommand {

    static Client *_client;
    Client();
    static thread _gameThread;
    static thread _clientThread;
    SOCKET _ConnectSocket = INVALID_SOCKET;
    int _iResult;
    char _recvbuf[DEFAULT_BUFLEN];
    int _recvbuflen = DEFAULT_BUFLEN;
    addrinfo *_ptr;
    // const char* _msg;

    // a queue of messages that are to be sent to the simulater.
    queue<string> _clientData;

    public:

    // static const char* _ipAddres;
    // static const char* _port;

    void sender(string message);

    void command(vector<string> msg) override;

    void send_data(const char *sendbuf);

    static Client *getInstance();
};

#endif