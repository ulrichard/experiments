CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(trustworthy_software)
SET(CMAKE_MODULE_PATH ${trustworthy_software_SOURCE_DIR} ${CMAKE_MODULE_PATH})

FIND_PACKAGE(LATEX REQUIRED)

MACRO(CopyFileToBuildDir fileName)
    EXECUTE_PROCESS(
        COMMAND ${CMAKE_COMMAND} -E copy ${trustworthy_software_SOURCE_DIR}/${fileName} ${PROJECT_BINARY_DIR}/${fileName}
    )
ENDMACRO(CopyFileToBuildDir)

CopyFileToBuildDir(borm_logo.jpg)
CopyFileToBuildDir(pointLine_signature.png)
CopyFileToBuildDir(certificate_authority_hierarchies.png)
CopyFileToBuildDir(isp_malware.png)
CopyFileToBuildDir(tor_exit_windows_update.png)
CopyFileToBuildDir(sha1.png)
CopyFileToBuildDir(skype.png)
CopyFileToBuildDir(backdoor_criminals.png)
CopyFileToBuildDir(great_canon.png)
CopyFileToBuildDir(obsolete_signature.png)

# http://www.cmake.org/Wiki/CMakeUserUseLATEX
INCLUDE(UseLATEX)
ADD_LATEX_DOCUMENT(trustworthy_software.tex 
    CONFIGURE trustworthy_software.tex 
    DEFAULT_PDF
)

