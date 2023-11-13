#pragma once
#include <iostream>
#include "TCPClient.h"

class NetworkManager {
public:
    NetworkManager(boost::asio::io_service& io_service, const std::string& server_address, const std::string& port)
        : m_tcpClient(io_service, server_address, port) 
    {
        std::cout << "initialized network manager." << std::endl;
    }

    void connect()
    {
        std::cout << "Network manager connecting to server." << std::endl;
        m_tcpClient.connect();
    }

    void send(const std::string& objectId, const std::string& type, const std::string& data) {
        auto const msg = objectId + ":" + type + ":" + data + "\n";
        
        m_tcpClient.send(msg);
    }

private:
    TCPClient m_tcpClient;
};