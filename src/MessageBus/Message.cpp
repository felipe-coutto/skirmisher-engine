#include "Message.h"

using namespace MessageBus;

Message::Message()
{
}

Message::Message(MessageType type) :
	m_type(type)
{
}

void Message::set_publisher_name(string pub_name)
{
	m_publisher_name = pub_name;
}

string Message::get_publisher_name()
{
	return m_publisher_name;
}

MessageType Message::get_type()
{
	return m_type;
}
