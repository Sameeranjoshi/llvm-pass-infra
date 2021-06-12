add_library(legacyhelloworld SHARED legacyhelloworld.cpp)
target_include_directories(legacyhelloworld PRIVATE ${CMAKE_SOURCE_DIR}/include)

add_library(newpmhelloworld SHARED newpmhelloworld.cpp)
target_include_directories(newpmhelloworld PRIVATE ${CMAKE_SOURCE_DIR}/include)
