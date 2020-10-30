
#pragma once

#include "Message.h"

using namespace MessageBus;

namespace MessageBus
{
	class IMailBox
	{
	public:
		virtual ~IMailBox() {}
		virtual void deliver_message(shared_ptr<Message>) = 0;
		virtual string get_name() = 0;
	};
}