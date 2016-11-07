//
// Core.cpp for Spider server in /home/touzet_t/epitech/cpp/cpp_spider/server/src
// 
// Made by Theo TOUZET
// Login   <touzet_t@epitech.net>
// 
// Started on  Tue Nov  1 13:48:39 2016 Theo TOUZET
// Last update Mon Nov  7 06:16:27 2016 Theo TOUZET
//

#include "Core.hh"

Core::Core(const std::string &config) :
  cfg(config), db(cfg.getConfigKey("database"))
{
  std::cout << "DB rc = " << db.getRc() << std::endl;
}

Core::~Core()
{
}

int	Core::run()
{
  std::cout << "Running" << std::endl;
  return (0);
}
