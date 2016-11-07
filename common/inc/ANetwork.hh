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

class ANetwork {
protected:
  boost::asio::io_service                     ioservice;
  bool                                        isEnding;

public:
  ANetwork();
  virtual ~ANetwork();

  // Methods
  virtual void stopService() = 0;
  virtual void read() = 0;
  virtual void write(const void *) = 0;
};

#endif /* !ANETWORK_HH_ */
