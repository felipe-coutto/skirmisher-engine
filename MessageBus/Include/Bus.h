#pragma once

#include <string>
#include <map>
#include <list>
#include <memory>

#include "Message.h"
#include "IDeliverMessage.h"

using namespace std;
namespace MessageBus 
{
	class Subscriber; 

	typedef shared_ptr<IDeliverMessage> SubscriberPtr;
	typedef list<SubscriberPtr>  SubscriberList;
	typedef map<MessageType, SubscriberList> SubscriptionMap;

	class Bus
	{
	public:
		void publish_message(Message msg);

		void subscribe(MessageType msg_type, SubscriberPtr subscriber);
		void unsubscribe(MessageType msg_type, SubscriberPtr subscriber);

	private:
		void deliver_to_subscribers(Message msg, SubscriberList);

		SubscriptionMap m_subscription_map;
	};

}