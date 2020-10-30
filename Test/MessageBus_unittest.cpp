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
	shared_ptr<IMailBox> sub((IMailBox*) new Subscriber("test_sub"));

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

	// Get the interface pointer to ISubscribeMessage to receive messages
	auto consume = dynamic_pointer_cast<ISubscription>(sub);

	// Receive first message
	auto consume_msg_ptr = consume->get_next_message();
	auto t_msg_ptr = dynamic_pointer_cast<TestMessage>(consume_msg_ptr);
	EXPECT_EQ(t_msg_ptr->get_string(), "test string 1");

	bus->publish_message(msg_3);

	// Receive second message
	consume_msg_ptr = consume->get_next_message();
	t_msg_ptr = dynamic_pointer_cast<TestMessage>(consume_msg_ptr);
	EXPECT_EQ(t_msg_ptr->get_string(), "test string 3");
}

TEST(MessageBusTest, MultipleSubscribtionsToTheSameMessageType) {

	// Create test Message Bus
	shared_ptr<Bus> bus = make_shared<Bus>();

	// Create subscriber object with interface to deliver messages
	shared_ptr<IMailBox> sub_1((IMailBox*) new Subscriber("test_sub_1"));
	shared_ptr<IMailBox> sub_2((IMailBox*) new Subscriber("test_sub_2"));

	// Subscribe to a specific message type for both 
	const MessageType subscribed_msg_type = 123;
	const MessageType not_subscribed_msg_type = 124;
	bus->subscribe(subscribed_msg_type, sub_1);
	bus->subscribe(subscribed_msg_type, sub_2);

	// Create 3 messages, being 2 of the subscribed type
	auto msg_1 = make_shared<TestMessage>(subscribed_msg_type, "test string 1");
	auto msg_2 = make_shared<TestMessage>(not_subscribed_msg_type, "test string 2");
	auto msg_3 = make_shared<TestMessage>(subscribed_msg_type, "test string 3");

	// Publish all messages to the mesage bus
	bus->publish_message(msg_1);
	bus->publish_message(msg_2);
	bus->publish_message(msg_3);

	// Get the interface pointer to ISubscribeMessage to receive messages
	auto consume_1 = dynamic_pointer_cast<ISubscription>(sub_1);
	auto consume_2 = dynamic_pointer_cast<ISubscription>(sub_2);

	// Receive first message for first subscriber 
	auto consume_msg_ptr = consume_1->get_next_message();
	auto t_msg_ptr = dynamic_pointer_cast<TestMessage>(consume_msg_ptr);
	EXPECT_EQ(t_msg_ptr->get_string(), "test string 1");

	// Receive second message for first subscriber
	consume_msg_ptr = consume_1->get_next_message();
	t_msg_ptr = dynamic_pointer_cast<TestMessage>(consume_msg_ptr);
	EXPECT_EQ(t_msg_ptr->get_string(), "test string 3");

	// Receive first message for second subscriber 
	consume_msg_ptr = consume_2->get_next_message();
	t_msg_ptr = dynamic_pointer_cast<TestMessage>(consume_msg_ptr);
	EXPECT_EQ(t_msg_ptr->get_string(), "test string 1");

	// Receive second message for first subscriber
	consume_msg_ptr = consume_2->get_next_message();
	t_msg_ptr = dynamic_pointer_cast<TestMessage>(consume_msg_ptr);
	EXPECT_EQ(t_msg_ptr->get_string(), "test string 3");
}

TEST(MessageBusTest, UnsubscribeToPreviousSubscriptionDoesNotGiveNewMessages) {

	// Create test Message Bus
	shared_ptr<Bus> bus = make_shared<Bus>();

	// Create subscriber object with interface to deliver messages
	shared_ptr<IMailBox> sub((IMailBox*) new Subscriber("test_sub"));

	// Subscribe to a specific message type
	const MessageType subscribed_msg_type = 123;
	bus->subscribe(subscribed_msg_type, sub);

	// Create 3 messages, being 2 of the subscribed type
	auto msg_1 = make_shared<TestMessage>(subscribed_msg_type, "test string 1");

	// Publish a message to the mesage bus
	bus->publish_message(msg_1);

	// Get the interface pointer to ISubscribeMessage to receive messages
	auto consume = dynamic_pointer_cast<ISubscription>(sub);

	// Receive message
	auto consume_msg_ptr = consume->get_next_message();
	auto t_msg_ptr = dynamic_pointer_cast<TestMessage>(consume_msg_ptr);
	EXPECT_EQ(t_msg_ptr->get_string(), "test string 1");

	// Unsubscribe 
	bus->unsubscribe(subscribed_msg_type, sub);

	// Publish a new message to the mesage bus
	bus->publish_message(msg_1);

	// Try to receive message
	EXPECT_EQ(consume->get_next_message(), nullptr);
}

TEST(MessageBusTest, UnsubscribeToNonExistentSubscriptionThrowsException) {

	// Create test Message Bus
	auto bus = make_shared<Bus>();

	// Create subscriber object with interface to deliver messages
	shared_ptr<IMailBox> sub((IMailBox*) new Subscriber("test_sub"));

	// Subscribe to a specific message type
	const MessageType subscribed_msg_type = 123;

	// Unsubscribe 
	EXPECT_THROW(bus->unsubscribe(subscribed_msg_type, sub), exception);
}

