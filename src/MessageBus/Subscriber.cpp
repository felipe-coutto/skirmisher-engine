#include "Subscriber.h"

using namespace MessageBus;

Subscriber::Subscriber(string name):
	m_name(name)
{
}

shared_ptr<Message> Subscriber::get_next_message()
{
	if (!m_msg_queue.empty())
	{
		auto msg_ptr = m_msg_queue.front();
		m_msg_queue.pop();
		return msg_ptr;
	}
	return nullptr;
}

void Subscriber::deliver_message(shared_ptr<Message> msg_ptr)
{
	m_msg_queue.push(msg_ptr);
}

string Subscriber::get_name()
{
	return m_name;
}

