//
// main.cpp for Spider client in C:\Users\vezia_l\Documents\Epitech\cpp_spider\client
// 
// Made by Louis VEZIA
// Login   <vezia_l@epitech.eu>
// 
// Started on  Tue Nov  1 13:50:03 2016 Louis VEZIA
// Last update Tue Nov  1 13:50:10 2016 Louis VEZIA
//

#include "Core.hh"
#include "Keylog.hh"

ClientNetwork net;

int		main(int ac, char **av)
{
	Core core;
#if _WIN32
	//fopen_s(&Keylog::myKeylogfile, "MyFileKey", "a+");
#else
	//myKeylogfile = fopen("MyFileKey", "a+");
#endif
	core.run();
	(void)ac;
	(void)av;
	return (0);
}