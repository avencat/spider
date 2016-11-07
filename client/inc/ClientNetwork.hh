#ifndef CLIENTNETWORK_HH_
# define CLIENTNETWORK_HH_

# include "ANetwork.hh"
# include <queue>
# include <boost/array.hpp>
# include <boost/bind.hpp>

class ClientNetwork : public ANetwork {
private:
  boost::asio::ip::tcp::socket socket;
  std::queue<void *>           queue;
  boost::array<char, 792>      read_buffer;

public:
  ClientNetwork();
  virtual ~ClientNetwork();

  virtual void read();
  virtual void write(const void *);
  virtual void stopService();
  bool         connect(const std::string &ip, const unsigned short &port);
  void         handle_write(const boost::system::error_code& error, const size_t &bytes_transferred);
};

#endif /* !CLIENTNETWORK_HH_ */
