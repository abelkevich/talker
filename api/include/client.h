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

	bool send(uint16_t receiver, const void* data, size_t len, size_t type_hash);
	bool addHandler(size_t, std::function<void(const Msg&)> handler);

public:
	Client();
	~Client();

	uint16_t getId() const;

	void connect(Router &router);
	bool disconnect();

	template<typename T>
	void send(uint16_t receiver, const T &data)
	{
		send(receiver, &data, sizeof(data), typeid(T).hash_code());
	}

	template <typename T>
	bool addHandler(std::function<void(uint16_t, const T*)> user_handler)
	{
		auto handler = [user_handler](const Msg& msg) -> void
		{
			user_handler(msg.sender, reinterpret_cast<const T*>(msg.data));
		};

		return addHandler(typeid(T).hash_code(), handler);
	}
};

}
