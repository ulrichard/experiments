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

ADD_EXECUTABLE(named_initializerlists
	named_initializerlists.cpp
)
SET_TARGET_PROPERTIES(named_initializerlists PROPERTIES
    COMPILE_FLAGS -std=c++11
)

ADD_EXECUTABLE(named_initializerlists2
	named_initializerlists2.cpp
)
SET_TARGET_PROPERTIES(named_initializerlists2 PROPERTIES
    COMPILE_FLAGS -std=c++11
)

ADD_EXECUTABLE(std_initializer_list
	std_initializer_list.cpp
)
SET_TARGET_PROPERTIES(std_initializer_list PROPERTIES
    COMPILE_FLAGS -std=c++11
)

ADD_EXECUTABLE(constructor
	constructor.cpp
)
SET_TARGET_PROPERTIES(constructor PROPERTIES
    COMPILE_FLAGS -std=c++11
)
ADD_CUSTOM_COMMAND(TARGET constructor POST_BUILD
    COMMAND constructor
    ARGS > ${PROJECT_BINARY_DIR}/constructor.txt
)

ADD_CUSTOM_COMMAND(TARGET constructor POST_BUILD
    COMMAND ${CMAKE_COMMAND}
    ARGS -E copy ${initializerlists_SOURCE_DIR}/cubx.png ${PROJECT_BINARY_DIR}/cubx.png
)

ADD_EXECUTABLE(realworld98
	realworld98.cpp
)
SET_TARGET_PROPERTIES(realworld98 PROPERTIES
    COMPILE_FLAGS -std=c++98
)

ADD_EXECUTABLE(realworld11lambda
	realworld11lambda.cpp
)
SET_TARGET_PROPERTIES(realworld11lambda PROPERTIES
    COMPILE_FLAGS -std=c++11
)

ADD_EXECUTABLE(realworld11initializerlist
	realworld11initializerlist.cpp
)
SET_TARGET_PROPERTIES(realworld11initializerlist PROPERTIES
    COMPILE_FLAGS -std=c++11
)

# http://www.cmake.org/Wiki/CMakeUserUseLATEX
INCLUDE(UseLATEX)
ADD_LATEX_DOCUMENT(initializerlists.tex 
    CONFIGURE initializerlists.tex 
    DEFAULT_PDF
)

