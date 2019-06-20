#include "Client.h"
#include "Router.h"

namespace Talker 
{

	void Client::receive(const Msg &msg)
	{
		m_f(msg);
		delete msg.getData();
	}

	Client::Client(std::function<void(const Msg&)> f, Router *router)
		: m_router(router)
		, m_id(router->connect(this))
		, m_f(f)
	{

	}

	Client::~Client()
	{
		m_router->disconnect(m_id);
	}

	uint16_t Client::getId() { return m_id; }

}