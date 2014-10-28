CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(initializerlists)
SET(CMAKE_MODULE_PATH ${initializerlists_SOURCE_DIR} ${CMAKE_MODULE_PATH})

FIND_PACKAGE(LATEX REQUIRED)

ADD_EXECUTABLE(container_98
	container_98.cpp
)
SET_TARGET_PROPERTIES(container_98 PROPERTIES
    COMPILE_FLAGS -std=c++98
)

ADD_EXECUTABLE(container_11
	container_11.cpp
)
SET_TARGET_PROPERTIES(container_11 PROPERTIES
    COMPILE_FLAGS -std=c++11
)

ADD_EXECUTABLE(constructor
	constructor.cpp
)
SET_TARGET_PROPERTIES(constructor PROPERTIES
    COMPILE_FLAGS -std=c++11
)

# http://www.cmake.org/Wiki/CMakeUserUseLATEX
INCLUDE(UseLATEX)
ADD_LATEX_DOCUMENT(initializerlists.tex 
    CONFIGURE initializerlists.tex 
    DEFAULT_PDF
)




