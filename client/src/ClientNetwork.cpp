#include  "ClientNetwork.hh"

ClientNetwork::ClientNetwork() : ANetwork(), socket(ioservice)
{

}

ClientNetwork::~ClientNetwork()
{

}

bool ClientNetwork::connect(const std::string &ip, const unsigned short &port)
{
  boost::system::error_code      ec;
  boost::asio::ip::tcp::endpoint endpoint;

  socket.connect(endpoint, ec);
  if (ec) {
    return (false);
  } else {
    return (true);
  }
}

void ClientNetwork::read()
{
  if (!isEnding && socket.available() > 0) {
    read_buffer.assign(0);
    socket.receive(boost::asio::buffer(read_buffer));
    queue.push(static_cast<void *>(read_buffer.c_array()));
  }
}

void ClientNetwork::handle_write(const boost::system::error_code& error,
                          const size_t &bytes_transferred)
{
  if (error) {
    std::cerr << "Error: " << error.message() << std::endl <<
    bytes_transferred << " bytes transferred." << std::endl;
  }
}

void ClientNetwork::write(const void *to_send)
{
  if (socket.is_open()) {
    boost::asio::async_write(socket, boost::asio::buffer(std::string(
                             static_cast<char *>(const_cast<void *>(to_send)))),
                             boost::bind(&ClientNetwork::handle_write,
                             this, boost::asio::placeholders::error,
                             boost::asio::placeholders::bytes_transferred));
  }
}

void ClientNetwork::stopService()
{
  isEnding = true;
  ioservice.stop();
}
