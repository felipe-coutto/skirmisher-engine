#include "Subscriber.h"

using namespace MessageBus;

MessageBus::Subscriber::Subscriber(string name):
	m_name(name)
{
}

bool MessageBus::Subscriber::get_next_message(Message& msg)
{
	bool has_msg = false;
	if (!m_msg_queue.empty())
	{
		msg = m_msg_queue.front();
		m_msg_queue.pop();
		has_msg = true;
	}

	return has_msg;
}

void Subscriber::deliver_message(Message msg)
{
	m_msg_queue.push(msg);
}

string MessageBus::Subscriber::get_name()
{
	return m_name;
}
