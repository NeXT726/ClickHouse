set(bRPC_INCLUDE_DIRS "${ClickHouse_SOURCE_DIR}/contrib/brpc/include")

set(_brpc_SOURCE_DIR "${ClickHouse_SOURCE_DIR}/contrib/brpc")
set(_bRPC_BINARY_DIR "${ClickHouse_BINARY_DIR}/contrib/brpc")

set(_bRPC_PROTOBUF_LIBRARIES ch_contrib::protobuf)


set(_brpc_PROTOBUF_INCLUDE_DIR "${ClickHouse_SOURCE_DIR}/contrib/protobuf/src")
set(_bRPC_PROTOBUF_PROTOC_EXECUTABLE $<TARGET_FILE:protoc>)

set(_bRPC_PROTOC_LIB ch_contrib::protoc)

set(_bRPC_GFLAGS_LIBRARY /home/ubuntu/third-party/lib/libgflags.so)
set(_bRPC_GFLAGS_INCLUDE_PATH /home/ubuntu/third-party/include)

set(_bRPC_OPENSSL_CRYPTO_LIBRARY OpenSSL::SSL)
set(_bRPC_OPENSSL_INCLUDE_DIR "${ClickHouse_SOURCE_DIR}/contrib/boringssl/include")

find_path(_bRPC_LEVELDB_INCLUDE_PATH NAMES leveldb/db.h)
find_library(_bRPC_LEVELDB_LIB libleveldb.a /usr/lib/x86_64-linux-gnu/)
if ((NOT _bRPC_LEVELDB_INCLUDE_PATH) OR (NOT LEVELDB_LIB))
    message(FATAL_ERROR "Fail to find leveldb")
endif()

add_subdirectory("${_brpc_SOURCE_DIR}" "${_bRPC_BINARY_DIR}")

add_library(_ch_contrib_brpc INTERFACE)
target_link_libraries(_ch_contrib_brpc INTERFACE brpc-static)
target_include_directories(_ch_contrib_brpc SYSTEM INTERFACE ${bRPC_INCLUDE_DIRS})
add_library(ch_contrib::brpc ALIAS _ch_contrib_brpc)
