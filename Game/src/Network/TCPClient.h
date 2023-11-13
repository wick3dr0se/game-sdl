#include <iostream>
#include <boost/asio.hpp>

using namespace boost::asio;
using boost::asio::ip::address;
using boost::asio::placeholders::error;
using boost::system::error_code;

class TCPClient {
public:
    TCPClient(io_service& io_service, const std::string& server_address, const std::string& port)
        : m_socket(io_service), m_resolver(io_service), m_server_address(server_address), m_port(port) { }

    void connect() 
    {
        std::cout << "TCPClient connecting" << std::endl;
        ip::tcp::resolver::query query(m_server_address, m_port);
        m_resolver.async_resolve(query, [this](const boost::system::error_code& ec, const boost::asio::ip::tcp::resolver::iterator& iterator) {
            if (!ec) {
                // Successfully resolved the server address. Now, initiate the connection.
                async_connect(m_socket, iterator, [this](const boost::system::error_code& ec, const boost::asio::ip::tcp::resolver::iterator&) {
                    if (!ec) {
                        std::cout << "Connected to the server." << std::endl;
                        // Connection successful, you can perform additional operations here.
                    }
                    else {
                        std::cerr << "Connection error: " << ec.message() << std::endl;
                    }
                    });
            }
            else {
                std::cerr << "Resolution error: " << ec.message() << std::endl;
            }
            });
    }

    void send(const std::string& data) {
        async_write(m_socket, boost::asio::buffer(data),
            [this](const boost::system::error_code& ec, std::size_t) {
                if (!ec) {
                    std::cout << "Data sent successfully." << std::endl;
                }
                else {
                    std::cerr << "Send error: " << ec.message() << std::endl;
                }
            });
    }

    void asyncRead() {
        // Create a buffer to hold the received data
        std::vector<char> buffer(1024);

        // Initiate an asynchronous read operation
        m_socket.async_read_some(boost::asio::buffer(buffer),
            [this, &buffer](const boost::system::error_code& ec, std::size_t bytes_transferred) {
                if (!ec) {
                    std::cout << "Received data: " << std::string(buffer.begin(), buffer.begin() + bytes_transferred) << std::endl;

                    asyncRead();
                }
                else {
                    std::cerr << "Read error: " << ec.message() << std::endl;
                }
            });
    }

    void close() {
        m_socket.close();
    }



private:
    
    

    io_service m_io_service;
    ip::tcp::socket m_socket;
    ip::tcp::resolver m_resolver;
    std::string m_server_address;
    std::string m_port;
    enum { max_length = 1024 };
    char m_reply[max_length];
};
