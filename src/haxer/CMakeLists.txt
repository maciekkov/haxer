
INCLUDE_DIRECTORIES(.)

list(APPEND SOURCE_FILES
    ../../haxer.cpp
    socket/SSLConnection.cpp

    )

add_executable(${project_name} ${SOURCE_FILES})
