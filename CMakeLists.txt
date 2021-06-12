cmake_minimum_required(VERSION 3.10)

project(Audiotest C)

add_subdirectory(lib/portaudio EXCLUDE_FROM_ALL)

add_library(sas src/data.c)

add_executable(${PROJECT_NAME} src/main.c "src/data.c")
target_link_libraries(${PROJECT_NAME} sas)

target_link_libraries(${PROJECT_NAME} portaudio_static)

install(TARGETS ${PROJECT_NAME})
