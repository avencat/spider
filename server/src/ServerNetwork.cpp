#include "ServerNetwork.hh"

ServerNetwork::ServerNetwork(const unsigned short &port, std::condition_variable &cv)
                            : ANetwork(), acceptor(ioservice, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)), cv(cv)
{

}

ServerNetwork::~ServerNetwork()
{
  ioservice.stop();
  thread.detach();
  for (std::vector<Client *>::iterator it = clients.begin(); it < clients.end(); it++) {
    (*it)->close();
  }
  cleanClients();
}

void ServerNetwork::readForEachClient(std::mutex &mtx)
{
  std::unique_lock<std::mutex> lock(mtx);
  for (std::vector<Client*>::iterator client = clients.begin(); client != clients.end(); client++) {
    lock.unlock();
    (*client)->receive(mtx);
    lock.lock();
  }
  lock.unlock();
}

void ServerNetwork::writeForEachClient(const std::string &str)
{
  for (std::vector<Client*>::iterator client = clients.begin(); client != clients.end(); client++) {
    if ((*client)->isOpen())
      (*client)->send(str);
  }
}

void ServerNetwork::startAccept(std::mutex &mtx)
{
  thread = std::thread([&]{ServerNetwork::accept(mtx);});
}

void ServerNetwork::accept(std::mutex &mtx)
{
  while (isEnding == false) {
    Client *new_connection = new Client(acceptor.get_io_service(), cv);

    acceptor.accept(new_connection->getSocket());
    std::async(std::launch::async, [&]{ServerNetwork::handleAccept(new_connection, mtx);});
  }
}

void ServerNetwork::handleAccept(Client *new_connection, std::mutex &mtx)
{
  std::unique_lock<std::mutex> lock(mtx);
  new_connection->setState(Client::states::NEW);
  clients.push_back(new_connection);
  cv.notify_one();
  lock.unlock();
}

const std::vector<Client*> ServerNetwork::getClients() const
{
  return (clients);
}

const Client               *ServerNetwork::getClientById(const int &id) const
{
  for (std::vector<Client *>::const_iterator it = clients.begin(); it != clients.end(); it++) {
    if ((*it)->getId() == id)
      return (*it);
  }
  return (NULL);
}

void ServerNetwork::stopService()
{
  isEnding = true;
  this->ioservice.stop();
  thread.join();
}

void ServerNetwork::read(std::mutex &mtx)
{
  readForEachClient(mtx);
}

void ServerNetwork::write(const std::string &str)
{
  writeForEachClient(str);
}

void ServerNetwork::run()
{
  ioservice.run();
}

void ServerNetwork::cleanClients()
{
  for (std::vector<Client*>::iterator client = clients.begin(); client != clients.end(); ) {
    if (!(*client)->is_alive()) {
      delete *client;
      client = clients.erase(client);
    } else {
      client++;
    }
  }
}
