//
// Core.hh for Spider server in /home/touzet_t/epitech/cpp/cpp_spider/server/src
//
// Made by Theo TOUZET
// Login   <touzet_t@epitech.net>
//
// Started on  Tue Nov  1 13:49:07 2016 Theo TOUZET
// Last update Mar Nov 1 17:42:47 2016
//

#ifndef NETWORK_HH_
# define NETWORK_HH_

# include <boost/asio.hpp>

class Network {
private:
  boost::asio::ip::tcp::acceptor acceptor;
  boost::asio::io_service        ioservice;
  boost::asio::ip::tcp::endpoint endpoint;
  boost::asio::ip::tcp::socket   socket;

public:
  Network();
  virtual ~Network();

  // Methods
  bool read(std::string &str);
  bool write(std::string &str);
  bool accept();
  bool connect(std::string &ip, std::string &port);
};

#endif /* !NETWORK_HH_ */
