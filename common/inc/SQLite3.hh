//
// SQLite3.hh for Spider in /home/touzet_t/epitech/cpp/cpp_spider/common/inc
// 
// Made by Theo TOUZET
// Login   <touzet_t@epitech.net>
// 
// Started on  Wed Nov  2 14:44:52 2016 Theo TOUZET
// Last update Mon Nov  7 14:21:17 2016 Theo TOUZET
//

#ifndef SQLITE3_HH_
# define SQLITE3_HH_

# include <string>
# include <iostream>
# include <vector>
# include "sqlite3.h"

class	SQLite3
{
public:
  SQLite3(const std::string&, const bool = false);
  ~SQLite3();

  int				getRc() const;
  std::string			getSql() const;
  std::string			getMessage() const;
  bool				getPrintRequest() const;
  bool				getPrintMessage() const;
  std::vector<std::string>	&getColList() const;
  std::vector<std::string>	&getValList() const;
  void				resetLists();
  void				setPrintRequest(const bool);
  void				setPrintMessage(const bool);

  int		createTable(const std::string&,
			    const std::vector<std::string>&);
  int		dropTable(const std::string&);
  int		insert(const std::string&,
		       const std::vector<std::string>&,
		       const std::vector<std::string>&);
  int		select(const std::string&,
		       const std::vector<std::string>&);
  int		update(const std::string&, const std::string&,
  		       const std::string&, const std::string&);
  int		deleteSQL(const std::string&, const std::string&);

  static int	callback(void*, int, char**, char**);

private:
  int		execQuery();

  sqlite3	*db;
  int		rc;
  char		*zErrMsg;
  std::string	sql;
  std::string	message;
  bool		printMessage;
  bool		printRequest;

  static std::vector<std::string>	colList;
  static std::vector<std::string>	valList;
};

#endif /* !SQLITE3_HH_ */
