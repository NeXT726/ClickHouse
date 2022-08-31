set(bRPC_INCLUDE_DIRS "${ClickHouse_SOURCE_DIR}/contrib/brpc/include")

add_library(_ch_contrib_brpc INTERFACE)
target_link_libraries(_ch_contrib_brpc INTERFACE brpc-static)
target_include_directories(_ch_contrib_brpc SYSTEM INTERFACE ${bRPC_INCLUDE_DIRS})
add_library(ch_contrib::brpc ALIAS _ch_contrib_brpc)
