#include <iostream>
#include <string>

#include "Router.h"
#include "Msg.h"
#include "Client.h"

using namespace Talker;

void handle_zero(const Msg& msg)
{
    std::cout << "zero\n";
}

void handle_first(const Msg& msg)
{
	std::string *str = reinterpret_cast<std::string*>(msg.getData());

    std::cout << *str << std::endl;
}

int main()
{
    Router router;

    Client client_0(handle_zero, &router);
    Client client_1(handle_first, &router);


	for(uint16_t i = 0; i<1000; i++)
	{
		client_0.send(client_1.getId(), std::string("kawabangaa"));

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	while (true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}


	return 0;
}

