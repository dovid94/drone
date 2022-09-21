#include <thread>
#include "server.h"
#include "docommand.h"


class OpenServer: public DoCommand
{
    
    static OpenServer *_openServer;

    OpenServer();

    thread _serverThread;

    public:
    
    void command(vector<string> msg) override;

    static OpenServer *getInstance();

    
};