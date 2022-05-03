project(tui)

find_package(Threads REQUIRED)

file(GLOB SRC_FILES *.cpp)

add_library(${PROJECT_NAME} ${SRC_FILES})
add_library(sub::tui ALIAS ${PROJECT_NAME})

target_include_directories( ${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}
)

target_link_libraries(tui PRIVATE Threads::Threads)
