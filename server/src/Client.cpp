#include "Client.hh"

Client::Client(boost::asio::io_service &ioservice) : socket(ioservice)
{
  isAlive = true;
}

Client::~Client()
{

}

void Client::setId(const int &new_id)
{
  this->id = new_id;
}

const int &Client::getId() const
{
  return (this->id);
}

const std::queue<void *> &Client::getQueue() const
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
  read_buffer.assign(0);
  socket.receive(boost::asio::buffer(read_buffer));
  queue.push(static_cast<void *>(read_buffer.c_array()));
}

void Client::send(const void *to_send)
{
  boost::asio::async_write(socket, boost::asio::buffer(std::string(
                           static_cast<char *>(const_cast<void *>(to_send)))),
                           boost::bind(&Client::handle_write,
                           this, boost::asio::placeholders::error,
                           boost::asio::placeholders::bytes_transferred));
}

void Client::handle_write(const boost::system::error_code& error,
                          const size_t &bytes_transferred)
{
  if (error) {
    std::cerr << "Error: " << error.message() << std::endl <<
    bytes_transferred << " bytes transferred." << std::endl;
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
