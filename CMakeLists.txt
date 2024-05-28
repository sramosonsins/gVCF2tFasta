cmake_minimum_required(VERSION 3.5.0)
project(gVCF2tFasta VERSION 0.1.0 LANGUAGES C CXX)

#include(CTest)
#enable_testing()


add_compile_options("-DLOG_USE_COLOR")
IF(CMAKE_BUILD_TYPE MATCHES Debug)
add_compile_options("-DDEBUG")
ENDIF(CMAKE_BUILD_TYPE MATCHES Debug)

# Assuming HTSlib was installed in /usr/local
find_path(HTSLIB_INCLUDE_DIR NAMES htslib/sam.h HINTS /usr/local/include)
find_library(HTSLIB_LIBRARY NAMES hts PATHS /usr/local/lib)

## find htslib on windows
if(NOT HTSLIB_INCLUDE_DIR OR NOT HTSLIB_LIBRARY)
  find_path(HTSLIB_INCLUDE_DIR NAMES htslib/sam.h HINTS "C:/Program Files/htslib/include")
  find_library(HTSLIB_LIBRARY NAMES hts PATHS "C:/Program Files/htslib/lib")
endif()
## find htslib on macos
if(NOT HTSLIB_INCLUDE_DIR OR NOT HTSLIB_LIBRARY)
  find_path(HTSLIB_INCLUDE_DIR NAMES htslib/sam.h HINTS "/usr/local/Cellar/htslib")
  find_library(HTSLIB_LIBRARY NAMES hts PATHS "/usr/local/Cellar/htslib")
endif()


if(NOT HTSLIB_INCLUDE_DIR OR NOT HTSLIB_LIBRARY)
  message(FATAL_ERROR "Could not find htslib")
endif()

file(GLOB_RECURSE SOURCE_FILE CONFIGURE_DEPENDS "src/*.c*")

# gVCF2tFasta ${PROJECT_NAME}
add_executable(gVCF2tFasta ${SOURCE_FILE})

target_link_libraries(gVCF2tFasta ${HTSLIB_LIBRARY} )




#add_executable(gecho src/p/gecho.cpp)
#target_include_directories(gecho PRIVATE ${HTSLIB_INCLUDE_DIR})
#target_link_libraries(gecho PRIVATE ${HTSLIB_LIBRARY})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
