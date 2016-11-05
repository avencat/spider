#include "ServerNetwork.hh"
#include <cstring>

int main()
{
  ServerNetwork server("127.0.0.1", 4242);

  server.startAccept();
  std::vector<Client*> clients;

  while (42)
  {
    server.useData();
    server.readForEachClient();
    clients = server.getClients();
    for (std::vector<Client*>::iterator client = clients.begin(); client != clients.end(); client++) {
      if ((*client.base())->getSocket().available() > 0)
        (*client.base())->receive();
      else if (!(*client.base())->getQueue().empty() && strcmp((*client.base())->getQueue().front().c_str(), "PING") == 0)
        (*client.base())->send("PONG");
    }
    server.releaseData();
  }

  return 0;
}
