#include "ServerNetwork.hh"

ServerNetwork::ServerNetwork(const std::string &ip, const unsigned short &port) : Network(ip, port), acceptor(ioservice, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
{

}

ServerNetwork::~ServerNetwork()
{

}

void ServerNetwork::useData()
{
  mtx.lock();
}

void ServerNetwork::releaseData()
{
  mtx.unlock();
}

void ServerNetwork::readForEachClient()
{
  for (std::vector<Client*>::iterator client = clients.begin(); client != clients.end(); client++) {
    if ((*client.base())->getSocket().available() > 0)
      (*client.base())->receive();
  }
}

void ServerNetwork::startAccept()
{
  thread = std::thread(&ServerNetwork::accept, this);
}

void ServerNetwork::accept()
{
  while (isEnding == false) {
    Client *new_connection = new Client(acceptor.get_io_service());

    acceptor.accept(new_connection->getSocket());
    std::async(std::launch::async, &ServerNetwork::handleAccept, this, new_connection);
  }
}

void ServerNetwork::handleAccept(Client *new_connection)
{
  mtx.lock();
  clients.push_back(new_connection);
  mtx.unlock();
}

const std::vector<Client*> ServerNetwork::getClients() const
{
  return (clients);
}

void ServerNetwork::stopService()
{
  isEnding = true;
  this->ioservice.stop();
  thread.join();
}
