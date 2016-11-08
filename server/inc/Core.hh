//
// Core.hh for Spider server in /home/touzet_t/epitech/cpp/cpp_spider/server/src
// 
// Made by Theo TOUZET
// Login   <touzet_t@epitech.net>
// 
// Started on  Tue Nov  1 13:49:07 2016 Theo TOUZET
// Last update Tue Nov  8 11:50:30 2016 Theo TOUZET
//

#ifndef CORE_HH_
# define CORE_HH_

# include <iostream>
# include <sstream>
# include <string>
# include <vector>
# include "Configuration.hh"
# include "Protocol.h"
# include "ServerNetwork.hh"
# include "SQLite3.hh"

// Table
# define TABLE_KEYS	"Keys"
# define TABLE_LIST	"List"
# define TABLE_USER	"Usr_"

class	Core
{
public:
  Core(const std::string&);
  ~Core();

  int	getErrorLevel() const;

  void	createPrivateTable();
  void	createListTable();
  int	newUserDB(const std::string&, const std::string&);
  int	handshake(Client&);
  int	run();

private:
  Configuration		cfg;
  SQLite3		db;
  ServerNetwork		server;
  int			error_level;
  std::vector<Client*>	clients;

  enum	errorLevels
    {
      NONE_CORE = 0,
      WARNING_CORE,
      CRITICAL_CORE
    };
};

#endif /* !CORE_HH_ */
