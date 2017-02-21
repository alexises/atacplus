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

# library
find_package(Boost 1.46.1 REQUIRED COMPONENTS unit_test_framework)
find_package(OpenSSL REQUIRED)

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
)
add_library (atacplus_network ${Atacplus_network_src})
include_directories(${Boost_INCLUDE_DIRS} ${OPENSSL_INCLUDE_DIR})

# unit test
enable_testing()
set (network_test_files 
	"${TEST_DIR}/network/TacacsPacketHeader.cpp"
	"${TEST_DIR}/network/crypto.cpp"
	"${TEST_DIR}/network/FixedLengthString.cpp"
	"${TEST_DIR}/network/network.cpp")


add_executable (test_network_exec
	${network_test_files})
include_directories(${SRC_DIR})
target_link_libraries(test_network_exec atacplus_network ${Boost_LIBRARIES} ${OPENSSL_LIBRARIES})

add_test (NAME test_network COMMAND test_network_exec)
