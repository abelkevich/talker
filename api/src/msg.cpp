#include "msg.h"

#include "lib/include/msg.h"

namespace Talker
{

Msg::Msg(uint16_t sender, uint8_t* data)
	   : sender(sender)
	   , data(data)
{
}

}
