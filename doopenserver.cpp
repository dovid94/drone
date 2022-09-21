#include "doopenserver.h"

OpenServer::OpenServer(){};

/**
 * @brief runs the server on a thread.
 * 
 * @param msg the ip and port number
 */
void OpenServer::command(vector<string> msg) 
{
    Server server;
    _serverThread = thread(&Server::open, &server, msg);
    // Sleep(5000);
    // std::thread t(system, "fgfs --telnet=socket,in,10,127.0.0.1,5402,tcp--httpd=8080 --generic=socket,out,10,127.0.0.1,9999,tcp,generic_small");
    // Sleep(75000);
}

/**
 * @brief returns an instance of the class
 * 
 * @return OpenServer* 
 */
OpenServer *OpenServer::getInstance()
{
    if (!OpenServer::_openServer)
        _openServer = new OpenServer;
    return _openServer;
}

OpenServer *OpenServer::_openServer = 0;

// int main()
// {
//     OpenServer s;
//     s.command({"5400", "10"});
//     return 0;
// }