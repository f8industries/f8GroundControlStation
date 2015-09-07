#pragma once

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost\bind.hpp>



#include <qdebug.h>

using boost::asio::ip::udp;

class UdpServer
{
public:
  UdpServer(unsigned short local_port) ;
  ~UdpServer();

private:
  boost::asio::io_service io_service;
  boost::asio::ip::udp::socket socket;
  udp::endpoint server_endpoint;
  udp::endpoint remote_endpoint;
  boost::thread service_thread;
  enum { max_length = 1400 };

  boost::array<char, max_length> buffer_;// deprect local buffer

  void start_receive();
  void handle_receive(const boost::system::error_code& error, std::size_t bytes_transferred);
  void run_service(); 
};

