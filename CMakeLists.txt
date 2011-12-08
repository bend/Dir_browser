cmake_minimum_required(VERSION 2.6)

PROJECT(DIR_BROWSER)

SET(EXECUTABLE_NAME browsed)

SET(CMAKE_BUILD_TYPE Release)

ADD_DEFINITIONS(
    -Wall
    -Werror
    -ansi 
    -pedantic
    )
FILE(GLOB SOURCE *.c)

FILE(GLOB HEADERS *.h)

IF(WIN32)
    MESSAGE(SEND_ERROR "This program is not compatible with Window")
    return()
ENDIF()

# Compiler flags
if(CMAKE_COMPILER_IS_GNUC)
    set(CMAKE_C_FLAGS "-O2")        ## Optimize
endif()

ADD_EXECUTABLE(${EXECUTABLE_NAME} ${SOURCE})

#Install
INSTALL(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)
