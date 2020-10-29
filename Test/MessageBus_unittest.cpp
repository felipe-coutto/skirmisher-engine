#include "pch.h"

#include <MessageBus/include/Bus.h>
#include <MessageBus/include/Subscriber.h>
#include <MessageBus/include/Message.h>

using namespace std;

class TestMessage : public Message
{
public:
	TestMessage() : Message()
	{

	}

	TestMessage(MessageType type) : Message(type)
	{
	}

	TestMessage(MessageType type, string s) : Message(type)
	{
		m_string_data = s;
	}

	void set_string(string s)
	{
		m_string_data = s;
	}

	string get_string()
	{
		return m_string_data;
	}

private:
	string m_string_data;

};

TEST(MessageBusTest, SubscribingToMessageTypeReceivesOnlyMessagesOfThatType) {
	

	// Create test Message Bus
	shared_ptr<Bus> bus = make_shared<Bus>();

	// Create subscriber object with interface to deliver messages
	shared_ptr<IDeliverMessage> sub((IDeliverMessage*) new Subscriber("test_pub"));

	// Subscribe to a specific message type
	const MessageType subscribed_msg_type = 123;
	const MessageType not_subscribed_msg_type = 124;
	bus->subscribe(subscribed_msg_type, sub);

	// Create 3 messages, being 2 of the subscribed type
	auto msg_1 = make_shared<TestMessage>(subscribed_msg_type, "test string 1");
	auto msg_2 = make_shared<TestMessage>(not_subscribed_msg_type, "test string 2");
	auto msg_3 = make_shared<TestMessage>(subscribed_msg_type, "test string 3");


	// Publish all messages to the mesage bus
	bus->publish_message(msg_1);
	bus->publish_message(msg_2);
	bus->publish_message(msg_3);

	// Get the interface pointer to ISubscribeMessage to receive messages
	auto consume = dynamic_pointer_cast<ISubscribeMessage>(sub);

	// Receive first message
	int msg_count = 0;
	auto consume_msg_ptr = consume->get_next_message();
	auto t_msg_ptr = dynamic_pointer_cast<TestMessage>(consume_msg_ptr);
	EXPECT_EQ(t_msg_ptr->get_string(), "test string 1");
	++msg_count;

	// Receive second message
	consume_msg_ptr = consume->get_next_message();
	t_msg_ptr = dynamic_pointer_cast<TestMessage>(consume_msg_ptr);
	EXPECT_EQ(t_msg_ptr->get_string(), "test string 3");
	++msg_count;
}