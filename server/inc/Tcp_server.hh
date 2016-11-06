//
// Core.hh for Spider server in /home/touzet_t/epitech/cpp/cpp_spider/server/src
//
// Made by Theo TOUZET
// Login   <touzet_t@epitech.net>
//
// Started on  Tue Nov  1 13:49:07 2016 Theo TOUZET
// Last update Jun Nov 4 12:25:30 2016
//

#ifndef TCP_SERVER_HH_
# define TCP_SERVER_HH_

# include "Tcp_connection.hh"

class Tcp_server
{
public:
  Tcp_server(boost::asio::io_service &io_service, const int &port)
    : acceptor(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
  {
    accept();
  }

private:
  boost::asio::ip::tcp::acceptor acceptor;

  void accept()
  {
    Tcp_connection::pointer new_connection =
      Tcp_connection::create(acceptor.get_io_service());

    acceptor.async_accept(new_connection->getSocket(),
        boost::bind(&Tcp_server::handle_accept, this, new_connection,
          boost::asio::placeholders::error));
  }

  void handle_accept(Tcp_connection::pointer new_connection,
      const boost::system::error_code& error)
  {
    if (!error)
    {
      new_connection->start();
      accept();
    }
  }
};

#endif /* !TCP_SERVER_HH_ */
