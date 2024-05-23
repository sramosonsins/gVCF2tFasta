cmake_minimum_required(VERSION 3.5.0)
project(gVCF2tFasta VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()


add_compile_options("-DLOG_USE_COLOR")
IF(CMAKE_BUILD_TYPE MATCHES DEBUG)
add_compile_options("-DDEBUG")
ENDIF(CMAKE_BUILD_TYPE MATCHES DEBUG)


file(GLOB_RECURSE SOURCE_FILE CONFIGURE_DEPENDS "src/*.c*")
list(FILTER SOURCE_FILE EXCLUDE REGEX "src/p/gecho.cpp")


add_executable(${PROJECT_NAME} ${SOURCE_FILE})

target_link_libraries(${PROJECT_NAME} -lz)

# Assuming HTSlib was installed in /usr/local
find_path(HTSLIB_INCLUDE_DIR NAMES htslib/sam.h HINTS /usr/local/include)
find_library(HTSLIB_LIBRARY NAMES hts PATHS /usr/local/lib)


add_executable(gecho src/p/gecho.cpp)
target_include_directories(gecho PRIVATE ${HTSLIB_INCLUDE_DIR})
target_link_libraries(gecho PRIVATE ${HTSLIB_LIBRARY})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
