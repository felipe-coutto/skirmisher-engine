
#include <sstream>

#include "Bus.h"

using namespace MessageBus;
using namespace std;

void Bus::publish_message(shared_ptr<Message> msg_ptr)
{
    // Find subscribers to the message type
    auto it = m_subscription_map.find(msg_ptr->get_type());
    if (it != m_subscription_map.end())
    {
        deliver_to_subscribers(msg_ptr, it->second);
    }
}

void Bus::deliver_to_subscribers(shared_ptr<Message> msg_ptr, SubscriberList subscribers)
{
    //Publish message to list of subscribers
    for (auto it = subscribers.begin(); it != subscribers.end(); ++it)
    {
        (*it)->deliver_message(msg_ptr);
    }
}

void Bus::subscribe(MessageType msg_type, IMailBoxPtr subscriber)
{
    SubscriberList subscribers = m_subscription_map[msg_type];
    subscribers.push_back(subscriber);
    m_subscription_map[msg_type] = subscribers;
}

void Bus::unsubscribe(MessageType msg_type, IMailBoxPtr subscriber)
{
    SubscriberList subscribers = m_subscription_map[msg_type];

    auto it = std::find_if(std::begin(subscribers),std::end(subscribers),
        [&](const IMailBoxPtr s) { return subscriber->get_name() == s->get_name(); });

    if (it != subscribers.end())
    {
        subscribers.erase(it);
        m_subscription_map[msg_type] = subscribers;
    }
    else
    {
        stringstream msg;
        msg << "Cannot find subscription for msg_type=" << msg_type << " and sub=" << subscriber->get_name();
        throw exception();
    }
}



