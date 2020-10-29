#include "Subscriber.h"

using namespace MessageBus;

MessageBus::Subscriber::Subscriber(string name):
	m_name(name)
{
}

shared_ptr<Message> MessageBus::Subscriber::get_next_message()
{
	bool has_msg = false;

	if (!m_msg_queue.empty())
	{
		auto msg_ptr = m_msg_queue.front();
		m_msg_queue.pop();
		return msg_ptr;
	}
	return nullptr;
}

void Subscriber::deliver_message(MessagePtr msg_ptr)
{
	m_msg_queue.push(msg_ptr);
}

string MessageBus::Subscriber::get_name()
{
	return m_name;
}
