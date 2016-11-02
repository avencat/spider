//
// SQLite3.cpp for Spider in /home/touzet_t/epitech/cpp/cpp_spider/common
// 
// Made by Theo TOUZET
// Login   <touzet_t@epitech.net>
// 
// Started on  Wed Nov  2 14:42:59 2016 Theo TOUZET
// Last update Wed Nov  2 14:43:42 2016 Theo TOUZET
//

#include "SQLite3.hh"

SQLite3::SQLite3(const std::string &name, const bool silent) :
  printMessage(false), printRequest(false)
{
  db = NULL;
  zErrMsg = NULL;
  rc = sqlite3_open(name.c_str(), &db);
  if (rc)
    std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
  else if (!silent)
    std::cout << "Opened database successfully" << std::endl;
}

SQLite3::~SQLite3()
{
  if (db)
    sqlite3_close(db);
}

int	SQLite3::getRc() const
{
  return (rc);
}

std::string	SQLite3::getSql() const
{
  return (sql);
}

std::string	SQLite3::getMessage() const
{
  return (message);
}

bool	SQLite3::getPrintRequest() const
{
  return (printRequest);
}

bool	SQLite3::getPrintMessage() const
{
  return (printMessage);
}

void	SQLite3::setPrintRequest(const bool pr)
{
  printRequest = pr;
}

void	SQLite3::setPrintMessage(const bool pm)
{
  printMessage = pm;
}

int		SQLite3::createTable(const std::string &name,
				     const std::vector<std::string> &columns)
{
  sql = "CREATE TABLE ";
  sql.append(name);
  sql.append("(");
  for (std::vector<std::string>::const_iterator it = columns.begin();
       it != columns.end(); ++it)
    {
      if (it != columns.begin())
	sql.append(",");
      sql.append(*it);
    }
  sql.append(");");
  message = "Table created successfully";
  return (this->execQuery());
}

int		SQLite3::insert(const std::string &name,
				const std::vector<std::string> &columns,
				const std::vector<std::string> &values)
{
  sql = "INSERT INTO ";
  sql.append(name + "(");
  for (std::vector<std::string>::const_iterator it = columns.begin();
       it != columns.end(); ++it)
    {
      if (it != columns.begin())
	sql.append(",");
      sql.append(*it);
    }
  sql.append(") VALUES(");
  for (std::vector<std::string>::const_iterator it = values.begin();
       it != values.end(); ++it)
    {
      if (it != values.begin())
	sql.append(",");
      sql.append(*it);
    }
  sql.append(");");
  message = "Records created successfully";
  return (this->execQuery());
}

int		SQLite3::select(const std::string &name,
				const std::vector<std::string> &columns)
{
  sql = "SELECT ";
  for (std::vector<std::string>::const_iterator it = columns.begin();
       it != columns.end(); ++it)
    {
      if (it != columns.begin())
	sql.append(",");
      sql.append(*it);
    }
  sql.append(" FROM " + name);
  message = "SELECT FROM " + name;
  return (this->execQuery());
}

int	SQLite3::update(const std::string &name,
			const std::string &column,
			const std::string &value,
			const std::string &conditions)
{
  sql = "UPDATE " + name + " set " + column + " = " + value + " where " +
    conditions;
  message = "UPDATE " + name;
  return (this->execQuery());
}

int	SQLite3::deleteSQL(const std::string &name,
			   const std::string &conditions)
{
  sql = "DELETE from " + name + " where " + conditions;
  message = "DELETE from " + name;
  return (this->execQuery());
}

int		SQLite3::callback(void *data, int ac, char **av,
				  char **azColName)
{
  std::string	str(static_cast<char*>(data));

  std::cerr << str << ":" << std::endl;
  for (int i = 0; i < ac; ++i)
    std::cout << azColName[i] << " = " <<
      (av[i] ? av[i] : "NULL") << std::endl;
  std::cout << std::endl;
  return (0);
}

int	SQLite3::execQuery()
{
  if (printRequest)
    std::cout << "Request: " << sql << std::endl;
  rc = sqlite3_exec(db, sql.c_str(), &callback,
		    static_cast<void*>(const_cast<char*>(message.c_str())),
		    &zErrMsg);
  if (rc != SQLITE_OK)
    {
      std::cerr << "SQL error: " << zErrMsg << std::endl;
      sqlite3_free(zErrMsg);
      return (1);
    }
  else if (printMessage)
    std::cout << message << std::endl;
  return (0);
}
