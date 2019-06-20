#pragma once
#include <functional>
#include <inttypes.h>
#include "Msg.h"


namespace Talker 
{
	class Router;

	class Client final
	{
	private:
		Router* m_router;
		const uint16_t m_id;
		std::function<void(const Msg&)> m_f;

		void receive(const Msg &msg);

	public:

		Client(std::function<void(const Msg&)> f, Router *router);
		~Client();

		uint16_t getId();

		template<typename T>
		void send(uint16_t receiver, const T &data)
		{
			uint16_t len = sizeof(data);
			uint8_t* data_copy = new uint8_t[len];
			memcpy(data_copy, &data, len);

			m_router->send(Msg(m_id, receiver, data_copy, len));
		}

		friend class Router;
	};

}