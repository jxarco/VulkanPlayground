cmake_minimum_required(VERSION 3.13)

# Directories
set(VK_DIR_ROOT       ${CMAKE_CURRENT_LIST_DIR})
set(VK_DIR_LIBRARIES  "${VK_DIR_ROOT}/externals")
set(VK_DIR_SOURCES    "${VK_DIR_ROOT}/src")

project(VulkanApp CXX)

find_package(Vulkan REQUIRED)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "build")

add_subdirectory(libraries/glfw EXCLUDE_FROM_ALL)
add_subdirectory(libraries/glm EXCLUDE_FROM_ALL)

# Sources
macro(VK_FILES_APPEND)
    file(GLOB FILES_APPEND CONFIGURE_DEPENDS ${ARGV})
    list(APPEND VK_SOURCES ${FILES_APPEND})
endmacro()
macro(VK_SOURCES_APPEND)
    VK_FILES_APPEND(${ARGV0}/*.h)
    VK_FILES_APPEND(${ARGV0}/*.cpp)
endmacro()

VK_SOURCES_APPEND(${VK_DIR_SOURCES})

add_executable(${PROJECT_NAME} ${VK_SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${VK_DIR_SOURCES})

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

# vulkan
target_link_libraries(${PROJECT_NAME} ${Vulkan_LIBRARIES})
target_include_directories(${PROJECT_NAME} PUBLIC ${Vulkan_INCLUDE_DIR})

# glfw
target_link_libraries(${PROJECT_NAME} glfw)

# glm
target_link_libraries(${PROJECT_NAME} glm)
