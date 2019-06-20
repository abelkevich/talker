#include "Router.h"
#include "Client.h"

namespace Talker 
{

	void Router::process()
	{
		while (true)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1));

			std::lock_guard<std::mutex> lock(m_queue_mutex);
			while (!m_msg_queue.empty())
			{
				const Msg &msg = m_msg_queue.front();
				auto it = m_map_id_receiver.find(msg.getReceiver());

				if (it != m_map_id_receiver.end())
				{
					it->second->receive(msg);
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

	uint16_t Router::connect(Client* receiver)
	{
		std::lock_guard<std::mutex> lock(m_queue_mutex);

		uint16_t id = genId();

		auto id_receiver = std::make_pair(id, receiver);
		m_map_id_receiver.insert(id_receiver);

		return id;
	}

	void Router::disconnect(uint16_t id)
	{
		auto it = m_map_id_receiver.find(id);

		if (it != m_map_id_receiver.end())
		{
			m_map_id_receiver.erase(it);
		}
	}

	Router::Router()
	{
		m_thread = std::thread([=] {process(); });
	}

	Router::~Router()
	{
		m_thread.join();
	}

}