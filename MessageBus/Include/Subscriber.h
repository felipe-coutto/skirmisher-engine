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
	public:
		Subscriber(string name);

		virtual bool get_next_message(Message& msg);

		virtual void deliver_message(Message msg);

		string get_name();

	private:
		string m_name;
		shared_ptr<Bus> m_bus_ptr;
		queue<Message> m_msg_queue;

	};
}