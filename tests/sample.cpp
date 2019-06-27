#include <iostream>
#include <string>

#include "Router.h"
#include "Msg.h"
#include "Client.h"

using namespace Talker;


class Sample final
{
private:
	Client *m_client;

	void handle(const Msg& msg)
	{
		std::string *str = reinterpret_cast<std::string*>(msg.getData());

		std::cout << *str << std::endl;
	}

public:
	Sample(Router &router) 
	{
		m_client = new Client([this](const Msg& msg) -> void {handle(msg); });
		m_client->connect(router);
	}

	~Sample()
	{
		delete m_client;
	}

	Client& getClient() const { return *m_client; }
};


void handle_zero(const Msg& msg)
{
	std::cout << "zero\n";
}

int main()
{
    Router router;

    Client client_0(handle_zero);

	client_0.connect(router);

	Sample *sample_0 = new Sample(router);

	for(uint16_t i = 0; i<1000; i++)
	{
		client_0.send<std::string>(sample_0->getClient().getId(), std::string("kawabangaa"));

		if (i == 5) sample_0->getClient().disconnect();

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	while (true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}


	return 0;
}

