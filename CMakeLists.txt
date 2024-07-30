cmake_minimum_required(VERSION 3.5.0)
project(gVCF2tFasta VERSION 1.0.1 LANGUAGES C CXX)

#include(CTest)
#enable_testing()

# Set the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


# Get the current date and time
string(TIMESTAMP CURRENT_DATE "%Y%m%d")
string(TIMESTAMP CURRENT_TIME "%H%M%S")


# Concatenate date and time to create a build number
set(BUILD_NUMBER "${CURRENT_DATE}${CURRENT_TIME}")

# Define the version number
set(VERSION_NUMBER "${gVCF2tFasta_VERSION}")


# Define preprocessor macros for date, time, build number, and version number
add_definitions(-DCURRENT_DATE=\"${CURRENT_DATE}\")
add_definitions(-DCURRENT_TIME=\"${CURRENT_TIME}\")
add_definitions(-DBUILD_NUMBER=\"${BUILD_NUMBER}\")
add_definitions(-DVERSION_NUMBER=\"${VERSION_NUMBER}\")


# Write version number to a text file
file(WRITE "${CMAKE_BINARY_DIR}/version.txt" "${VERSION_NUMBER}")

add_compile_options("-DLOG_USE_COLOR")
IF(CMAKE_BUILD_TYPE MATCHES Debug)
add_compile_options("-DDEBUG")
ENDIF(CMAKE_BUILD_TYPE MATCHES Debug)

# Assuming HTSlib was installed in /usr/local
find_path(HTSLIB_INCLUDE_DIR NAMES htslib/sam.h HINTS /usr/local/include)
find_library(HTSLIB_LIBRARY NAMES hts PATHS /usr/local/lib)

## find htslib on windows NEED TO BE TESTED
if(NOT HTSLIB_INCLUDE_DIR OR NOT HTSLIB_LIBRARY)
  find_path(HTSLIB_INCLUDE_DIR NAMES htslib/sam.h HINTS "C:/Program Files/htslib/include")
  find_library(HTSLIB_LIBRARY NAMES hts PATHS "C:/Program Files/htslib/lib")
endif()
## find htslib on macos NEED TO BE TESTED
if(NOT HTSLIB_INCLUDE_DIR OR NOT HTSLIB_LIBRARY)
  find_path(HTSLIB_INCLUDE_DIR NAMES htslib/sam.h HINTS "/usr/local/Cellar/htslib")
  find_library(HTSLIB_LIBRARY NAMES hts PATHS "/usr/local/Cellar/htslib")
endif()
# /opt/homebrew/opt/htslib
if(NOT HTSLIB_INCLUDE_DIR OR NOT HTSLIB_LIBRARY)
  find_path(HTSLIB_INCLUDE_DIR NAMES htslib/sam.h HINTS "/opt/homebrew/opt/htslib/include")
  find_library(HTSLIB_LIBRARY NAMES hts PATHS "/opt/homebrew/opt/htslib/lib")
endif()
## if not search in  /opt/homebrew/Cellar/htslib/1.20
if(NOT HTSLIB_INCLUDE_DIR OR NOT HTSLIB_LIBRARY)
  find_path(HTSLIB_INCLUDE_DIR NAMES htslib/sam.h HINTS "/opt/homebrew/Cellar/htslib")
  find_library(HTSLIB_LIBRARY NAMES hts PATHS "/opt/homebrew/Cellar/htslib") 
endif()

if(NOT HTSLIB_INCLUDE_DIR OR NOT HTSLIB_LIBRARY)
  message(FATAL_ERROR "Could not find htslib")
endif()

file(GLOB_RECURSE SOURCE_FILE CONFIGURE_DEPENDS "src/*.c*")


## add include directories
include_directories(${HTSLIB_INCLUDE_DIR})

# gVCF2tFasta ${PROJECT_NAME}
add_executable(gVCF2tFasta ${SOURCE_FILE})

target_link_libraries(gVCF2tFasta ${HTSLIB_LIBRARY} )




#add_executable(gecho src/p/gecho.cpp)
#target_include_directories(gecho PRIVATE ${HTSLIB_INCLUDE_DIR})
#target_link_libraries(gecho PRIVATE ${HTSLIB_LIBRARY})

include(CPack)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
install(TARGETS gVCF2tFasta DESTINATION bin)
install(FILES README.md DESTINATION .)
set(CPACK_RESOURCE_FILE_README "${CMAKE_SOURCE_DIR}/README.md")
