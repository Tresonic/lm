add_subdirectory(tui)

add_executable(lm main.cpp)

target_link_libraries(${PROJECT_NAME}
    sub::tui
)


#target_include_directories(${PROJECT_NAME} PRIVATE
#    sub::tui
#)

#target_include_directories(lm PRIVATE src)

