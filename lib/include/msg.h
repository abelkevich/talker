#pragma once

#include <cinttypes>

namespace Lib
{

class Msg final
{
protected:
	const uint16_t m_sender;
	const uint16_t m_receiver;
	const uint16_t m_length;
	const size_t m_type_hash;
	uint8_t* m_data;

public:
	Msg(uint16_t sender, uint16_t receiver, uint8_t* data, uint16_t len, size_t type_hash);

	uint16_t getSender() const;
	uint16_t getReceiver() const;
	uint16_t getLength() const;
	size_t getTypeHash() const;

	uint8_t* getData() const;
};

}
