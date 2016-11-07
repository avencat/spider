#ifndef CLIENT_HH_
# define CLIENT_HH_

# include <queue>
# include <string>
# include <boost/asio.hpp>
# include <boost/enable_shared_from_this.hpp>
# include <boost/bind.hpp>
# include <boost/array.hpp>
# include <iostream>
# include "Protocol.h"

class Client {
private:
  // Methods
  void          handle_write(const boost::system::error_code &, const size_t &, const void *);
  void          close();

  // Attributes
  std::queue<void *>           queue;
  int                          id;
  boost::asio::ip::tcp::socket socket;
  boost::array<char, 792>      read_buffer;
  bool                         isAlive;

public:
  Client(boost::asio::io_service &ioservice);
  virtual ~Client();

  // Methods
  boost::asio::ip::tcp::socket  &getSocket();
  void                          setId(const int &);
  const int                     &getId() const;
  void                          receive();
  void                          send(const void *);
  const std::queue<void *>      &getQueue() const;
  void                          popFromQueue();
};

#endif /* !CLIENT_HH_ */
