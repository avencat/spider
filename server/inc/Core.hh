//
// Core.hh for Spider server in /home/touzet_t/epitech/cpp/cpp_spider/server/src
// 
// Made by Theo TOUZET
// Login   <touzet_t@epitech.net>
// 
// Started on  Tue Nov  1 13:49:07 2016 Theo TOUZET
// Last update Mon Nov  7 11:41:36 2016 Theo TOUZET
//

#ifndef CORE_HH_
# define CORE_HH_

# include <iostream>
# include <string>
# include <vector>
# include "Configuration.hh"
# include "ServerNetwork.hh"
# include "SQLite3.hh"

// Table
# define TABLE_KEYS	"Keys"
# define TABLE_LIST	"List"
# define TABLE_USER	"Usr_"

// Error levels
# define NONE_CORE	0
# define WARNING_CORE	1
# define CRITICAL_CORE	2

class	Core
{
public:
  Core(const std::string&);
  ~Core();

  int	getErrorLevel() const;

  void	createPrivateTable();
  void	createListTable();
  int	newUserDB(const std::string&, const std::string&);
  int	run();

private:
  Configuration		cfg;
  SQLite3		db;
  ServerNetwork		server;
  int			error_level;
  std::vector<Client*>	clients;
};

#endif /* !CORE_HH_ */
