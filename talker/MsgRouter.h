#pragma once
#include <map>
#include <inttypes.h>

namespace Messanger 
{

class MsgReceiver;
class Msg;

class MsgRouterClient
{
public:
    virtual bool routeMsg(const Msg &msg) = 0;
};

class MsgRouterServer final : public MsgRouterClient
{
private:
    std::map<uint16_t, MsgReceiver*> m_handlers;

    bool idExist(uint16_t id);

public:

    MsgRouterServer();

    bool routeMsg(const Msg &msg) override;

    bool addReceiver(MsgReceiver &handler);
    bool removeReceiver(uint16_t id);
};
}