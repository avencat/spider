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
	mousePosX = 0;
	mousePosY = 0;
	keyPressed = 0;
}

Keylog::~Keylog()
{
}

int		Keylog::getKey(INPUT_RECORD InRec)
{
	std::cout << InRec.Event.KeyEvent.uChar.AsciiChar << std::endl;
	if (InRec.Event.KeyEvent.uChar.AsciiChar == 'x')
		return (1);
	return (0);
}

int		Keylog::getMouse()
{
	std::cout << "Hello Mouse !" << std::endl;	
	return (0);
}

int		Keylog::getForeground()
{
	fg = GetForegroundWindow();

	return (0);
}