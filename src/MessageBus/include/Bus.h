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
		void publish_message(shared_ptr<Message> msg_ptr);

		void subscribe(MessageType msg_type, SubscriberPtr subscriber);
		void unsubscribe(MessageType msg_type, SubscriberPtr subscriber);

	private:
		void deliver_to_subscribers(shared_ptr<Message> msg_ptr, SubscriberList);

		SubscriptionMap m_subscription_map;
	};

}