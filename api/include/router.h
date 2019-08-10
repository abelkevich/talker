#pragma once

#include <list>
#include <cinttypes>

namespace Lib
{
	class Router;
}

namespace Talker
{

class Router
{
private:
    Lib::Router *m_lib_router;  
  
public:
    std::list<uint16_t> getOnlineClients();
	bool isQueueEmpty() const;
    bool isClientOnline(uint16_t id);
	bool disconnectClient(uint16_t id);
	void reset();

	Lib::Router* getRouter() const;

	Router(uint16_t freq_khz = 1);
	~Router();
};

}
