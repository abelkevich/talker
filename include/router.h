#pragma once
#include <thread>
#include <mutex>
#include <inttypes.h>
#include <map>
#include <queue>
#include "Msg.h"


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

	void process();

	uint16_t genId();
	void send(Msg msg);
	uint16_t connect(Client* receiver);
	void disconnect(uint16_t id);

public:
	friend class Client;

	Router();
	~Router();
};

}