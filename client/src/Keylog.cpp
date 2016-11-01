//
// Keylog.cpp for Spider client in C:\Users\vezia_l\Documents\Epitech\cpp_spider\client\inc
// 
// Made by Louis VEZIA
// Login   <vezia_l@epitech.eu>
// 
// Started on  Tue Nov  1 13:50:30 2016 Louis VEZIA
// Last update Tue Nov  1 13:50:48 2016 Louis VEZIA
//

#include "Keylog.hh"

Keylog::Keylog()
{
}

Keylog::~Keylog()
{
}

int		Keylog::getKey()
{
	return (0);
}

int		Keylog::getMouse()
{
	HANDLE hIn;
	HANDLE hOut;
	COORD KeyWhere;
	COORD MouseWhere;
	COORD EndWhere;
	bool Continue = TRUE;
	int KeyEvents = 0;
	int MouseEvents = 0;
	INPUT_RECORD InRec;
	DWORD NumRead;

	hIn = GetStdHandle(STD_INPUT_HANDLE);
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	std::cout << "Key Events   : " << std::endl;
	std::cout << "Mouse Events : " << std::flush;

	KeyWhere.X = 15;
	KeyWhere.Y = 0;
	MouseWhere.X = 15;
	MouseWhere.Y = 1;
	EndWhere.X = 0;
	EndWhere.Y = 3;

	while (Continue)
	{
		ReadConsoleInput(hIn, &InRec, 1, &NumRead);

		switch (InRec.EventType)
		{
		case KEY_EVENT:
			++KeyEvents;
			SetConsoleCursorPosition(hOut,
				KeyWhere);
			std::cout << KeyEvents << std::flush;
			if (InRec.Event.KeyEvent.uChar.AsciiChar == 'x')
			{
				SetConsoleCursorPosition(hOut,
					EndWhere);
				std::cout << "Exiting..." << std::endl;
				Continue = FALSE;
			}
			break;

		case MOUSE_EVENT:
			++MouseEvents;
			SetConsoleCursorPosition(hOut,
				MouseWhere);
			std::cout << MouseEvents << std::flush;
			break;
		}
	}
	return (0);
}

int		Keylog::getForeground()
{
	fg = GetForegroundWindow();

	return (0);
}