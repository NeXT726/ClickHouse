include("${ClickHouse_SOURCE_DIR}/cmake/dbms_glob_sources.cmake")

set(BRPC_TEST_LIBS
    pthread
    ch_contrib::brpc
    /home/ubuntu/third-party/lib/libgflags.a
    OpenSSL::SSL
    ch_contrib::protobuf
)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w")

add_headers_and_sources(clickhouse_cache .)
add_library(clickhouse_cache ${clickhouse_cache_headers} ${clickhouse_cache_sources})
target_link_libraries(clickhouse_cache ${BRPC_TEST_LIBS})
target_include_directories(clickhouse_cache PRIVATE /home/ubuntu/third-party/include)
# target_include_directories(clickhouse_cache PRIVATE ${BORINGSSL_ROOT_DIR}/src/include)

