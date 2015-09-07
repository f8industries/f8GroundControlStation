#include "udpServer.h"

#include <exception>


UdpServer::UdpServer(unsigned short local_port) :
    socket(io_service, udp::endpoint(udp::v4(), local_port)),
    service_thread(std::bind(&UdpServer::run_service, this))
{
  qDebug()<<  "starting server on a port: " << local_port;
}


UdpServer::~UdpServer()
{
  io_service.stop();
  service_thread.join();
}

void UdpServer::start_receive()
{
  socket.async_receive_from(boost::asio::buffer(buffer_, max_length), remote_endpoint,
        boost::bind(&UdpServer::handle_receive, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void UdpServer::handle_receive(const boost::system::error_code& error, std::size_t bytes_transferred)
{
    if (!error)
    {
      try{
		  qDebug()<<"packet size is: " << bytes_transferred;
        //meta.size_ = bytes_transferred;
        //vbuffer_->Enqueue(meta);
      }
      catch(std::exception ex) {
        std::cout << "handle_receive: Error parsing incoming message:" << ex.what() <<std::endl;
      }
      catch (...) {
        std::cout << "handle_receive: Unknown error while parsing incoming message"<<std::endl;
        };

    }
    else
    {
       std::cout << "handle_receive: error: " << error.message() <<std::endl;
    }
    
    
    start_receive();
}

void UdpServer::run_service()
{
    start_receive();
    while (!io_service.stopped()){
        try {
            io_service.run();
        } catch( const std::exception& e ) {
            std::cout << "Server network exception: " << e.what() <<std::endl;
        }
        catch(...) {
          std::cout << "Unknown exception in server network thread" << std::endl;
        }
    }
    std::cout << "Server network thread stopped" << std::endl;
};

