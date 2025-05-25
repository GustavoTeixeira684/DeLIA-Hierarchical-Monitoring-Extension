cmake_minimum_required (VERSION 3.5)
project (DeLIA 
  VERSION 1.0 
  DESCRIPTION "Library of Fault tolerance")

include(GNUInstallDirs)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to '${DEFAULT_BUILD_TYPE}' as none was specified.")
  set(CMAKE_BUILD_TYPE "${DEFAULT_BUILD_TYPE}" CACHE STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

option (VERBOSE "Enable verbose mode." OFF)

option (TEST "Compile tests" OFF)

# Enable code testing
if(TEST)
  message (STATUS "Setting build with TESTING.")
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DTEST")
endif()

# Enable verbosing
if (VERBOSE)
  message (STATUS "Setting build with VERBOSE.")
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DVERBOSE")
endif ()

# Enable debug options
if (DEBUG)
  message (STATUS "Setting build type to 'Debug'.")
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -DDEBUG")
endif ()

# Enable debug-monitoring-heartbeat-msg options
if (DEBUGHEARTBEATMSG)
  message (STATUS "Setting build type to 'Debug heartbeat msg'.")
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -DDEBUGHEARTBEATMSG")
endif ()

set (LIB_DESTINATION ${PROJECT_NAME}_lib)

add_library(${PROJECT_NAME} STATIC)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -fPIE -std=c++17")

# target_compile_options(libGC PRIVATE -fpie)

file(GLOB SOURCES src/*.cpp libs/jsoncpp/*.cpp)
file(GLOB HEADERS libs/jsoncpp/json/*.h src/*.h)
target_sources(${PROJECT_NAME}
    PRIVATE
      ${SOURCES}
      ${HEADERS}
)
set (DELIA_LIB_DIR "DeLIA")
target_include_directories(${PROJECT_NAME}
    PRIVATE
        # where the library itself will look for its internal headers
        ${CMAKE_CURRENT_SOURCE_DIR}/src
    PUBLIC
        # where top-level project will look for the library's public headers
        $<BUILD_INTERFACE:${${PROJECT_NAME}_lib}/include>
        # where external projects will look for the library's public headers
        $<INSTALL_INTERFACE:${${PROJECT_NAME}_lib}>
)



# set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${HEADERS}")

install(TARGETS ${PROJECT_NAME} DESTINATION ${LIB_DESTINATION})

install(DIRECTORY include/ DESTINATION ${LIB_DESTINATION}/include)

install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}Config
        ARCHIVE  DESTINATION ${LIB_DESTINATION}
        LIBRARY  DESTINATION ${LIB_DESTINATION}
        RUNTIME  DESTINATION ${LIB_DESTINATION})

install(EXPORT ${PROJECT_NAME}Config DESTINATION ${LIB_DESTINATION})

export(TARGETS ${PROJECT_NAME} FILE ${LIB_DESTINATION}/${PROJECT_NAME}Config.cmake)
