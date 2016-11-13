#ifndef CLIENTNETWORK_HH_
# define CLIENTNETWORK_HH_

# include "ANetwork.hh"
# include <queue>
# include <boost/array.hpp>
# include <boost/bind.hpp>

class ClientNetwork : public ANetwork {
private:
  boost::asio::ip::tcp::socket socket;
  std::queue<std::string>      queue;
  boost::array<char, 792>      read_buffer;

public:
  ClientNetwork();
  virtual ~ClientNetwork();

  virtual void read(std::mutex &);
  virtual void write(const std::string &);
  virtual void stopService();
  std::queue<std::string> &getQueue();
  void         receive();
  bool         connect(const std::string &ip, const unsigned short &port);
  void         handle_write(const boost::system::error_code& error, const size_t &bytes_transferred);
};

#endif /* !CLIENTNETWORK_HH_ */
