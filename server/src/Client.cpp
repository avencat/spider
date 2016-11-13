#include "Client.hh"

Client::Client(boost::asio::io_service &ioservice, std::condition_variable &cv) : socket(ioservice), cv(cv)
{
  isAlive = true;
  isReading = false;
  state = Client::states::NEW;
}

Client::~Client()
{
  thread.detach();
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

void Client::receive(std::mutex &mtx)
{
  if (isReading)
    return ;
  isReading = true;
  if (thread.joinable())
    thread.join();
  thread = std::thread([&]{Client::do_receive(mtx);});
}

void Client::do_receive(std::mutex &mtx)
{
  std::unique_lock<std::mutex> lock(mtx);
  if (!socket.is_open())
    return ;
  lock.unlock();
  try {
    boost::asio::read_until(socket, buffer, DELIM);
    lock.lock();
    std::istream is(&buffer);
    std::string str;
    std::getline(is, str);
    queue.push(str);
    isReading = false;
    cv.notify_one();
    lock.unlock();
  } catch (const std::exception &error) {
    lock.lock();
    std::cerr << "Exception: " << error.what() << std::endl;
    isAlive = false;
    close();
    isReading = false;
    lock.unlock();
  }
}

void Client::send(const std::string &to_send)
{
  if (!socket.is_open())
    return ;
  boost::asio::async_write(socket, boost::asio::buffer(to_send),
                           boost::bind(&Client::handle_write,
                           this, boost::asio::placeholders::error,
                           boost::asio::placeholders::bytes_transferred,
                           to_send));
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
    socket.cancel();
    socket.close();
  }
  isAlive = false;
}

bool Client::available() const
{
  if (socket.is_open() && socket.available() > 0) {
    return (true);
  } else {
    return (false);
  }
}

bool Client::isOpen() const
{
  available();
  return (socket.is_open());
}

bool Client::is_alive() const
{
  if (!isAlive || !isOpen())
    return (false);
  return (true);
}
