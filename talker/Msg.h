#pragma once
#include <inttypes.h>
#include <typeinfo>

namespace Messanger
{

class Msg
{
private:
    uint16_t m_sender;
    uint16_t m_receiver;
    
protected:

    Msg(uint16_t sender, uint16_t receiver);

public:

    uint16_t getSender() const;
    uint16_t getReceiver() const;
    
    virtual const type_info& getTypeInfo() const = 0;

    virtual ~Msg();
};

template<class T>
class MsgData final: public Msg
{
private:
    T m_data;

public:

    MsgData(uint16_t sender, uint16_t receiver, T data)
        : Msg(sender, receiver)
        , m_data(data)
    {
    
    }

    const type_info& getTypeInfo() const override
    {
        return typeid(T);
    }

    const T& getData() const {return m_data; }
};

template <class T> 
const T* tryExtractData(const Msg& msg)
{
    if(!compareDataTypes<T>(msg))
    {
        return nullptr;
    }
    
    const MsgData<T>* msg_data = dynamic_cast<const MsgData<T>*>(&msg);
    
    if (msg_data)
    {
        return &(msg_data->getData());
    }
    
    return nullptr;
}

template <class T>
bool compareDataTypes(const Msg& msg)
{
    if (msg.getTypeInfo().hash_code() == typeid(T).hash_code())
    {
        return true;
    }


    return false;
}



}