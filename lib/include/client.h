#pragma once

#include <functional>
#include <mutex>
#include <cinttypes>
#include <map>

#include "msg.h"
#include "utils.h"

namespace Lib
{

class Router;

class Client final
{
private:
	std::mutex m_handlers_mutex;
	Router* m_router;
	uint16_t m_id;

	std::map<size_t, std::function<void(const Msg&)>> m_handlers;

public:	

	bool addHandler(std::pair<size_t, std::function<void(const Msg&)>> handler);

	void receiveUserMsg(Msg msg);
	void receiveSystemMsg(const RouterMsg &msg);

	bool sendSystemMsg(const ClientMsg &msg);

	Client();
	~Client();

	uint16_t getId() const;

	void connect(Router &router);
	bool disconnect();

	bool send(uint16_t receiver, const void* data, size_t len, size_t type_hash);
};

}
