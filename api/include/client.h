#pragma once

#include <functional>
#include <cinttypes>

#include "msg.h"
#include "router.h"

namespace Lib
{
	class Client;
}

namespace Talker
{

class Client
{
private:
	Lib::Client* m_lib_client;

	bool send(uint16_t receiver, const void* data, size_t len);

public:
	Client(std::function<void(const Msg&)> msg_handler);
	~Client();

	uint16_t getId() const;

	void connect(Router &router);
	bool disconnect();

	template<typename T>
	void send(uint16_t receiver, const T &data)
	{
		send(receiver, &data, sizeof(data));
	}
};

}
