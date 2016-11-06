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
  std::mutex                     mtx;
  boost::asio::ip::tcp::acceptor acceptor;
  std::string                    readed;

  void                           accept();
  void                           handleAccept(Client *new_client);
public:
  ServerNetwork(const std::string &ip, const unsigned short &port);
  virtual ~ServerNetwork();

  // Methods
  void                           startAccept();
  virtual void                   stopService();
  virtual void                   read();
  virtual void                   write(const std::string &);
  void                           readForEachClient();
  void                           writeForEachClient(const std::string &);
  // MUST BE CALL BEFORE USING ANY OF THIS OBJECT DATA
  void                           useData();
  // MUST BE CALL AFTER USING ANY OF THIS OBJECT DATA
  void                           releaseData();
  const std::vector<Client*>     getClients() const;
};

#endif /* !SERVERNETWORK_HH_ */
