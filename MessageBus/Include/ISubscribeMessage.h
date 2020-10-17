#pragma once

#include "Message.h"

namespace MessageBus
{
	class ISubscribeMessage
	{
	public:
		virtual ~ISubscribeMessage() {};
		virtual bool get_next_message(Message&) = 0;
	};
}
