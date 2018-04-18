#include <iostream>
#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/thread.hpp>

namespace ip          = boost::asio::ip;
namespace asio        = boost::asio;
namespace this_thread = boost::this_thread;
namespace posix_time  = boost::posix_time;

void read(ip::udp::socket& socket)
{
    ip::udp::endpoint sender;
    std::vector<char> buffer;
    std::size_t bytes_readable = 0;

    while (true) {
        // Poll until data is available.
        while (!bytes_readable) {
            // Issue command to socket to get number of bytes
            // readable.
            asio::socket_base::bytes_readable num_of_bytes_readable(true);
            socket.io_control(num_of_bytes_readable);

            // Get the value from the command.
            bytes_readable = num_of_bytes_readable.get();

            // If there is no data available, then sleep.
            if (!bytes_readable) {
                this_thread::sleep(posix_time::seconds(1));
                buffer.
            }
        }

        // Resize the buffer to store all available data.
        buffer.resize(bytes_readable);

        // Read available data.
        socket.receive_from(asio::buffer(buffer, bytes_readable),
                sender);

        // Extract data from the buffer.
        std::string message(buffer.begin(), buffer.end());

        // Output data.
        std::cout << "Received message: ";
        std::cout << message << std::endl;
    }
}

void write(ip::udp::socket& socket, ip::udp::endpoint& destination)
{
    std::string message;
    for (unsigned int i = 0; i<10; ++i) {
        std::ostringstream stream;
        stream << i;
        message = stream.str();
        socket.send_to(asio::buffer(message), destination);
        std::cout << "Sent message: " << message << std::endl;
    }
}

int main(int argc, char* argv[])
{

    // Extract command-line arguments.
    bool receiver = std::string(argv[1])=="receive";
    ip::address address = ip::address::from_string(argv[2]);
    unsigned short port = boost::lexical_cast<unsigned short>(argv[3]);

    // Create socket.
    asio::io_service service;
    ip::udp::socket socket(service);
    socket.open(ip::udp::v4());

    // Allow other processes to reuse the address, permitting other
    // processes on
    // the same machine to use the multicast address.
    socket.set_option(ip::udp::socket::reuse_address(true));

    // Guarantee the loopback is enabled so that multiple processes on the
    // same
    // machine can receive data that originates from the same socket.
    socket.set_option(ip::multicast::enable_loopback(true));

    socket.bind(ip::udp::endpoint(ip::address_v4::any(), port));
    ip::udp::endpoint destination(address, port);

    // Join group.
    socket.set_option(ip::multicast::join_group(address));

    // Start read or write loops based on command line options.
    if (receiver)
        read(socket);
    else
        write(socket, destination);

    return 0;
}
