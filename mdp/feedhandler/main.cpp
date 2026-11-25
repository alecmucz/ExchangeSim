#include <atomic>
#include <csignal>
#include <exception>
#include <iostream>

#include "feedhandler/WebSocketConn.h"

namespace {
    std::atomic<bool> stop_requested{false};
    static_assert(std::atomic<bool>::is_always_lock_free);
    void on_signal(int) { stop_requested.store(true, std::memory_order_relaxed); }
}

int main() {
    std::signal(SIGINT, on_signal);   // Ctrl-C
    std::signal(SIGTERM, on_signal);  // docker stop / kill

    try {
        mdp::feedhandler::WebSocketConn conn{"advanced-trade-ws.coinbase.com", 443, "/"};
        conn.connect();
        conn.send(R"({"type":"subscribe","product_ids":["BTC-USD"],"channel":"heartbeats"})");
        conn.send(R"({"type":"subscribe","product_ids":["BTC-USD"],"channel":"market_trades"})");
        while (!stop_requested) {
            std::cout << conn.next() << '\n';
        }
        conn.close();
        std::cout << "FeedHandler Shutdown" << '\n';
    } catch (const std::exception& e) {
        std::cerr << "feedhandler error: " << e.what() << '\n';
        return 1;
    }
}