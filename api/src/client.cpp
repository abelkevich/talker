#include "client.h"
#include "lib/include/client.h"

namespace Talker
{

Client::Client(std::function<void(const Msg&)> msg_hanlder)
             : m_lib_client(new Library::Client(msg_handler))
{
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
	m_lib_client->connect(router->getRouter());
}

bool Client::disconnect()
{
    m_lib_client->disconnect();
}

bool Client::send(uint16_t receiver, const void* data, size_t len)
{
	m_lib_client->send(receiver, data, len);
}

}
