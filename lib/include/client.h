#pragma once

#include <functional>
#include <mutex>
#include <cinttypes>

#include "msg.h"
#include "utils.h"

namespace Lib
{

class Router;

class Client final
{
private:
	std::mutex m_handler_mutex;
	Router* m_router;
	uint16_t m_id;
	std::function<void(const Msg&)> m_f;

public:	
	void receiveUserMsg(Msg msg);
	void receiveSystemMsg(const RouterMsg &msg);

	bool sendSystemMsg(const ClientMsg &msg);

	Client(std::function<void(const Msg&)> f);
	~Client();

	uint16_t getId() const;

	void connect(Router &router);
	bool disconnect();

	bool send(uint16_t receiver, const void* data, size_t len);
};

}
