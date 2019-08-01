#include <cstring>
#include "client.h"
#include "router.h"

namespace Talker 
{

void Client::receiveUserMsg(Msg msg)
{
	std::lock_guard<std::mutex> lock(m_handler_mutex);
	m_f(msg);
	delete msg.getData();
}

void Client::receiveSystemMsg(const RouterMsg &msg)
{
	switch (msg.msg)
	{
	case Talker::ERouterMsg::eConnected:
	{
		m_id = msg.data;
		break;
	}

	case Talker::ERouterMsg::eDisconnected:
	case Talker::ERouterMsg::eShuttingDown:
		m_router = nullptr;
		break;

	}
}

bool Client::send(uint16_t receiver, const void* data, size_t len)
{
	if (!m_router)
	{
		return false;
	}

	uint8_t* data_copy = new uint8_t[len];
	std::memcpy(data_copy, data, len);

	m_router->send(Msg(m_id, receiver, data_copy, len));

	return true;
}

Client::Client(std::function<void(const Msg&)> f)
			 : m_router(nullptr)
			 , m_id(0)
			 , m_f(f)
{

}

Client::~Client()
{
	disconnect();
}

void Client::connect(Router &router)
{
	disconnect();

	m_router = &router;
	sendSystemMsg(ClientMsg(EClientMsg::eConnectRequest, this));
}

bool Client::disconnect()
{
	return sendSystemMsg(ClientMsg(EClientMsg::eDisconnectRequest, this));
}

bool Client::sendSystemMsg(const ClientMsg &msg)
{
	if (!m_router) return false;

	m_router->receiveSystemMsg(msg);
	return true;
}

uint16_t Client::getId() const { return m_id; }

}
