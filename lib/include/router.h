#pragma once

#include <thread>
#include <mutex>
#include <cinttypes>
#include <map>
#include <queue>
#include <list>
#include <atomic>

#include "msg.h"
#include "utils.h"

namespace Lib
{

class Client;

class Router final
{
private:
	std::thread m_msg_queue_process_thread;

	std::map<uint16_t, Client*> m_map_id_client;
	std::queue<Msg> m_msg_queue;

	std::mutex m_queue_mutex;
	std::mutex m_clients_mutex;
	std::atomic_bool m_queue_empty;
	
	void process(uint16_t freq_khz);
	uint16_t genId();
	bool sendSystemMsg(const RouterMsg &msg, uint16_t id);

public:
	// Client part
	void receiveSystemMsg(ClientMsg msg);
	void send(Msg msg);
	uint16_t connect(Client* receiver);

	// User part
	std::list<uint16_t> getOnlineClients();
	bool isQueueEmpty() const;
    bool isClientOnline(uint16_t id);	
	bool disconnectClient(uint16_t id);
	void reset();

	Router(uint16_t freq_khz);
	~Router();
};
 
}
