#pragma once

namespace Talker
{

class Router
{
private:
    SystemRouter *m_system_router;  
  
public:
    std::list<uint16_t> getOnlineClients();
	bool isQueueEmpty() const;
    bool isClientOnline(uint16_t id);	
	bool disconnectClient(uint16_t id);
	void reset();

	Router(uint16_t freq_khz = 1);
	~Router();
};
 
}
