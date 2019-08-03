#pragma once

#include <cinttypes>

namespace Library
{

class Msg
{
protected:
	const uint16_t m_sender;
	const uint16_t m_receiver;
	const uint16_t m_length;
	uint8_t* m_data;

public:
	Msg(uint16_t sender, uint16_t receiver, uint8_t* data, uint16_t len);

	uint16_t getSender() const;
	uint16_t getReceiver() const;
	uint16_t getLength() const;

	uint8_t* getData() const;
};

}
