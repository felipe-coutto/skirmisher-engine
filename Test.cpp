

#include <iostream>

#include "Subscriber.h"
#include "Bus.h"

using namespace MessageBus;
using namespace std;

int main()
{
	cout << "Starting test..." << endl;
	const MessageType test_msg_type = 123;

	cout << "Creating bus" << endl;
	shared_ptr<Bus> bus = make_shared<Bus>();
	
	cout << "Creating pub and sub" << endl;
	shared_ptr<IDeliverMessage> sub((IDeliverMessage *) new Subscriber("test_pub"));

	cout << "Subscribing" << endl;

	bus->subscribe(test_msg_type, sub);

	cout << "Publishing" << endl;
	Message msg(test_msg_type);
	Message msg_2(2);
	msg.set_publisher_name("Test publisher");
	bus->publish_message(msg);
	bus->publish_message(msg_2);
	bus->publish_message(msg);

	cout << "Consuming messages" << endl;
	auto consume = dynamic_pointer_cast<ISubscribeMessage>(sub);

	Message consume_msg;
	while (consume->get_next_message(consume_msg))
	{
		cout << "Received msg from " << consume_msg.get_publisher_name() << endl;
	}

	cout << "Exiting" << endl;
}