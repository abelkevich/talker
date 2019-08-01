#pragma once
#include <functional>
#include <mutex>
#include <inttypes.h>
#include "msg.h"
#include "utils.h"

namespace Talker 
{
	class Router;

	class Client final
	{
	private:
       	std::mutex m_handler_mutex;
       	Router* m_router;
		uint16_t m_id;
		std::function<void(const Msg&)> m_f;

		void receiveUserMsg(Msg msg);
		void receiveSystemMsg(const RouterMsg &msg);

		bool sendSystemMsg(const ClientMsg &msg);

	public:
		Client(std::function<void(const Msg&)> f);
		~Client();

		uint16_t getId() const;

		void connect(Router &router);
		bool disconnect();

		bool send(uint16_t receiver, const void* data, size_t len);

		template<typename T>
		void send(uint16_t receiver, const T &data)
		{
			send(receiver, &data, sizeof(data));
		}

		friend class Router;
	};

}
