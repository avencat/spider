#ifndef SERVERNETWORK_HH_
# define SERVERNETWORK_HH_

# include "ANetwork.hh"
# include "Client.hh"
# include <thread>
# include <mutex>
# include <future>

class ServerNetwork : public ANetwork {
private:
  std::vector<Client*>           clients;
  std::thread                    thread;
  boost::asio::ip::tcp::acceptor acceptor;
  std::string                    readed;
  std::condition_variable        &cv;

  void                           accept(std::mutex &mtx);
  void                           handleAccept(Client *new_client, std::mutex &mtx);
public:
  ServerNetwork(const unsigned short &port, std::condition_variable &cv);
  virtual ~ServerNetwork();

  // Methods
  void                           startAccept(std::mutex &mtx);
  virtual void                   stopService();
  virtual void                   read(std::mutex &mtx);
  virtual void                   write(const std::string &);
  void                           readForEachClient(std::mutex &mtx);
  void                           writeForEachClient(const std::string &);
  const std::vector<Client*>     getClients() const;
  void                           cleanClients();
  void                           run();
};

#endif /* !SERVERNETWORK_HH_ */
