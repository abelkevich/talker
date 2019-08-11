#pragma once

#include <functional>
#include <mutex>
#include <cinttypes>
#include <list>
#include <map>

#include "msg.h"
#include "utils.h"

namespace Lib
{

class Router;

class HandlerBase
{
private:
	size_t m_type_hash;
	std::mutex m_handler_mutex;

protected:
	HandlerBase(size_t type_hash);

public:
	size_t getTypeHash() const;
	virtual void receive(const Msg& msg) = 0;
};

template<typename MsgType>
class Handler final
{
private:
	std::function<void(const MsgType*)> m_handler;

public:
	void receive(const Msg& msg) override
	{
		m_handler(reinterpret_cast<const MsgType*>(msg.getData()));
	}

};

class Client final
{
private:
	std::mutex m_handlers_mutex;
	Router* m_router;
	uint16_t m_id;

	std::map<size_t, std::function<void(const Msg&)>> m_handlers;

public:	

	template <typename T>
	bool addHandler(std::function<void(const T*)> user_handler)
	{
		auto handler = [user_handler](const Msg& msg) -> void
		{
			user_handler(reinterpret_cast<const T*>(msg.getData()));
		};

		m_handlers.insert(std::pair<size_t, std::function<void(const Msg&)>>(typeid(T).hash_code(), handler));
	
		return true;
	}

	void receiveUserMsg(Msg msg);
	void receiveSystemMsg(const RouterMsg &msg);

	bool sendSystemMsg(const ClientMsg &msg);

	Client();
	~Client();

	uint16_t getId() const;

	void connect(Router &router);
	bool disconnect();

	template<typename T>
	void send(uint16_t receiver, const T& data)
	{
		send(receiver, &data, sizeof(data), typeid(T).hash_code());
	}

	bool send(uint16_t receiver, const void* data, size_t len, size_t type_hash);
};

}
