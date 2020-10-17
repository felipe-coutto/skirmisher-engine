#include "Bus.h"

using namespace MessageBus;
using namespace std;

void Bus::publish_message(Message msg)
{
    // Find subscribers to the message type
    auto it = m_subscription_map.find(msg.get_type());
    if (it != m_subscription_map.end())
    {
        deliver_to_subscribers(msg, it->second);
    }
}

void Bus::deliver_to_subscribers(Message msg, SubscriberList subscribers)
{
    //Publish message to list of subscribers
    for (auto it = subscribers.begin(); it != subscribers.end(); ++it)
    {
        (*it)->deliver_message(msg);
    }
}

void Bus::subscribe(MessageType msg_type, SubscriberPtr subscriber)
{
    SubscriberList subscribers = m_subscription_map[msg_type];
    subscribers.push_back(subscriber);
    m_subscription_map[msg_type] = subscribers;
}

void Bus::unsubscribe(MessageType msg_type, SubscriberPtr subscriber)
{

}


