#pragma once

#include <cinttypes>

namespace Library 
{

typedef uint16_t ID;

class Client;

enum class ERouterMsg
{
	eConnected,
	eDisconnected,
	eShuttingDown
};

enum class EClientMsg
{
	eConnectRequest,
	eDisconnectRequest,
	eShuttingDown
};

struct ClientMsg
{
	EClientMsg msg;
	Client *client;

	ClientMsg(EClientMsg msg, Client *client)
		: msg(msg)
		, client(client)
	{

	}
};

struct RouterMsg
{
	ERouterMsg msg;
	uint16_t data;

	RouterMsg(ERouterMsg msg, uint16_t data = 0)
		: msg(msg)
		, data(data)
	{

	}
};

enum class EConnectionStatus
{
	eConnected,
	eDisconnected
};

}
