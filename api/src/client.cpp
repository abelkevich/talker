#include "client.h"

#include "lib/include/client.h"
#include "lib/include/msg.h"

namespace Talker
{

Client::Client()
			 : m_lib_client(new Lib::Client())
{
}
  
Client::~Client()
{
    delete m_lib_client;
}

bool Client::addHandler(size_t type_hash, std::function<void(const Msg&)> handler)
{
	auto handler_adaptor = [handler](const Lib::Msg& lib_msg)
	{
		handler(Msg(lib_msg.getSender(), lib_msg.getData()));
	};

	std::pair<size_t, std::function<void(const Lib::Msg&)>> pair(type_hash, handler_adaptor);

	return m_lib_client->addHandler(pair);
}


uint16_t Client::getId() const
{
	return m_lib_client->getId();
}

void Client::connect(Router &router)
{
	m_lib_client->connect(*router.getRouter());
}

bool Client::disconnect()
{
    return m_lib_client->disconnect();
}

bool Client::send(uint16_t receiver, const void* data, size_t len, size_t type_hash)
{
	return m_lib_client->send(receiver, data, len, type_hash);
}

}
