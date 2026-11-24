#include "feedhandler/WebSocketConn.h"

namespace mdp::feedhandler{

    WebSocketConn::WebSocketConn(std::string host, uint16_t port, std::string path) :
        host{std::move(host)}, port{std::move(port)}, path{std::move(path)},
        ssl_ctx{net::ssl::context::tls_client}{
            ssl_ctx.set_verify_mode(net::ssl::verify_peer);
            ssl_ctx.set_default_verify_paths();
    }

    void WebSocketConn::connect(){
        tcp::resolver resolver{io_ctx};
        auto const results = resolver.resolve(host, std::to_string(port));
        auto      endpoint = beast::get_lowest_layer(ws).connect(results);  // 3 Way TCP Handshake
        if(! SSL_set_tlsext_host_name(ws.next_layer().native_handle(), host.c_str())){
            throw beast::system_error(
                static_cast<int>(::ERR_get_error()),
                net::error::get_ssl_category());
        }
        ws.next_layer().set_verify_callback(net::ssl::host_name_verification(host));
        ws.next_layer().handshake(net::ssl::stream_base::client);   // SSL/TLS Handshake

        // ToDo: Replace client decorator
        // ws.set_option(beast::websocket::stream_base::decorator(
        //     [](beast::websocket::request_type& req)
        //     {
        //         req.set(beast::http::field::user_agent,
        //             std::string(BOOST_BEAST_VERSION_STRING) +
        //                 " websocket-client-coro");
        //     }));

        ws.handshake(host, path);   // WebSocket Handshake
    }
}
