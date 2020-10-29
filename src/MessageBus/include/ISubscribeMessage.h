#pragma once

#include "Message.h"

namespace MessageBus
{

	class ISubscribeMessage
	{
	public:
		virtual ~ISubscribeMessage() {};
		virtual shared_ptr<Message> get_next_message() = 0;
	};
}
