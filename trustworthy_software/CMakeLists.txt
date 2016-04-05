CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(trustworthy_software)
SET(CMAKE_MODULE_PATH ${trustworthy_software_SOURCE_DIR} ${CMAKE_MODULE_PATH})

FIND_PACKAGE(LATEX REQUIRED)


EXECUTE_PROCESS(
    COMMAND ${CMAKE_COMMAND} -E copy ${ipfs_SOURCE_DIR}/borm_logo.jpg ${PROJECT_BINARY_DIR}/borm_logo.jpg
)
EXECUTE_PROCESS(
    COMMAND ${CMAKE_COMMAND} -E copy ${ipfs_SOURCE_DIR}/skype.png ${PROJECT_BINARY_DIR}/skype.png
)

# http://www.cmake.org/Wiki/CMakeUserUseLATEX
INCLUDE(UseLATEX)
ADD_LATEX_DOCUMENT(trustworthy_software.tex 
    CONFIGURE trustworthy_software.tex 
    DEFAULT_PDF
)

