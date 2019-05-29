#include "MsgReceiver.h"
#include "MsgRouter.h"
#include "Msg.h"

namespace Messanger
{
    MsgReceiver::MsgReceiver(uint16_t id)
        : m_id(id)
    {

    }

    uint16_t MsgReceiver::getId() const { return m_id; }

    MsgReceiverWithRouterClient::MsgReceiverWithRouterClient(uint16_t id, MsgRouterClient& router_client)
        : MsgReceiver(id)
        , m_router_client(router_client)
    {
    
    }
    
    bool MsgReceiverWithRouterClient::sendMsg(const Msg& msg)
    {
        return m_router_client.routeMsg(msg);
    }

}