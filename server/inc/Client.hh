#ifndef CLIENT_HH_
# define CLIENT_HH_

# include <queue>
# include <string>
# include <boost/asio.hpp>
# include <boost/bind.hpp>
# include <boost/array.hpp>
# include <iostream>
# include "Protocol.h"

# define DELIM "\n"

class Client {
private:
  // Methods
  void                          handle_write(const boost::system::error_code &, const size_t &, std::string &);
  void                          handleRead(const boost::system::error_code &);

  // Attributes
  boost::asio::streambuf        buffer;
  char                          state;
  std::queue<std::string>       queue;
  int                           id;
  boost::asio::ip::tcp::socket  socket;
  bool                          isAlive;

public:
  Client(boost::asio::io_service &ioservice);
  virtual ~Client();

  // Methods
  boost::asio::ip::tcp::socket  &getSocket();
  void                          setState(const char &);
  const char                    &getState() const;
  void                          setId(const int &);
  const int                     &getId() const;
  void                          receive();
  void                          send(const std::string &);
  const std::queue<std::string> &getQueue() const;
  void                          popFromQueue();
  void                          close();

  enum states
  {
    NEW,
    SYN,
    ACK,
    OK
  };
};

#endif /* !CLIENT_HH_ */
