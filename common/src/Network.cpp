#include "Network.hh"

Network::Network(const std::string &ip, const unsigned short &port)
{
  this->endpoint = boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(ip), port);
  isEnding = false;
}

Network::~Network() {}

bool Network::connect()
{
  boost::system::error_code ec;

  socket.begin().base()->connect(endpoint, ec);
  if (ec.message() != "") {
    std::cerr << "Error: " << ec.message() << std::endl;
    return (false);
  }
  return (true);
}

void Network::stopService()
{
  isEnding = true;
  this->ioservice.stop();
}
