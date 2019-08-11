#include <cstring>

#include "client.h"
#include "router.h"

namespace Lib
{

	HandlerBase::HandlerBase(size_t type_hash)
		: m_type_hash(type_hash)
	{

	}

	size_t HandlerBase::getTypeHash() const
	{
		return m_type_hash;
	}


void Client::receiveUserMsg(Msg msg)
{
	//std::lock_guard<std::mutex> lock(m_handler_mutex);
	
	auto find_it = m_handlers.find(msg.getTypeHash());

	if (find_it == m_handlers.end())
	{
		return;
	}

	find_it->second(msg);

	delete msg.getData();
}

void Client::receiveSystemMsg(const RouterMsg &msg)
{
	switch (msg.msg)
	{
	case ERouterMsg::eConnected:
	{
		m_id = msg.data;
		break;
	}

	case ERouterMsg::eDisconnected:
	case ERouterMsg::eShuttingDown:
		m_router = nullptr;
		break;

	}
}

bool Client::send(uint16_t receiver, const void* data, size_t len, size_t type_hash)
{
	if (!m_router)
	{
		return false;
	}

	uint8_t* data_copy = new uint8_t[len];
	std::memcpy(data_copy, data, len);

	m_router->send(Msg(m_id, receiver, data_copy, len, type_hash));

	return true;
}

Client::Client()
			 : m_router(nullptr)
			 , m_id(0)
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
