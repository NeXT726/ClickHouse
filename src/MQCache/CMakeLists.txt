PROTOBUF_GENERATE_GRPC_CPP(helloworld_sources helloworld_headers helloworld.proto)

include("${ClickHouse_SOURCE_DIR}/cmake/dbms_glob_sources.cmake")

# Ignore warnings while compiling protobuf-generated *.pb.h and *.pb.cpp files.
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w")

# Disable clang-tidy for protobuf-generated *.pb.h and *.pb.cpp files.
set (CMAKE_CXX_CLANG_TIDY "")

add_headers_and_sources(clickhouse_cache .)
add_library(clickhouse_cache ${clickhouse_cache_headers} ${clickhouse_cache_sources} ${helloworld_sources} ${helloworld_headers})

target_include_directories(clickhouse_cache SYSTEM PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries (clickhouse_cache PUBLIC ch_contrib::grpc)

