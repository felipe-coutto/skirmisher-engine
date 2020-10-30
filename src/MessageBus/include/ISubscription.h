#pragma once

#include "Message.h"

namespace MessageBus
{

	class ISubscription
	{
	public:
		virtual ~ISubscription() {};
		virtual shared_ptr<Message> get_next_message() = 0;
	};
}
