#pragma once

#include "cmn.h"

namespace Talker
{

struct Msg final
{
	id_t sender;
	uint8_t* data;

	Msg(id_t sender, uint8_t* data);
};

}
