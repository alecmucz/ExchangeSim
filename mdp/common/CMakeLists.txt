# Data Schemas
add_library(schemas STATIC)
target_link_libraries(schemas
        PUBLIC
        protobuf::libprotobuf)
target_include_directories(schemas
        PUBLIC
        ${CMAKE_CURRENT_BINARY_DIR})
protobuf_generate(
        TARGET schemas
        PROTOS ${MDP_PROTO_DIR}/marketdata/trade.proto
        IMPORT_DIRS ${MDP_PROTO_DIR}
        PROTOC_OUT_DIR ${CMAKE_CURRENT_BINARY_DIR})