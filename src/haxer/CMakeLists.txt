
INCLUDE_DIRECTORIES(.)

list(APPEND SOURCE_FILES
    ../../haxer.cpp
    socket/SSLConnection.cpp


    )
find_library(SSL name  ssl HINTS /usr/lib/x86_64-linux-gnu/)
find_library(THREAD names pthread HINTS /lib/x86_64-linux-gnu/)
find_library(ZMQ names zmq HINTS /lib/x86_64-linux-gnu/)


list(APPEND PROJECT_LIB
    ${SSL}
    ${THREAD}
    ${ZMQ}
    )

add_executable(${PROJECT_NAME} ${SOURCE_FILES} )

target_link_libraries(${PROJECT_NAME} ${PROJECT_LIB})
