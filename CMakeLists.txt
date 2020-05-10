cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_FLAGS "-std=gnu++11")
project(gearfactory-course)
set(GOOLETESTDIR "third_party/googletest")
add_subdirectory(${GOOLETESTDIR})
enable_testing()



# Notice! you should open your interested structure test to test your own code

option(BPLUSTREE "open the bplustree test" ON)
option(RBTREE "open the rbtree test" ON)
option(AVLTREE "open the avltree test" ON)
option(HASMAP "open the hashmap test" ON)
option(LINKEDLIST "open the linkedlist test" ON)
option(LRU "open the lru cache test" ON)
option(LFU "open the lfu cache test" ON)
option(HUFFMAN "open the huffman test" ON) 
option(RADIXTREE "open the radixtree test" ON) 
option(TRIE "open trie test" ON)

# Ignore below code , these code is nouse for you to learn
include_directories(
  PUBLIC "${GOOLETESTDIR}/googletest/include"
  # the all header and source
  PUBLIC "bplustree"
  PUBLIC "rbtree"
  PUBLIC "radixtree"
  PUBLIC "lru"
  PUBLIC "lfu"
  PUBLIC "linkedlist"
  PUBLIC "hashmap"
  PUBLIC "huffman"
  PUBLIC "bitset"
  PUBLIC "bloomfilter"
  PUBLIC "trie"
)
if(BPLUSTREE)
  # bplustree lab cmake will generate a executable file bplustree_test 
  # you can run it yourself or let CTest to run automatically
  add_library(bplustree STATIC "bplustree/bplustree.cc")
  add_executable(bplustree_test "tests/bplustree/test.cc")
  target_link_libraries(bplustree_test gtest)
  add_test(bplustree_test bplustree_test)
endif(BPLUSTREE)
