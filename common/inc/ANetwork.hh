//
// ANetwork.hh for cpp_spider
//
// Made by	Axel Vencatareddy
// Login	vencat_a
//
// Started on	Sun Nov 06 12:08:40 2016 Axel Vencatareddy
// Last update	Sun Nov 06 12:08:40 2016 Axel Vencatareddy
//

#ifndef ANETWORK_HH_
# define ANETWORK_HH_

# include <boost/asio.hpp>
# include <iostream>
# include <mutex>

class ANetwork {
protected:
  boost::asio::io_service ioservice;
  bool                    isEnding;

public:
  ANetwork();
  virtual ~ANetwork();

  // Methods
  virtual void            read(std::mutex &) = 0;
  virtual void            stopService() = 0;
  virtual void            write(const std::string &) = 0;
};

#endif /* !ANETWORK_HH_ */
