#pragma once

#include <cinttypes>

namespace Lib
{
	class Msg;
}

namespace Talker
{

class Msg final
{
private:
	Lib::Msg* m_lib_msg;


public:
	Msg(uint16_t sender, uint16_t receiver, uint8_t* data, uint16_t len);
	~Msg();

	uint16_t getLength() const;
	uint8_t* getData() const;
	uint16_t getSender() const;
	uint16_t getReceiver() const;
};

}
