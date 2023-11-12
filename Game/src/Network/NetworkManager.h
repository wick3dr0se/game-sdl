#pragma once
#include <iostream>
#include "TCPClient.h"

class NetworkManager {
public:
    NetworkManager(boost::asio::io_service& io_service, const std::string& server_address, short port)
        : m_tcpClient(io_service, server_address, port) {}

    void sendData(const std::string& data) {
        m_tcpClient.sendMessage(data);
    }

private:
    TCPClient m_tcpClient;
};