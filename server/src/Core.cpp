//
// Core.cpp for Spider server in /home/touzet_t/epitech/cpp/cpp_spider/server/src
//
// Made by Theo TOUZET
// Login   <touzet_t@epitech.net>
//
// Started on  Tue Nov  1 13:48:39 2016 Theo TOUZET
// Last update Tue Nov  8 12:00:15 2016 Theo TOUZET
//

#include "Core.hh"

Core::Core(const std::string &config) :
  cfg(config), db(cfg.getConfigKey("database"), true), server(static_cast<unsigned short>(std::stoul(cfg.getConfigKey("port"))), cv), error_level(NONE_CORE)
{
  std::vector<std::string>	cols;

  createPrivateTable();
  createListTable();
  cols.clear();
  cols.push_back("*");
  db.select(TABLE_KEYS, cols);
}

Core::~Core()
{

}

void				Core::createPrivateTable()
{
  std::vector<std::string>	cols;
  std::vector<std::string>	vals;

  cols.push_back("ID INT PRIMARY KEY NOT NULL");
  cols.push_back("P_KEY TEXT NOT NULL");
  if (!(db.createTable(TABLE_KEYS, cols)))
    {
      cols.clear();
      cols.push_back("ID");
      vals.push_back("1");
      cols.push_back("PRIV_KEY");
      vals.push_back("Random stuff");
      if (db.insert(TABLE_KEYS, cols, vals))
        error_level = CRITICAL_CORE;
    }
}

void				Core::createListTable()
{
  std::vector<std::string>	cols;

  cols.clear();
  cols.push_back("USERNAME TEXT NOT NULL");
  cols.push_back("PUB_KEY TEXT NOT NULL");
  db.createTable(TABLE_LIST, cols);
}

int	Core::getErrorLevel() const
{
  return (error_level);
}

int				Core::newUserDB(const std::string &username, const std::string &key)
{
  std::vector<std::string>	cols;
  std::vector<std::string>	vals;
  int				i;

  db.resetLists();
  cols.push_back("rowid, *");
  db.select(TABLE_LIST, cols);
  vals = db.getValList();
  if (std::find(vals.begin(), vals.end(), username) == vals.end())
    {
      std::cout << "No user " << username << std::endl;
      vals.clear();
      cols.clear();
      cols.push_back("USERNAME");
      vals.push_back(username);
      cols.push_back("PUB_KEY");
      vals.push_back(key);
      if (db.insert(TABLE_LIST, cols, vals))
	return (-1);
    }
  cols.clear();
  db.resetLists();
  cols.push_back("rowid, *");
  db.select(TABLE_LIST, cols);
  cols = db.getColList();
  vals = db.getValList();
  i = 0;

  for (std::vector<std::string>::iterator it = cols.begin(); it != cols.end(); ++it)
    {
      // if (i && i % 2 == 0)
      // 	std::cout << std::endl;
      // else if (i)
      // 	std::cout << "\t| ";
      // std::cout << *it << " = " << vals[i];
      if (username == vals[i])
	return (std::stol(vals[i - 1]));
      ++i;
    }
  std::cout << std::endl;
  return (0);
}

int			Core::handshake(Client &client)
{
  std::string		data;
  t_spider_hs_client	hs;
  char			state;
  std::stringstream	dataStream;

  if (!client.getQueue().empty())
    {
      std::cout << "HANDSHAKE" << std::endl;
      data = client.getQueue().front();
      dataStream.clear();
      dataStream.str(data);
      state = client.getState();
      std::cout << "Client state: " << state << std::endl <<
		"Client data: " << data << std::endl;
      dataStream >> hs.type;
      if (state == Client::states::NEW)
	{
	  if (hs.type != SPD_SYN)
	    {
	      std::cout << "SYN failed" << std::endl;
	      client.close();
	      return (1);
	    }
	  client.setState(Client::states::SYN);
	  client.popFromQueue();
	}
      else if (state == Client::states::SYN)
	{
	  client.setState(Client::states::ACK);
	  client.popFromQueue();
	}
      else if (state == Client::states::ACK)
	{
	  client.setState(Client::states::OK);
	  client.popFromQueue();
	}
    }
  return (0);
}

int	Core::run()
{
  try
    {
      std::cout << "Starting server" << std::endl;
      server.startAccept();
      std::cout << "Server start" << std::endl;
      // Attention, ça pète ici parce que error_level est à CRITICAL_ERROR quand il n'y a pas de database !!!
      // Décommenter la prochaine ligne pour que ça fonctionne au début
      // error_level = 0;
    std::unique_lock<std::mutex> lock(mtx);
    lock.unlock();
      while (error_level != CRITICAL_CORE)
	{
    lock.lock();
    server.cleanClients();
	  clients = server.getClients();
    lock.unlock();
    server.readForEachClient();
    lock.lock();
    cv.wait(lock);
	  for (std::vector<Client*>::iterator client = clients.begin(); client != clients.end(); ++client)
	    {
	      if ((*client)->getState() != Client::states::OK)
		handshake(*(*client));
	      // else if (!(*client.base())->getQueue().empty() &&
	      // 	       std::string(static_cast<char*>((*client.base())->getQueue().front())) ==
	      // 	       std::string("PING\n"))
	      // 	(*client.base())->send("PONG"
				       // );
	    }
	  std::string user("User");
	  newUserDB(user, "random key");
	  lock.unlock();
	}
    }
  catch (const std::exception &e)
    {
      std::cerr << "Exception: " << e.what() << std::endl;
    }
    std::cout << "sortie de run" << std::endl;
  return (0);
}
