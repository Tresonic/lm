cmake_minimum_required (VERSION 3.11)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(lm
  LANGUAGES CXX
  VERSION 0.0.1
)

add_subdirectory(src)

#install(TARGETS lm RUNTIME DESTINATION "bin")
