#pragma once

#include <string>
#include <queue>
#include <memory>

#include "Bus.h"
#include "ISubscription.h"
#include "IMailBox.h"

using namespace std;

namespace MessageBus
{
	class Bus;

	class Subscriber : public ISubscription, public IMailBox
	{
	public:
		// Constructor
		Subscriber(string name);

		// ISubscription implementations
		virtual shared_ptr<Message> get_next_message();

		// IMailBox implementations
		virtual void deliver_message(shared_ptr<Message> msg);
		virtual string get_name();
	private:
		string m_name;
		shared_ptr<Bus> m_bus_ptr;
		queue<shared_ptr<Message> > m_msg_queue;
	};
}