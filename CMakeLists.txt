cmake_minimum_required (VERSION 2.6)
project (atacplus)

# The version number.
set (Atacplus_VERSION_MAJOR 0)
set (Atacplus_VERSION_MINOR 1)
set (Atacplus_VERSION_PATCH 0)

# source dir /output dir
set (SRC_DIR "${PROJECT_SOURCE_DIR}/src")
set (TEST_DIR "${PROJECT_SOURCE_DIR}/test")
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# debug
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -std=gnu++03 -Wall -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")
set(VALGRIND /usr/bin/valgrind)
set(VALGRIND_ARGS "--leak-check=full")

# library
find_package(Boost 1.46.1 REQUIRED COMPONENTS unit_test_framework program_options)
find_package(OpenSSL REQUIRED)
find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

# network library
set (Atacplus_network_src
	"${SRC_DIR}/network/DecodingException.cpp"
	"${SRC_DIR}/network/EncodingException.cpp"
	"${SRC_DIR}/network/TacacsPacketHeader.cpp"
	"${SRC_DIR}/network/PreconditionFailException.cpp"
	"${SRC_DIR}/network/crypto.cpp"
	"${SRC_DIR}/network/FixedLengthString.cpp"
        "${SRC_DIR}/network/TacacsPacketContext.cpp"
        "${SRC_DIR}/network/Buffer.cpp"
        "${SRC_DIR}/network/TcpSocket.cpp"
        "${SRC_DIR}/network/BufferedTcpSocket.cpp"
        "${SRC_DIR}/network/TcpClient.cpp"
        "${SRC_DIR}/network/TcpServer.cpp"
        "${SRC_DIR}/network/TacacsPacketAuthentication.cpp"
        "${SRC_DIR}/network/TacacsPacketAuthenticationStart.cpp"
        "${SRC_DIR}/network/TacacsPacketAuthenticationReplay.cpp"
        "${SRC_DIR}/network/TacacsPacketAuthenticationContinue.cpp"
        "${SRC_DIR}/network/TacacsPacketWithHeader.cpp"
)
add_library (atacplus_network ${Atacplus_network_src})
include_directories(${Boost_INCLUDE_DIRS} ${OPENSSL_INCLUDE_DIR} )

# config library
FLEX_TARGET(scanner
        "${SRC_DIR}/config/parser.l"
        "${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/scanner.cpp"
        COMPILE_FLAGS "--header-file=${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/scanner.h")

BISON_TARGET(parser
        "${SRC_DIR}/config/parser.y"
        "${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/parser.cpp"
)

set (Atacplus_config_src
        "${SRC_DIR}/config/ConfigElement.cpp"
        "${SRC_DIR}/config/ConfigSection.cpp"
        "${SRC_DIR}/config/ServerConfigSection.cpp"
        "${SRC_DIR}/config/ConfigElementNotFoundException.cpp"
        "${SRC_DIR}/config/parser.cpp"
        "${SRC_DIR}/config/ParserContext.cpp"
        ${FLEX_scanner_OUTPUTS}
        ${BISON_parser_OUTPUTS}
)
add_library (atacplus_config ${Atacplus_config_src})
target_include_directories(atacplus_config 
        PRIVATE "${SRC_DIR}/config/"
        PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles")

#daemon 
set (Atacplus_daemon_src
        "${SRC_DIR}/daemon/Options.cpp"
        "${SRC_DIR}/daemon/daemonize.cpp"
        "${SRC_DIR}/daemon/main.cpp"
)

add_executable (atacplus
        ${Atacplus_daemon_src}
        )

target_include_directories(atacplus
        PRIVATE "${SRC_DIR}/config/"
        PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles")

target_link_libraries(atacplus
        ${Boost_LIBRARIES}
        atacplus_network
        atacplus_config
        )



#####################################
# testing
#####################################

# unit test
enable_testing()

## network test
set (network_test_files 
	"${TEST_DIR}/network/TacacsPacketHeader.cpp"
	"${TEST_DIR}/network/crypto.cpp"
	"${TEST_DIR}/network/FixedLengthString.cpp"
	"${TEST_DIR}/network/network.cpp"
        "${TEST_DIR}/network/Buffer.cpp"
        "${TEST_DIR}/network/TacacsPacketWithHeader.cpp"
        "${TEST_DIR}/network/TacacsPacketAuthenticationStart.cpp"
        "${TEST_DIR}/network/TacacsPacketAuthenticationReplay.cpp"
        "${TEST_DIR}/network/TacacsPacketAuthenticationContinue.cpp"
        "${TEST_DIR}/network/TcpServer.cpp")

add_executable (test_network_exec
	${network_test_files}
        )

include_directories(${SRC_DIR})
target_link_libraries(test_network_exec 
        atacplus_network
        ${Boost_LIBRARIES} ${OPENSSL_LIBRARIES})

## config test ##
set (config_test_files
        "${TEST_DIR}/config/config.cpp"
        "${TEST_DIR}/config/ConfigElement.cpp"
        "${TEST_DIR}/config/ConfigSection.cpp"
        "${TEST_DIR}/config/parser.cpp")

add_executable (test_config_exec
        ${config_test_files}
        )

target_include_directories(test_config_exec 
        PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles")
target_link_libraries(test_config_exec 
        atacplus_config
        ${Boost_LIBRARIES})


add_test (NAME test_network COMMAND test_network_exec)
add_test (NAME test_config COMMAND test_config_exec)

# valgrind profile
add_custom_target(profile DEPENDS test_network_profile test_config_profile)
add_custom_target(test_network_profile
                  DEPENDS test_network_exec
                  COMMAND ${VALGRIND} ${VALGRIND_ARGS} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test_network_exec VERBATIM)

add_custom_target(test_config_profile
                  DEPENDS test_config_exec
                  COMMAND ${VALGRIND} ${VALGRIND_ARGS} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test_config_exec VERBATIM)
