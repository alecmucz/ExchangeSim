# Library
add_library(mdp_feedhandler
        src/WebSocketConn.cpp
        src/MarketFeed.cpp
        src/FeedConnection.cpp
        include/feedhandler/FeedConnection.h)
target_include_directories(mdp_feedhandler
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(mdp_feedhandler
        PUBLIC Boost::beast OpenSSL::SSL OpenSSL::Crypto schemas)
target_compile_options(mdp_feedhandler
        PRIVATE -Wall -Wextra -Wpedantic)

# Main
add_executable(feedhandler main.cpp)
target_link_libraries(feedhandler
        PRIVATE mdp_feedhandler)
target_compile_options(feedhandler
        PRIVATE -Wall -Wextra -Wpedantic)