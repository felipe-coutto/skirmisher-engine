#pragma once

#include <string>
#include <queue>
#include <memory>

#include "Bus.h"
#include "ISubscribeMessage.h"
#include "IDeliverMessage.h"

using namespace std;

namespace MessageBus
{
	

	class Bus;

	class Subscriber : public ISubscribeMessage, public IDeliverMessage

	{
		typedef shared_ptr<Message> MessagePtr;

	public:
		Subscriber(string name);

		virtual shared_ptr<Message> get_next_message();

		virtual void deliver_message(MessagePtr msg);

		string get_name();

	private:
		string m_name;
		shared_ptr<Bus> m_bus_ptr;
		queue<MessagePtr> m_msg_queue;

	};
}