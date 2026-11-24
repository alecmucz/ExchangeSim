#pragma once

#include <string>
#include <cstdint>
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/beast/ssl/ssl_stream.hpp>
#include <boost/asio/ssl.hpp>

namespace mdp::feedhandler{
namespace net   = boost::asio;
namespace beast = boost::beast;
using tcp = boost::asio::ip::tcp;

class WebSocketConn{
private:
    std::string host;
    std::uint16_t port;
    std::string path;
    net::io_context io_ctx;
    net::ssl::context ssl_ctx;
    beast::websocket::stream<beast::ssl_stream<beast::tcp_stream>> ws{io_ctx, ssl_ctx};


public:
    WebSocketConn(std::string host, uint16_t port, std::string path);
    void connect();


};
}
