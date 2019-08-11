#pragma once

#include <cinttypes>

namespace Talker
{

struct Msg final
{
	uint16_t sender;
	uint8_t* data;

	Msg(uint16_t sender, uint8_t* data);
};

}
