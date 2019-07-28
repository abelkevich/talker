#pragma once
#include <thread>
#include <mutex>
#include <inttypes.h>
#include <map>
#include <queue>
#include <list>
#include <atomic>
#include "msg.h"
#include "utils.h"

namespace Talker 
{

class Client;

class Router final
{
private:
	std::thread m_thread;

	std::map<uint16_t, Client*> m_map_id_receiver;
	std::queue<Msg> m_msg_queue;

	std::mutex m_queue_mutex;
	std::mutex m_clients_mutex;
	std::atomic_bool m_queue_empty;
	
	void process(uint16_t freq_khz);

	uint16_t genId();
	void send(Msg msg);
	bool connect(Client* receiver);
	std::pair<uint16_t, Client*> findByClient(Client* client);

	bool sendSystemMsg(const RouterMsg &msg, Client* client);
	void receiveSystemClientMsg(ClientMsg msg);
	
public:
	friend class Client;

	bool isQueueEmpty() const;
	std::list<const Client*> getClients();
	bool disconnect(const Client* client);
	bool disconnect(uint16_t id);
	void reset();

	Router(uint16_t freq_khz = 1);
	~Router();
};

}
