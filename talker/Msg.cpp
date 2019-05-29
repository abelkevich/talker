#include "Msg.h"


namespace Messanger
{
    Msg::Msg(uint16_t sender, uint16_t receiver)
        : m_sender(sender)
        , m_receiver(receiver)
    {

    }

    uint16_t Msg::getSender() const { return m_sender; }
    
    uint16_t Msg::getReceiver() const { return m_receiver; }

    Msg::~Msg()
    {

    }

}