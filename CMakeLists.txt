
# We require at least CMake V2.8.10
cmake_minimum_required(VERSION 2.8.10 FATAL_ERROR)

################################################################################
# project metadata
################################################################################
project(hpx_test)

################################################################################
# Find and Include HPX
################################################################################
if(NOT HPX_DIR)
   #  message("HPX_DIR not set, checking environment variables...")
   #  set(HPX_DIR $ENV{HPX_ROOT}/lib/cmake/hpx)
   #  if(NOT DEFINED HPX_DIR)
   message(FATAL_ERROR "HPX_ROOT not set, unable to find HPX!")
   #  endif()
   #  set(HPX_ROOT /usr/local)
endif()

if(HPX_ROOT AND NOT HPX_DIR)
   set(HPX_DIR "${HPX_ROOT}/lib/cmake/HPX")
endif()

# Instruct cmake to find the HPX settings, it looks for HPXConfig.cmake in ${HPX_DIR}
find_package(HPX)

include_directories(${HPX_INCLUDE_DIR})
link_directories(${HPX_LIBRARY_DIR})

# Adjust auxiliary build settings for HPX to work properly
if(NOT MSVC)
  set(HPX_RPATH ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}${HPX_RPATH})
else()
  # enable solution folders for MSVC
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)
  if(HPX_NO_INSTALL)
    set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/$(Configuration)" CACHE PATH
      "Prefix prepended to install directories." FORCE)
  endif()
endif()

################################################################################
# Additional CMake configuration
################################################################################
set(CMAKE_MODULE_PATH "${HPXIO_SOURCE_DIR}/cmake")

################################################################################
# Build and Create Executable
################################################################################
set (sources
    src/main.cpp)

#set(hello_world_FLAGS COMPONENT_DEPENDENCIES iostreams)

#find_package( LAPACK REQUIRED )
#include_directories(${LAPACK_INCLUDE_DIR})
#
#find_package( BLAS REQUIRED )
#include_directories(${BLAS_INCLUDE_DIR})

add_executable(hpx_test ${sources})
hpx_setup_target(hpx_test)

foreach(dir ${HPX_LIBRARY_DIR})
    target_link_libraries(hpx_test PRIVATE -L${dir})
endforeach()
