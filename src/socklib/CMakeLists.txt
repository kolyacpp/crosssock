set(INCLUDE ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME})
set(SRC ${PROJECT_SOURCE_DIR}/src/${PROJECT_NAME})

set(SOURCES
    ${INCLUDE}/Config.hpp
    ${INCLUDE}/IPAddress.hpp
    ${INCLUDE}/TCPSocket.hpp
    ${INCLUDE}/UDPSocket.hpp
    ${INCLUDE}/Enums.hpp
    ${SRC}/IPAddress.cpp
    ${SRC}/OS.hpp
    ${SRC}/Socket.hpp
    ${SRC}/SocketBase.tpp
    ${SRC}/SocketBase.hpp
    ${SRC}/TCPSocket.cpp
    ${SRC}/UDPSocket.cpp)

if(WIN32)
  set(SOURCES ${SOURCES} ${SRC}/Winsock2/Socket.hpp ${SRC}/Winsock2/Socket.tpp
              ${SRC}/Winsock2/OS.hpp ${SRC}/Winsock2/OS.cpp)
else()
  set(SOURCES ${SOURCES} ${SRC}/Unix/Socket.hpp ${SRC}/Unix/Socket.tpp
              ${SRC}/Unix/OS.hpp ${SRC}/Unix/OS.cpp)
endif()

aux_source_directory(${SRC} SOURCE)
aux_source_directory(${INCLUDE} INCL)
aux_source_directory(${SRC}/Winsock2 WS)

add_library(${PROJECT_NAME} ${SOURCE} ${INCL} ${WS})

if(WIN32)
  target_link_libraries(${PROJECT_NAME} PRIVATE ws2_32)
endif()

target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE}/.. ${SRC}/..)

target_compile_definitions(${PROJECT_NAME} PRIVATE CROSSSOCK_EXPORT NOMINMAX)
