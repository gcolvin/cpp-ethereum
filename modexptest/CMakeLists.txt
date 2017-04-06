aux_source_directory(. SRC_LIST)

add_executable(modexptest ${SRC_LIST})

find_package(Eth)

target_include_directories(modexptest PRIVATE ..)
target_link_libraries(modexptest ${Eth_ETHCORE_LIBRARIES})

install(TARGETS modexptest DESTINATION bin OPTIONAL)
