#ifndef SERVERNETWORK_HH_
# define SERVERNETWORK_HH_

# include "Network.hh"
# include "Client.hh"
# include <thread>
# include <mutex>
# include <future>

class ServerNetwork : public Network {
private:
  std::vector<Client*>           clients;
  std::thread                    thread;
  std::mutex                     mtx;
  boost::asio::ip::tcp::acceptor acceptor;

  void accept();
  void handleAccept(Client *new_client);
public:
  ServerNetwork(const std::string &ip, const unsigned short &port);
  virtual ~ServerNetwork();

  // Methods
  void startAccept();
  virtual void stopService();
  void readForEachClient();
  void useData();
  void releaseData();
  const std::vector<Client*> getClients() const;
};

#endif /* !SERVERNETWORK_HH_ */
