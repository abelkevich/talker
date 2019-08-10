#include "client.h"

#include "lib/include/client.h"
#include "lib/include/msg.h"

namespace Talker
{

Client::Client(std::function<void(const Msg&)> msg_hanlder)
			 : m_lib_client(nullptr)
{
	auto msg_adapter_f = [msg_hanlder] (const Lib::Msg& msg)
	{
		msg_hanlder(Msg(msg.getSender(), msg.getReceiver(), msg.getData(), msg.getLength()));
	};

	m_lib_client = new Lib::Client(msg_adapter_f);
}
  
Client::~Client()
{
    delete m_lib_client;
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

bool Client::send(uint16_t receiver, const void* data, size_t len)
{
	return m_lib_client->send(receiver, data, len);
}

}
