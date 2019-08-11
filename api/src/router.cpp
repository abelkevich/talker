#include "router.h"
#include "lib\include\router.h"

namespace Talker
{

Router::Router(id_t freq_khz)
			 : m_lib_router(new Lib::Router(freq_khz))
{
}

Router::~Router()
{
	delete m_lib_router;
}

std::list<id_t> Router::getOnlineClients()
{
    return m_lib_router->getOnlineClients();
}

bool Router::isQueueEmpty() const
{
    return m_lib_router->isQueueEmpty();
}

bool Router::isClientOnline(id_t id)
{
    return m_lib_router->isClientOnline(id);
}

bool Router::disconnectClient(id_t id)
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

}
