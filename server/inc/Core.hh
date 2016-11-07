//
// Core.hh for Spider server in /home/touzet_t/epitech/cpp/cpp_spider/server/src
// 
// Made by Theo TOUZET
// Login   <touzet_t@epitech.net>
// 
// Started on  Tue Nov  1 13:49:07 2016 Theo TOUZET
// Last update Mon Nov  7 05:47:51 2016 Theo TOUZET
//

#ifndef CORE_HH_
# define CORE_HH_

# include <string>
# include <iostream>
# include "Configuration.hh"
# include "SQLite3.hh"

class	Core
{
public:
  Core(const std::string&);
  ~Core();

  int	run();

private:
  Configuration	cfg;
  SQLite3	db;
};

#endif /* !CORE_HH_ */
