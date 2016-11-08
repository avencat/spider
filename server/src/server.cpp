//
// server.cpp for Spider server in /home/touzet_t/epitech/cpp/cpp_spider/server/src
// 
// Made by Theo TOUZET
// Login   <touzet_t@epitech.net>
// 
// Started on  Mon Nov  7 05:32:01 2016 Theo TOUZET
// Last update Mon Nov  7 11:01:07 2016 Theo TOUZET
//

#include "Core.hh"

int	main(int ac, char **av)
{
  Core	c("config.ini");

  (void)ac;
  (void)av;
  if (c.run())
    return (1);
  return (0);
}
