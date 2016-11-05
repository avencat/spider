#ifndef CLIENT_HH_
# define CLIENT_HH_

# include <queue>
# include <string>
# include <boost/asio.hpp>
# include <boost/enable_shared_from_this.hpp>
# include <boost/bind.hpp>
# include <boost/array.hpp>
# include <iostream>

class Client {
private:
  // Methods
  void          handle_write(const boost::system::error_code &, const size_t &, std::string &);
  void          handle_read(const boost::system::error_code &);
  void          close();

  // Attributes
  std::queue<std::string>      queue;
  int                          id;
  boost::asio::ip::tcp::socket socket;
  boost::asio::deadline_timer  timer;
  boost::array<char, 128>      read_buffer;
  bool                         isAlive;

public:
  Client(boost::asio::io_service &ioservice);
  virtual ~Client();

  // Methods
  boost::asio::ip::tcp::socket  &getSocket();
  void                          setId(const int &);
  const int                     &getId() const;
  void                          receive();
  void                          send(const std::string &);
  const std::queue<std::string> &getQueue() const;
  void                          popFromQueue();
};

#endif /* !CLIENT_HH_ */
