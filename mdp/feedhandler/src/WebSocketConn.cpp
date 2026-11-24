#include "feedhandler/WebSocketConn.h"

namespace mdp::feedhandler{

    WebSocketConn::WebSocketConn(std::string host, uint16_t port, std::string path) :
        host{std::move(host)}, port{std::move(port)}, path{std::move(path)},
        ssl_ctx{net::ssl::context::tls_client}{
            ssl_ctx.set_verify_mode(net::ssl::verify_peer);
            ssl_ctx.set_default_verify_paths();
        }
}