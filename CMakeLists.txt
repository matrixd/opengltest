cmake_minimum_required(VERSION 2.8)

project(opengltest)

FILE(GLOB HeadFiles "./*.hpp")
FILE(GLOB BuildFiles "./*.cpp")

add_custom_target(headers SOURCES ${HeadFiles})

add_executable(${PROJECT_NAME} ${BuildFiles})
target_link_libraries(${PROJECT_NAME} "glfw")
target_link_libraries(${PROJECT_NAME} "GL")
target_link_libraries(${PROJECT_NAME} "GLU")
target_link_libraries(${PROJECT_NAME} "GLEW")

