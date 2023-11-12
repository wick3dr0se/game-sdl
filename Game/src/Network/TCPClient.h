#include <iostream>
#include <boost/asio.hpp>

using namespace boost::asio;

class TCPClient {
public:
    TCPClient(io_service& io_service, const std::string& server_address, short port)
        : m_socket(io_service), m_server_address(server_address), m_port(port) {
        doConnect();
    }

    void sendMessage(const std::string& message) {
        io_service_.post([this, message]() {
            doWrite(message);
            std::cout << "Sent Mesasge: " << message << "\n";
        });
    }

private:
    void doConnect() {
        ip::tcp::resolver resolver(io_service_);
        auto endpoints = resolver.resolve({ m_server_address, std::to_string(m_port) });

        async_connect(m_socket, endpoints,
            [this](boost::system::error_code ec, ip::tcp::endpoint /*endpoint*/) {
                if (!ec) {
                    std::cout << "Connected to server\n";
                    doWrite("Hello from client!");
                }
                else {
                    std::cerr << "Connection error: " << ec.message() << "\n";
                }
            }
        );
    }

    void doWrite(const std::string& message) {
        async_write(m_socket, buffer(message),
            [this, message](boost::system::error_code ec, std::size_t /*length*/) {
                if (!ec) {
                    std::cout << "Message sent to server: " << message << "\n";
                    doRead();
                }
                else {
                    std::cerr << "Write error: " << ec.message() << "\n";
                }
            }
        );
    }

    void doRead() {
        async_read(m_socket, buffer(m_reply, max_length),
            [this](boost::system::error_code ec, std::size_t length) {
                if (!ec) {
                    std::cout << "Received reply from server: " << std::string(m_reply, length) << "\n";
                }
                else {
                    std::cerr << "Read error: " << ec.message() << "\n";
                }
            }
        );
    }

    io_service m_io_service;
    ip::tcp::socket m_socket;
    std::string m_server_address;
    short m_port;
    enum { max_length = 1024 };
    char m_reply[max_length];
};
