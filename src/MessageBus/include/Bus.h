#pragma once

#include <string>
#include <map>
#include <list>
#include <memory>

#include "Message.h"
#include "IMailBox.h"

using namespace std;
namespace MessageBus 
{
	class Subscriber; 

	typedef shared_ptr<IMailBox> IMailBoxPtr;
	typedef list<IMailBoxPtr>  SubscriberList;
	typedef map<MessageType, SubscriberList> SubscriptionMap;

	class Bus
	{
	public:
		void publish_message(shared_ptr<Message> msg_ptr);

		void subscribe(MessageType msg_type, IMailBoxPtr subscriber);
		void unsubscribe(MessageType msg_type, IMailBoxPtr subscriber);


	private:
		void deliver_to_subscribers(shared_ptr<Message> msg_ptr, SubscriberList);

		SubscriptionMap m_subscription_map;
	};

}