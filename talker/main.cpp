#include <iostream>
#include <inttypes.h>

#include "Msg.h"
#include "MsgRouter.h"
#include "MsgReceiver.h"


int main()
{
    using namespace Messanger;

    class Sample : public MsgReceiverWithRouterClient
    {
    private:

        void receiveMsg(const Msg &msg) override
        {
            printf("self id: %d, received from id: %d\n", MsgReceiver::getId(), msg.getSender());
            
            if(compareDataTypes<std::string>(msg)){

                const std::string* str = tryExtractData<std::string>(msg);
                if(str)
                {
                    printf("got MsgDataSample! data: %s\n", str->c_str());
                }
            }

        }
        

    public:

        Sample(uint16_t id, MsgRouterClient &router_client)
            : MsgReceiverWithRouterClient(id, router_client)
        {
        
        }

        void activateTo(uint16_t receiver_id)
        {
            sendMsg(makeMsgData<std::string>(receiver_id, "sraka"));
        }
    };


    MsgRouterServer router_server;
    MsgRouterClient& router_client = router_server;

    Sample s0(0, router_client);
    Sample s1(1, router_client);

    router_server.addReceiver(s0);
    router_server.addReceiver(s1);

    s0.activateTo(1);

    return 0;
}

