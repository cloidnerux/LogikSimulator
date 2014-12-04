Project(LogikSimulator)
cmake_minimum_required(VERSION 2.8.2)

SET(LogiSim_BIN_DIR bin)
SET(LogiSim_LIB_DIR lib)

SET(LIBRARY_OUTPUT_PATH    ${PROJECT_SOURCE_DIR}/${LogiSim_LIB_DIR})
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/${LogiSim_BIN_DIR})

SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_BINARY_DIR}/${LogiSim_BIN_DIR})
SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/${LogiSim_BIN_DIR})
SET( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${PROJECT_BINARY_DIR}/${LogiSim_LIB_DIR})
SET( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/${LogiSim_LIB_DIR})

SET(CMAKE_DEBUG_POSTFIX "d")

set(CMAKE_CXX_FLAGS "-std=c++11")

#SET(mainsrc src/main.cpp)

#
file(GLOB LogiSim_SRC "${PROJECT_SOURCE_DIR}/src/*")

file(GLOB LogiSim_HEADER "${PROJECT_SOURCE_DIR}/include/*")

INCLUDE_DIRECTORIES(
${PROJECT_SOURCE_DIR}/include 
)
Option(BuildApplication "Soll die Application gebaut werden" ON)


IF (BuildApplication MATCHES "ON")
MESSAGE("Building Application")

SET(LogiSimSource ${LogiSim_SRC} ${LogiSim_HEADER})

ADD_EXECUTABLE(LogiSim ${LogiSimSource})
#SET_TARGET_PROPERTIES(LogiSim PROPERTIES LINKER_LANGUAGE C++)
set_target_properties( LogiSim PROPERTIES DEBUG_POSTFIX "d" )


Target_LINK_LIBRARIES(LogiSim)

# install executable
install_targets (/bin LogiSim)
ENDIF(BuildApplication MATCHES "ON")
