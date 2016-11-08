#include "Client.hh"

Client::Client(boost::asio::io_service &ioservice) : socket(ioservice)
{
  isAlive = true;
}

Client::~Client()
{

}

void Client::setState(const char &state)
{
  this->state = state;
}

const char &Client::getState() const
{
  return (this->state);
}

void Client::setId(const int &new_id)
{
  this->id = new_id;
}

const int &Client::getId() const
{
  return (this->id);
}

const std::queue<std::string> &Client::getQueue() const
{
  return (this->queue);
}

void Client::popFromQueue()
{
  this->queue.pop();
}

boost::asio::ip::tcp::socket &Client::getSocket()
{
  return socket;
}

void Client::receive()
{
  if (!socket.is_open() || socket.available() <= 0)
    return ;
  boost::asio::async_read_until(socket, buffer, "\r\n",
                                boost::bind(&Client::handleRead, this,
                                boost::asio::placeholders::error));
}

void Client::send(const std::string &to_send)
{
  if (!socket.is_open())
    return ;
  boost::asio::async_write(socket, boost::asio::buffer(std::string(to_send)),
                           boost::bind(&Client::handle_write,
                           this, boost::asio::placeholders::error,
                           boost::asio::placeholders::bytes_transferred,
                           to_send));
}

void Client::handleRead(const boost::system::error_code &error)
{
  if (!error) {
    std::istream is(&buffer);
    std::string str;
    std::getline(is, str);
    queue.push(str);
  } else {
    isAlive = false;
    close();
  }
}

void Client::handle_write(const boost::system::error_code &error,
                          const size_t &bytes_transferred, std::string &to_send)
{
  if (error) {
    std::cerr << "Error: " << error.message() << std::endl <<
    bytes_transferred << " bytes transferred." << std::endl;
  } else if (to_send.length() > bytes_transferred && socket.is_open()) {
    to_send.erase(0, bytes_transferred);
    send(to_send);
  }
  if (!socket.is_open()) {
    isAlive = false;
  }
}

void Client::close()
{
  if (socket.is_open()) {
    socket.close();
  }
  isAlive = false;
}
