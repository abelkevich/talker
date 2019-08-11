#include "msg.h"

namespace Lib
{

Msg::Msg(uint16_t sender, uint16_t receiver, uint8_t* data, uint16_t len, size_t type_hash)
	   : m_sender(sender)
	   , m_receiver(receiver)
	   , m_data(data)
	   , m_length(len)
	   , m_type_hash(type_hash)
{
}

uint16_t Msg::getSender() const { return m_sender; }
uint16_t Msg::getReceiver() const { return m_receiver; }
uint16_t Msg::getLength() const { return m_length; }
uint8_t* Msg::getData() const { return m_data; }
size_t Msg::getTypeHash() const { return m_type_hash; }

}
