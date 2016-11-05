#include "Client.hh"

Client::Client(boost::asio::io_service &ioservice) : socket(ioservice), timer(ioservice, boost::posix_time::seconds(10))
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
  read_buffer.assign(0);
  timer.expires_from_now(boost::posix_time::seconds(1));
  socket.receive(boost::asio::buffer(read_buffer));
  std::string str = std::string(read_buffer.data());
  queue.push(str);
}

void Client::send(const std::string &to_send)
{
  socket.async_send(boost::asio::buffer(to_send),
                    boost::bind(&Client::handle_write, this,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred,
                    to_send));
}

void Client::handle_write(const boost::system::error_code& error,
    const size_t &bytes_transferred, std::string &to_send)
{
  if (error) {
    std::cerr << "Error: " << error.message() << std::endl <<
    bytes_transferred << " bytes transferred." << std::endl;
  } else if (bytes_transferred < to_send.length() && isAlive && socket.is_open()) {
    this->send(to_send.erase(0, bytes_transferred));
  }
  if (!socket.is_open()) {
    isAlive = false;
  }
}

void Client::handle_read(const boost::system::error_code& error)
{
  std::string str = std::string(read_buffer.data());

  if (!error && socket.is_open()) {
    queue.push(str);
    std::cout << str << std::endl;
    if (socket.available() > 0)
      receive();
  } else if (error && socket.is_open()) {
    close();
  }
}

void Client::close()
{
  if (socket.is_open()) {
    socket.close();
  }
  isAlive = false;
}
