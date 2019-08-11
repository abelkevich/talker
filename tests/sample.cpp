#include <iostream>
#include <thread>
#include <string>

#include "router.h"
#include "msg.h"
#include "client.h"

using namespace Talker;

class Sample final
{
private:
	Client *m_client;

	void handle(id_t sender, const std::string* msg)
	{
		std::cout << *msg << std::endl;
	}

public:
	Sample(Router &router)
	{
		m_client = new Client();
	    m_client->addHandler<std::string>([this](id_t sender, const std::string* msg) {handle(sender, msg);});
		m_client->connect(router);
	}

	~Sample()
	{
		delete m_client;
	}

	Client& getClient() const { return *m_client; }
};


void handle_zero(id_t sender, const std::string* msg)
{
	std::cout << "zero\n";
}

int main()
{
    Router router(100);

    Client client_0;

	client_0.addHandler<std::string>(handle_zero);

	client_0.connect(router);

	Sample *sample_0 = new Sample(router);

	for(uint16_t i = 0; i<10; i++)
	{
		client_0.send<std::string>(sample_0->getClient().getId(), std::string("kawabangaa"));

		if (i == 5) sample_0->getClient().disconnect();

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	return 0;
}

