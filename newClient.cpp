#include "newClient.h"

/**
 * @brief creates an instance of the class if none exist, and returns the instance 
 * 
 * @return Client* instance of the class
 */
Client *Client::getInstance()
{
    if (!_client)
        _client = new Client();
    return _client;
}

Client::Client(){};

/**
 * @brief initiates a socket that is connected to the simulaters server, enters an infinite while
 * loop and for each itaration it checks if the queue _clientData is empty, if not it will pop the 
 * queues content and send it to the simulater through the socket.
 * 
 * @param sendbuf 
 */
void Client::send_data(const char *sendbuf) 
{
        
    WSADATA wsaData;
    // SOCKET ConnectSocket = INVALID_SOCKET;
    struct addrinfo *result = NULL,
                    *ptr = NULL,
                    hints;
    // int iResult;

    // Initialize Winsock
    _iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (_iResult != 0) {
        printf("WSAStartup failed with error: %d\n", _iResult);
        return;
    }

    ZeroMemory( &hints, sizeof(hints) );
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Resolve the server address and port
    _iResult = getaddrinfo(IP_ADDRESS, DEFAULT_PORT, &hints, &result);
    if ( _iResult != 0 ) {
        printf("getaddrinfo failed with error: %d\n", _iResult);
        WSACleanup();
        return;
    }

    // Attempt to connect to an address until one succeeds
    for(ptr=result; ptr != NULL ;ptr=ptr->ai_next) {

        // Create a SOCKET for connecting to server
        _ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, 
            ptr->ai_protocol);
        if (_ConnectSocket == INVALID_SOCKET) {
            printf("socket failed with error: %ld\n", WSAGetLastError());
            WSACleanup();
            return;
        }

        // Connect to server.
        _iResult = connect( _ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (_iResult == SOCKET_ERROR) {
            closesocket(_ConnectSocket);
            _ConnectSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }

    freeaddrinfo(result);

    if (_ConnectSocket == INVALID_SOCKET) {
        printf("Unable to connect to server!\n");
        WSACleanup();
        return;
    }

    
    while (true)
    {
        if (!_clientData.empty())
        {
            string msg = _clientData.front();
            cout << msg << endl;
            _clientData.pop();
            _iResult = send(_ConnectSocket, msg.data(), (int)strlen(msg.data()), 0 );
        }
    }
    
    recv(_ConnectSocket, _recvbuf, (int)strlen(_recvbuf), 0);
    
    if ( _iResult > 0 )
        printf("Bytes received: %d\n", _iResult);
    else if ( _iResult == 0 )
        printf("Connection closed\n");
    else
        printf("recv failed with error: %d\n", WSAGetLastError());

}

/**
 * @brief starts the flight simulater on a thread, initiates the client socket on a thread
 *  and sleeps for 75 seconds to let the game start.  
 * 
 * @param msg 
 */
void Client::command(vector<string> msg)
{
    Client::_gameThread = thread(system, "fgfs --telnet=socket,in,10,127.0.0.1,5402,tcp--httpd=8080 --generic=socket,out,10,127.0.0.1,9999,tcp,generic_small");
    cout << "game started" << endl;
    Client *cl = cl->getInstance();
    Sleep(75000);
    Client::_clientThread = thread(&Client::send_data, cl, "");

}

/**
 * @brief gets a message that needs to be sent to the simulater and adds it to the queue.
 * 
 * @param message the message that needs to be sent to the simulater
 */
void Client::sender(string message)
{
    _clientData.push(message);
}


thread Client::_clientThread = thread();
thread Client::_gameThread = thread();
Client *Client::_client = 0;


