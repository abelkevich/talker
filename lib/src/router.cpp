#include "router.h"
#include "client.h"

namespace Library
{

Router::Router(uint16_t freq_khz)
             : m_queue_empty(true)
{
	m_msg_queue_process_thread = std::thread([=]{process(freq_khz);});
}

Router::~Router()
{
    reset();
	m_msg_queue_process_thread.join();
}

void Router::receiveSystemMsg(ClientMsg msg)
{
	switch (msg.msg)
	{
	case EClientMsg::eConnectRequest:
	{
	    uint16_t id = connect(msg.client);
	  
		if (!id)
		{
		    msg.client->receiveSystemMsg(RouterMsg(ERouterMsg::eDisconnected));
			return;
		}
	    
		sendSystemMsg(RouterMsg(ERouterMsg::eConnected, id), id);
		return;
	}
	case EClientMsg::eDisconnectRequest:
	case EClientMsg::eShuttingDown:
	{
	    disconnectClient(msg.client->getId());
		return;
	}
	}
}

bool Router::sendSystemMsg(const RouterMsg &msg, uint16_t id)
{
    if(!isClientOnline(id)) return false;

	Client *client = m_map_id_client[id];
	client->receiveSystemMsg(msg);
	return true;
}

void Router::process(uint16_t freq_khz)
{
	auto wait_time = std::chrono::microseconds(1000/freq_khz);

	while (true)
	{
		std::this_thread::sleep_for(wait_time);

		std::lock_guard<std::mutex> lock_queue(m_queue_mutex);

		m_queue_empty = m_msg_queue.empty();

		while (!m_msg_queue.empty())
		{
			const Msg &msg = m_msg_queue.front();
			auto it = m_map_id_client.find(msg.getReceiver());

			if (it != m_map_id_client.end())
			{
			    // TODO: store thread handler to manage it
			    std::thread(&Client::receiveUserMsg, it->second, msg).detach();
			}

			m_msg_queue.pop();
		}

		// TODO: remake empty queue flag
		// or delete this feature
		m_queue_empty = true; 
	}
}

std::list<uint16_t> Router::getOnlineClients()
{
    std::list<uint16_t> clients;

	{
		std::lock_guard<std::mutex> lock_clients(m_clients_mutex);

		for (auto it : m_map_id_client)
		{
			clients.push_back(it.first);
		}
	}

    return clients;
}

bool Router::isQueueEmpty() const
{
    return m_queue_empty;
}

void Router::reset()
{
    {
		std::lock_guard<std::mutex> lock_clients(m_clients_mutex);

		for (auto it: m_map_id_client)
		{
		    disconnectClient(it.second->getId());
		}
    }

	{
	    std::lock_guard<std::mutex> lock_queue(m_queue_mutex);

		while (!m_msg_queue.empty())
		{
			m_msg_queue.pop();
		}
	}
}

uint16_t Router::genId()
{
    for(uint16_t i=1; i<65536; i++)
	{
		if(!isClientOnline(i))
		{
			return i;
		}
	}

	return 0;
}

void Router::send(const Msg msg)
{
	std::lock_guard<std::mutex> lock_queue(m_queue_mutex);
	m_msg_queue.push(msg);
}

uint16_t Router::connect(Client* client)
{
  /*
    {
	  std::lock_guard<std::mutex> lock_clients(m_clients_mutex);

	  for (auto pair : m_map_id_client)
	  {
		  if (client == pair.second) return 0;
	  }
	}
  */
  
	uint16_t id = genId();

	std::lock_guard<std::mutex> lock_clients(m_clients_mutex);

	auto id_client = std::make_pair(id, client);
	m_map_id_client.insert(id_client);

	return id;
}

bool Router::disconnectClient(uint16_t id)
{
    if (!isClientOnline(id))
	{	
       return false;
	}
	
	sendSystemMsg(RouterMsg(ERouterMsg::eDisconnected), id);

	auto it = m_map_id_client.find(id);
	m_map_id_client.erase(it);

	return true;
}
 
bool Router::isClientOnline(uint16_t id)
{
    std::lock_guard<std::mutex> lock_clients(m_clients_mutex);

    auto it = m_map_id_client.find(id);
	return it != m_map_id_client.end();
}

}
