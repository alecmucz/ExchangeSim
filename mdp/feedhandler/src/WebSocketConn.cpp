#include "feedhandler/WebSocketConn.h"

#include <iostream>

namespace mdp::feedhandler{

    WebSocketConn::WebSocketConn(std::string host, uint16_t port, std::string path) :
        host{std::move(host)}, port{std::move(port)}, path{std::move(path)},
        ssl_ctx{net::ssl::context::tls_client}{
            ssl_ctx.set_default_verify_paths();
    }

    void WebSocketConn::connect(){
        tcp::resolver resolver{io_ctx};
        beast::get_lowest_layer(ws).connect(    // 3 Way TCP Handshake
            resolver.resolve(host, std::to_string(port)));
        std::cout << "TCP Handshake Established" << std::endl;
        if(! SSL_set_tlsext_host_name(ws.next_layer().native_handle(), host.c_str())){
            throw beast::system_error(
                static_cast<int>(::ERR_get_error()),
                net::error::get_ssl_category());
        }
        ws.next_layer().set_verify_callback(net::ssl::host_name_verification(host));
        ws.next_layer().set_verify_mode(net::ssl::verify_peer);
        ws.next_layer().handshake(net::ssl::stream_base::client);   // SSL/TLS Handshake
        std::cout << "SSL/TLS Handshake Established" << std::endl;
        // ToDo: Replace client decorator
        // ws.set_option(beast::websocket::stream_base::decorator(
        //     [](beast::websocket::request_type& req)
        //     {
        //         req.set(beast::http::field::user_agent,
        //             std::string(BOOST_BEAST_VERSION_STRING) +
        //                 " websocket-client-coro");
        //     }));

        ws.handshake(host, path);   // WebSocket Handshake
        std::cout << "WebSocket Handshake Established" << std::endl;
    }

    void WebSocketConn::send(std::string_view message){
        ws.text(true);
        ws.write(net::buffer(message));
    }

    std::string WebSocketConn::next(){
        buffer.clear();
        ws.read(buffer);
        return beast::buffers_to_string(buffer.data());
    }

    void WebSocketConn::close(){
        try{
            ws.close(beast::websocket::close_code::normal);
        } catch (const beast::system_error& e){
            if (e.code() != net::ssl::error::stream_truncated) throw;
        }
    }
}
