cmake_minimum_required(VERSION 3.12)

# Directories
set(VK_DIR_ROOT       ${CMAKE_CURRENT_LIST_DIR})
set(VK_DIR_LIBRARIES  "${VK_DIR_ROOT}/externals")
set(VK_DIR_SOURCES    "${VK_DIR_ROOT}/src")
set(VK_SHADERS_DIR    "${VK_DIR_ROOT}/shaders")

project(VulkanApp CXX)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "")

# vulkan
find_package(Vulkan REQUIRED COMPONENTS glslc)
find_program(glslc_executable NAMES glslc HINTS Vulkan::glslc)

# COMPILE SHADERS
file(GLOB SHADERS
  ${VK_SHADERS_DIR}/*.vert
  ${VK_SHADERS_DIR}/*.frag
  ${VK_SHADERS_DIR}/*.comp)

foreach(source IN LISTS SHADERS)
  get_filename_component(FILENAME ${source} NAME)
  add_custom_command(
    COMMAND
      ${glslc_executable}
      -o ${VK_SHADERS_DIR}/${FILENAME}.spv
      ${source}
    OUTPUT ${VK_SHADERS_DIR}/${FILENAME}.spv
    DEPENDS ${source} ${VK_SHADERS_DIR}
    COMMENT "Compiling ${FILENAME}"
  )
  list(APPEND SPV_SHADERS ${VK_SHADERS_DIR}/${FILENAME}.spv)
endforeach()

add_custom_target(Shaders ALL DEPENDS ${SPV_SHADERS})

# enable FetchContent
include(FetchContent)

# download stb_image
FetchContent_Declare(
    stb_image
    URL https://raw.githubusercontent.com/nothings/stb/master/stb_image.h
    DOWNLOAD_DIR ${VK_DIR_SOURCES}
    DOWNLOAD_NO_EXTRACT TRUE
)

# download stb_image
FetchContent_Declare(
    tinyobjloader
    URL https://raw.githubusercontent.com/tinyobjloader/tinyobjloader/release/tiny_obj_loader.h
    DOWNLOAD_DIR ${VK_DIR_SOURCES}
    DOWNLOAD_NO_EXTRACT TRUE
)

# # download texture
# FetchContent_Declare(
#     texture
#     URL https://vulkan-tutorial.com/resources/viking_room.png
#     DOWNLOAD_DIR ${CMAKE_CURRENT_LIST_DIR}/textures
#     DOWNLOAD_NO_EXTRACT TRUE
# )

# # download model
# FetchContent_Declare(
#     model
#     URL https://vulkan-tutorial.com/resources/viking_room.obj
#     DOWNLOAD_DIR ${CMAKE_CURRENT_LIST_DIR}/models
#     DOWNLOAD_NO_EXTRACT TRUE
# )

FetchContent_MakeAvailable(stb_image tinyobjloader) # texture model)

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

add_executable(${PROJECT_NAME} ${VK_SOURCES} ${Shaders})
add_dependencies(${PROJECT_NAME} Shaders)

target_include_directories(${PROJECT_NAME} PUBLIC ${VK_DIR_SOURCES})

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

# vulkan
target_link_libraries(${PROJECT_NAME} ${Vulkan_LIBRARIES})
include_directories(${Vulkan_INCLUDE_DIR})

# glfw
add_subdirectory(libraries/glfw EXCLUDE_FROM_ALL)
target_link_libraries(${PROJECT_NAME} glfw)

# glm
add_subdirectory(libraries/glm EXCLUDE_FROM_ALL)
target_link_libraries(${PROJECT_NAME} glm)