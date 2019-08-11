#pragma once

#include <list>

#include "cmn.h"

namespace Lib { class Router; }

namespace Talker
{

class Router final
{
private:
    Lib::Router *m_lib_router;  
  
public:
    std::list<id_t> getOnlineClients();
	bool isQueueEmpty() const;
    bool isClientOnline(id_t id);
	bool disconnectClient(id_t id);
	void reset();

	Lib::Router* getRouter() const;

	Router(id_t freq_khz = 1);
	~Router();
};

}
