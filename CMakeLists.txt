##################################################    Project     ##################################################
cmake_minimum_required(VERSION 3.20)

# Set project name & version
project(magma VERSION 0.1 LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Turn on solution folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include(set_max_warning_level)
set_max_warning_level ()

##################################################    Options     ##################################################
# option(VARIABLE "Descriptor" OFF)
option(BUILD_TEST "Build test executable" OFF)

##################################################    Sources     ##################################################
include_Directories(
  # Main Project files
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_SOURCE_DIR}/source
)

# Lib
file(GLOB SOURCE_LIST
  "${PROJECT_SOURCE_DIR}/include/*.hpp"
  "${PROJECT_SOURCE_DIR}/source/*.cpp"
)

# Test Executable
file(GLOB TEST_SOURCE_LIST
  "${PROJECT_SOURCE_DIR}/test/*.hpp"
  "${PROJECT_SOURCE_DIR}/test/*.cpp"
)

##################################################  Dependencies  ##################################################
# External Dependencies
# Vulkan
find_package(Vulkan REQUIRED)
list(APPEND PROJECT_INCLUDES ${Vulkan_INCLUDE_DIR})
list(APPEND PROJECT_LIBRARIES ${Vulkan_LIBRARIES})

# Submodule Dependencies:
## GLM
add_subdirectory(libraries/glm)
list(APPEND PROJECT_LIBRARIES glm)

## GLFW
add_subdirectory(libraries/glfw)
list(APPEND PROJECT_INCLUDES libraries/glfw/include)
list(APPEND PROJECT_LIBRARIES glfw ${GLFW_LIBRARIES})

# ADD LIBRARIES HERE.
# Examples:
# - Header Only:
#   find_package  (GLM REQUIRED)
#   import_library(GLM_INCLUDE_DIRS)
# - Identical Debug and Release:
#   find_package  (OpenGL REQUIRED)
#   import_library(OPENGL_INCLUDE_DIR OPENGL_LIBRARIES)
# - Separate Debug and Release:
#   find_package  (Boost REQUIRED iostreams)
#   import_library(Boost_INCLUDE_DIRS Boost_IOSTREAMS_LIBRARY_DEBUG Boost_IOSTREAMS_LIBRARY_RELEASE)
# - You may also set the PROJECT_INCLUDE_DIRS and PROJECT_LIBRARIES instead of using import_library.

##################################################    Targets     ##################################################

add_library(magma STATIC ${SOURCE_LIST})

#set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER "Library")

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_INCLUDES} )

target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_LIBRARIES})

# Configure header file to pass version number to source code
#configure_file(configured/MagmaConfig.hpp.in MagmaConfig.hpp)
#
#target_include_directories(magma PUBLIC
#                            "${PROJECT_BINARY_DIR}"
#                          )

# target_compile_definitions(target public/private precompiler-definition)

IF(${BUILD_TEST})
  set(TEST_NAME "HelloTriangle")

  add_executable(${TEST_NAME} ${TEST_SOURCE_LIST})

  set_property(TARGET ${TEST_NAME} PROPERTY FOLDER "Tests")

  target_link_libraries(${TEST_NAME} PRIVATE ${PROJECT_NAME} ${PROJECT_LIBRARIES})
ENDIF()

