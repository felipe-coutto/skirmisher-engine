
#pragma once

#include "Message.h"

using namespace MessageBus;

namespace MessageBus
{
	class IDeliverMessage
	{
	public:
		virtual ~IDeliverMessage() {}
		virtual void deliver_message(Message) = 0;
	};
}