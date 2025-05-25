cmake_minimum_required (VERSION 3.5)
project (FT_EXAMPLE)

set (libGC_FILES
  GDClass.cpp
  Settings.cpp)
add_library (libGC STATIC ${libGC_FILES})

find_package (MPI QUIET)
if (NOT MPI_CXX_FOUND)
  message (FATAL_ERROR "MPI must exist to compile.")
else ()
  message (STATUS "MPI ${MPI_CXX_VERSION} found & enabled.")
endif ()
separate_arguments(MPI_CXX_COMPILE_FLAGS)

target_include_directories (libGC PUBLIC ${MPI_CXX_INCLUDE_DIRS} )
target_compile_options (libGC PUBLIC ${MPI_CXX_COMPILE_FLAGS})
target_link_libraries (libGC ${MPI_CXX_LIBRARIES})

# ======================================
# Necessary part to use the FT library
if (DELIA)
  find_package(DeLIA QUIET)
  if (NOT TARGET DeLIA)
    message (FATAL_ERROR "Without using DeLIA.")
  else ()
    message (STATUS "Using DeLIA")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DFT")
    find_path(DeLIA_INCLUDE 
      "DeLIA.h"
      PATHS ${PROJECT_SOURCE_DIR}/DeLIA_lib/include/
      NO_CMAKE_FIND_ROOT_PATH
    )
    if (NOT DeLIA_INCLUDE)
        message(FATAL_ERROR "Can't find DeLIA_lib/include")
    else ()
      message(STATUS "Find ${PROJECT_SOURCE_DIR}")
      include_directories(${PROJECT_SOURCE_DIR}/DeLIA_lib/include/)
    endif()
  endif ()
endif ()
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -fPIE")
# ======================================

# Enable debug options
if (DEBUG)
  message (STATUS "Setting build type to 'Debug'.")
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -pg -DDEBUG")
endif ()

add_executable (EXEC_TEST Main.cpp)


# ======================================
# Necessary part to use the FT library
target_link_libraries(libGC DeLIA)
# ======================================

target_link_libraries (EXEC_TEST libGC)
install (TARGETS EXEC_TEST DESTINATION bin)