CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(DIR_BROWSER)

SET(EXECUTABLE_NAME browsed)

SET(CMAKE_BUILD_TYPE Release)


FILE(GLOB SOURCE *.c)

FILE(GLOB HEADERS *.h)

IF(WIN32)
    MESSAGE(SEND_ERROR "This program is not compatible with Window")
    RETURN()
ENDIF()

# Compiler flags
SET(CMAKE_C_FLAGS " -Wall -Werror -ansi -pedantic -g -std=gnu99 -O2")        ## Optimize

ADD_EXECUTABLE(${EXECUTABLE_NAME} ${SOURCE})

#Install
INSTALL(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)
