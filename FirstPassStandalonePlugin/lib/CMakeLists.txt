add_library(helloworld SHARED helloworld.cpp)
target_include_directories(helloworld PRIVATE ${CMAKE_SOURCE_DIR}/include)
