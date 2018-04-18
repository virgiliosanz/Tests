//
// receiver.cpp
// ~~~~~~~~~~~~
//
// Copyright (c) 2003-2014 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <string>

namespace io = boost::asio;
namespace ip = boost::asio::ip;
namespace sys = boost::system;

const short multicast_port = 3937;
const char* multicast_group = "239.0.2.129";

class receiver {

  public:
    receiver(io::io_service& io_service, const ip::address& listen_address,
             const ip::address& multicast_address, const short port)
        : socket_(io_service)
    {
        // Create the socket so that multiple may be bound to the same
        // address.
        ip::udp::endpoint listen_endpoint(listen_address, port);
        socket_.open(listen_endpoint.protocol());
        socket_.set_option(ip::udp::socket::reuse_address(true));
        socket_.bind(listen_endpoint);

        // Join the multicast group.
        socket_.set_option(ip::multicast::join_group(multicast_address));

        socket_.async_receive_from(
            io::buffer(data_, max_length), sender_endpoint_,
            boost::bind(&receiver::handle_receive_from, this,
                        io::placeholders::error,
                        io::placeholders::bytes_transferred));
    }

    void handle_receive_from(const sys::error_code& error, size_t bytes_recvd)
    {

        if (!error) {
            std::cout.write(data_, bytes_recvd);
            std::cout << std::endl;

            socket_.async_receive_from(
                io::buffer(data_, max_length), sender_endpoint_,
                boost::bind(&receiver::handle_receive_from, this,
                            io::placeholders::error,
                            io::placeholders::bytes_transferred));
        }
    }

  private:
    ip::udp::socket socket_;
    ip::udp::endpoint sender_endpoint_;
    enum { max_length = 1024 };
    char data_[max_length];
};

int main()
{
    try {
        io::io_service io_service;
        receiver r(io_service, ip::address::from_string("0.0.0.0"),
                   ip::address::from_string(multicast_group), multicast_port);
        io_service.run();
    }
    catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
