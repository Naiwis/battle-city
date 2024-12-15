cmake_minimum_required(VERSION 3.31 FATAL_ERROR)

set(PROJECT_NAME BattleCity)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 11) # change

add_executable(${PROJECT_NAME} src/main.cpp)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)

link_directories(external/glfw/build) # change

# Свяжите ваше приложение с библиотекой GLFW
target_link_libraries(${PROJECT_NAME} PRIVATE glfw ${CMAKE_THREAD_LIBS_INIT})
   
target_include_directories(${PROJECT_NAME} PRIVATE external/glfw/include) # change

add_subdirectory(external/glad)
target_include_directories(${PROJECT_NAME} PRIVATE external/glad/include)
target_link_libraries(${PROJECT_NAME} PRIVATE glad) # private

   