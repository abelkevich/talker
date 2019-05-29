#include "MsgRouter.h"
#include "MsgReceiver.h"
#include "Msg.h"

namespace Messanger
{
    bool MsgRouterServer::idExist(uint16_t id)
    {
        return m_handlers.find(id) != m_handlers.end();
    }

    MsgRouterServer::MsgRouterServer()
    {
    }

    bool MsgRouterServer::routeMsg(const Msg &msg)
    {
        if (!idExist(msg.getReceiver()))
        {
            return false;
        }

        auto receiver_it = m_handlers.at(msg.getReceiver());

        receiver_it->receiveMsg(msg);
        
        return true;
    }

    bool MsgRouterServer::addReceiver(MsgReceiver &handler)
    {
        if (idExist(handler.getId()))
        {
            return false;
        }

        m_handlers.insert(std::pair<uint16_t, MsgReceiver*>(handler.getId(), &handler));

        return true;
    }

    bool MsgRouterServer::removeReceiver(uint16_t id)
    {
        if (!idExist(id))
        {
            return false;
        }

        m_handlers.erase(id);

        return true;
    }

}