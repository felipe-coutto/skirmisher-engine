#pragma once

#include <string>

using namespace std;

namespace MessageBus
{
	typedef unsigned int MessageType;

	class Message
	{
	public:
		Message();
		Message(MessageType type);
		virtual ~Message() {}

		void set_publisher_name(string pub_name);
		string get_publisher_name();
		MessageType get_type();

	private:
		string m_publisher_name;
		MessageType m_type;
	};
}