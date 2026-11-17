# FeedHandler (app)
add_executable(feedhandler main.cpp)
target_include_directories(feedhandler
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(feedhandler
        PRIVATE
        schemas)
target_compile_options(feedhandler
        PRIVATE
        -Wall -Wextra -Wpedantic)