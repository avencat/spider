//
// Core.hh for Spider server in /home/touzet_t/epitech/cpp/cpp_spider/server/src
//
// Made by Theo TOUZET
// Login   <touzet_t@epitech.net>
//
// Started on  Tue Nov  1 13:49:07 2016 Theo TOUZET
// Last update Jul Nov 5 15:30:22 2016
//

#ifndef NETWORK_HH_
# define NETWORK_HH_

# include <boost/asio.hpp>
# include <iostream>

class Network {
protected:
  boost::asio::io_service        ioservice;
  boost::asio::ip::tcp::endpoint endpoint;
  bool                           isEnding;
  std::vector<boost::asio::ip::tcp::socket>   socket;

public:
  Network(const std::string &ip, const unsigned short &port);
  virtual ~Network();

  // Methods
  bool connect();
  void stopService();
};

#endif /* !NETWORK_HH_ */
