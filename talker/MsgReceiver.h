#pragma once
#include <inttypes.h>
#include "Msg.h"

namespace Messanger
{

class MsgRouterClient;
class MsgRouterServer;

class MsgReceiver
{
private:
    uint16_t m_id;
    
protected:
    MsgReceiver(uint16_t id);
    virtual void receiveMsg(const Msg& msg) = 0;

public:
    uint16_t getId() const;

    template <typename T>
    MsgData<T> makeMsgData(uint16_t receiver_id, T data)
    {
        return MsgData<T>(getId(), receiver_id, data);
    }

    friend MsgRouterServer;
};

class MsgReceiverWithRouterClient : public MsgReceiver
{
private:
    MsgRouterClient &m_router_client;

protected:

    bool sendMsg(const Msg& msg);

    MsgReceiverWithRouterClient(uint16_t id, MsgRouterClient& router_client);
};

}