#ifndef TCP_CONNECTION_HH_
# define TCP_CONNECTION_HH_

# include <boost/asio.hpp>
# include <boost/enable_shared_from_this.hpp>
# include <boost/bind.hpp>
# include <boost/array.hpp>
# include <iostream>

class Tcp_connection : public boost::enable_shared_from_this<Tcp_connection>
{
public:
  typedef boost::shared_ptr<Tcp_connection> pointer;

  static pointer create(boost::asio::io_service& io_service)
  {
    return pointer(new Tcp_connection(io_service));
  }

  boost::asio::ip::tcp::socket& getSocket()
  {
    return socket;
  }

  void initRead()
	{
		boost::asio::async_read(socket, boost::asio::buffer(buffer),
			boost::bind(&Tcp_connection::handle_read, shared_from_this(),
			boost::asio::placeholders::error));
		timer.expires_from_now(boost::posix_time::seconds(60));
		timer.async_wait(boost::bind(&Tcp_connection::close, shared_from_this()));
	}

  void start()
  {
    message = "Stop bullshit.";

    boost::asio::async_write(socket, boost::asio::buffer(message),
        boost::bind(&Tcp_connection::handle_write, shared_from_this(),
          boost::asio::placeholders::error,
          boost::asio::placeholders::bytes_transferred));
  }

private:
  Tcp_connection(boost::asio::io_service& io_service)
    : socket(io_service), timer(io_service, boost::posix_time::seconds(60))
  {
  }

  void handle_write(const boost::system::error_code& error,
      size_t bytes_transferred)
  {
    if (error) {
      std::cerr << "Error: " << error.message() << std::endl;
      std::cerr << bytes_transferred << " bytes transferred." << std::endl;
    } else {
      initRead();
    }
  }

  void handle_read(const boost::system::error_code& error)
  {
    if (!error) {
      initRead();
    } else {
      close();
    }
  }

  void close()
  {
    socket.close();
  }

  boost::asio::ip::tcp::socket socket;
  std::string message;
  boost::asio::deadline_timer timer;
  boost::array<char, 128> buffer;
};


#endif /* !TCP_CONNECTION_HH_ */
