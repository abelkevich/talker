#include "Router.h"
#include "Client.h"

namespace Talker 
{

	void Router::receiveSystemClientMsg(ClientMsg msg)
	{
		switch (msg.msg)
		{
		case Talker::EClientMsg::eConnectRequest:
		{
			if (!connect(msg.client))
			{
				sendSystemMsg(RouterMsg(ERouterMsg::eDisconnected), msg.client);
				return;
			}

			auto pair = findByClient(msg.client);
			sendSystemMsg(RouterMsg(ERouterMsg::eConnected, pair.first), msg.client);

			return;
		}
		case Talker::EClientMsg::eDisconnectRequest:
		case Talker::EClientMsg::eShuttingDown:
		{
			disconnect(msg.client);
			sendSystemMsg(RouterMsg(ERouterMsg::eDisconnected), msg.client);

			return;
		}
		}
	}

	bool Router::sendSystemMsg(const RouterMsg &msg, Client* client)
	{
		if (!client) return false;

		client->receiveSystemRouterMsg(msg);
		return true;
	}

	void Router::process(uint16_t freq_khz)
	{
		auto wait_time = std::chrono::microseconds(1000000 / (freq_khz * 1000));
		
		while (true)
		{
			std::this_thread::sleep_for(wait_time);

			std::lock_guard<std::mutex> lock(m_queue_mutex);
			while (!m_msg_queue.empty())
			{
				const Msg &msg = m_msg_queue.front();
				auto it = m_map_id_receiver.find(msg.getReceiver());

				if (it != m_map_id_receiver.end())
				{
					it->second->receiveUserMsg(msg);
					m_msg_queue.pop();
				}
			}
		}
	}

	uint16_t Router::genId()
	{
		static uint16_t id = 0;
		return id++;
	}

	void Router::send(const Msg msg)
	{
		std::lock_guard<std::mutex> lock(m_queue_mutex);
		m_msg_queue.push(msg);
	}

	std::pair<uint16_t, Client*> Router::findByClient(Client* client)
	{
		std::lock_guard<std::mutex> lock(m_queue_mutex);

		for (auto pair : m_map_id_receiver)
		{
			if (client == pair.second) return pair;
		}

		return std::pair<uint16_t, Client*>(0, nullptr);
	}

	bool Router::connect(Client* client)
	{
		std::lock_guard<std::mutex> lock(m_queue_mutex);

		for (auto pair : m_map_id_receiver)
		{
			if (client == pair.second) return false;
		}

		uint16_t id = genId();

		auto id_client = std::make_pair(id, client);
		m_map_id_receiver.insert(id_client);


		return true;
	}

	bool Router::disconnect(Client* client)
	{
		std::lock_guard<std::mutex> lock(m_queue_mutex);

		auto it = m_map_id_receiver.find(client->getId());

		if (it == m_map_id_receiver.end())
		{
			return false;
		}

		m_map_id_receiver.erase(it);

		return true;
	}

	Router::Router(uint16_t freq_khz)
	{
		m_thread = std::thread([=] {process(freq_khz); });
	}

	Router::~Router()
	{
		for (auto pair : m_map_id_receiver)
		{
			sendSystemMsg(RouterMsg(ERouterMsg::eShuttingDown), pair.second);
		}
		
		m_thread.join();
	}

}