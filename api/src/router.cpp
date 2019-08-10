#include "router.h"
#include "lib\include\router.h"

namespace Talker
{

std::list<uint16_t> Router::getOnlineClients()
{
    return m_lib_router->getOnlineClients();
}

bool Router::isQueueEmpty() const
{
    return m_lib_router->isQueueEmpty();
}

bool Router::isClientOnline(uint16_t id)
{
    return m_lib_router->isClientOnline(id);
}

bool Router::disconnectClient(uint16_t id)
{
    return m_lib_router->disconnectClient(id);
}
  
void Router::reset()
{
    m_lib_router->reset();
}

Lib::Router* Router::getRouter() const
{
	return m_lib_router;
}

Router::Router(uint16_t freq_khz)
             : m_lib_router(new Lib::Router(freq_khz))
{
}

Router::~Router()
{
    delete m_lib_router;
}
}
