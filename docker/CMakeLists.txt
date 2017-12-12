CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(docker)
SET(CMAKE_MODULE_PATH ${docker_SOURCE_DIR} ${CMAKE_MODULE_PATH})

FIND_PACKAGE(LATEX REQUIRED)

MACRO(CopyFileToBuildDir fileName)
    EXECUTE_PROCESS(
        COMMAND ${CMAKE_COMMAND} -E copy ${docker_SOURCE_DIR}/${fileName} ${PROJECT_BINARY_DIR}/${fileName}
    )
ENDMACRO(CopyFileToBuildDir)

CopyFileToBuildDir(borm_logo.jpg)
CopyFileToBuildDir(pGYAg7TMmp0.png)

# download the video
IF(NOT EXISTS "${PROJECT_BINARY_DIR}/pGYAg7TMmp0.webm")
    EXECUTE_PROCESS(COMMAND youtube-dl -o pGYAg7TMmp0.webm pGYAg7TMmp0)
ENDIF()

# http://www.cmake.org/Wiki/CMakeUserUseLATEX
INCLUDE(UseLATEX)
ADD_LATEX_DOCUMENT(docker.tex 
    CONFIGURE docker.tex 
    DEFAULT_PDF
)

