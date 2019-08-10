#include "msg.h"

#include "lib/include/msg.h"

namespace Talker
{

Msg::Msg(uint16_t sender, uint16_t receiver, uint8_t* data, uint16_t len)
	: m_lib_msg(new Lib::Msg(sender, receiver, data, len))
{
}

Msg::~Msg()
{
	delete m_lib_msg;
}

uint16_t Msg::getSender() const { return m_lib_msg->getSender(); }
uint16_t Msg::getReceiver() const { return m_lib_msg->getReceiver(); }
uint16_t Msg::getLength() const { return m_lib_msg->getLength(); }
uint8_t* Msg::getData() const { return m_lib_msg->getData(); }

}
