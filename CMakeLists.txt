cmake_minimum_required (VERSION 3.11)


project(lm
  LANGUAGES CXX
  VERSION 0.0.1
)

add_subdirectory(src)

#install(TARGETS lm RUNTIME DESTINATION "bin")
