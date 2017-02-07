cmake_minimum_required (VERSION 2.6)
project (atacplus)
# The version number.
set (Atacplus_VERSION_MAJOR 0)
set (Atacplus_VERSION_MINOR 1)
set (Atacplus_VERSION_PATCH 0)
set (SRC_DIR "${PROJECT_SOURCE_DIR}/src")

set (Atacplus_network_src
	"${SRC_DIR}/network/DecodingException.cpp"
	"${SRC_DIR}/network/EncodingException.cpp"
	"${SRC_DIR}/network/TacacsPacketHeader.cpp"
)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
add_library (atacplus_network ${Atacplus_network_src})
