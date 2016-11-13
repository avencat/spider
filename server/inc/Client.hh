#ifndef CLIENT_HH_
# define CLIENT_HH_

# include <queue>
# include <string>
# include <boost/asio.hpp>
# include <boost/bind.hpp>
# include <boost/array.hpp>
# include <iostream>
# include <thread>
# include <mutex>
# include <condition_variable>
# include "Protocol.h"

# define DELIM "\r\n"

class Client {
private:
  // Methods
  void                          handle_write(const boost::system::error_code &, const size_t &, std::string &);

  // Attributes
  boost::asio::streambuf        buffer;
  char                          state;
  std::queue<std::string>       queue;
  int                           id;
  boost::asio::ip::tcp::socket  socket;
  bool                          isAlive;
  std::thread                   thread;
  bool                          isReading;
  std::condition_variable       &cv;

public:
  Client(boost::asio::io_service &ioservice, std::condition_variable &cv);
  virtual ~Client();

  // Methods
  boost::asio::ip::tcp::socket  &getSocket();
  void                          setState(const char &);
  const char                    &getState() const;
  void                          setId(const int &);
  const int                     &getId() const;
  void                          receive(std::mutex &mtx);
  void                          do_receive(std::mutex &mtx);
  void                          send(const std::string &);
  const std::queue<std::string> &getQueue() const;
  void                          popFromQueue();
  void                          close();
  bool                          available() const;
  bool                          isOpen() const;
  bool                          is_alive() const;

  enum states
  {
    NEW,
    SYN,
    ACK,
    OK
  };
};

#endif /* !CLIENT_HH_ */
