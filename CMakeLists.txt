cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_FLAGS "-std=gnu++11")
project(gearfactory-course)
set(GOOLETESTDIR "third_party/googletest")
add_subdirectory(${GOOLETESTDIR})
enable_testing()

include_directories(
  PUBLIC "${GOOLETESTDIR}/googletest/include"
  # the all header and source
  PUBLIC "bplustree"
)

# bplustree course
add_library(bplustree STATIC "bplustree/bplustree.cc")
add_executable(bplustree_test "tests/bplustree/test.cc")
target_link_libraries(bplustree_test gtest)
add_test(bplustree_test bplustree_test)
# bplustree course