#include "router.h"
#include "system_router.h"

namespace Talker{

std::list<uint16_t> Router::getOnlineClients()
{
    return m_system_router->getOnlineClients();
}

bool Router::isQueueEmpty() const
{
    return m_system_router->isQueueEmpty();
}

bool Router::isClientOnline(uint16_t id)
{
    return m_system_router->isClientOnline(id);
}

bool Router::disconnectClient(uint16_t id)
{
    return m_system_router->disconnectClient(id);
}
  
void Router::reset()
{
    m_system_router->reset();
}

Router::Router(uint16_t freq_khz = 1)
             : m_system_router(new SystemRouter(freq_khz))
{
}

Router::~Router()
{
    delete m_system_router;
}

}
