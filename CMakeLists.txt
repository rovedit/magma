##########################################    Project     ##########################################
cmake_minimum_required(VERSION 3.20)

# Set project name & version
project(magma VERSION 1.0.0 LANGUAGES "CXX")

# Include directory for CMake modules
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Turn on solution folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Configure compiler warning level
include(set_max_warning_level)
set_max_warning_level ()

##########################################    Options     ##########################################
option(MAGMA_BUILD_DEPENDENCIES "Try to build dependencies that are available in extern folder before looking for system libraries." ON)
option(MAGMA_BUILD_TESTS "Build test executables." OFF)

######################################    Build Settings     #######################################
# Set a default build type if none was specified
# Single-build (Makefiles, ...):
if(NOT DEFINED CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Build everything into top level places
set(BIN_DIR ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_DIR})
set(LIB_DIR ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_DIR})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${BIN_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${BIN_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${BIN_DIR})

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${LIB_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${LIB_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${LIB_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO ${LIB_DIR})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${LIB_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${LIB_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${LIB_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO ${LIB_DIR})

##########################################  Dependencies  ##########################################
# Vulkan
find_package(Vulkan REQUIRED)
list(APPEND EXTERN_INCLUDES ${Vulkan_INCLUDE_DIR})
list(APPEND EXTERN_LIBRARIES ${Vulkan_LIBRARIES})

# GLFW
if(${MAGMA_BUILD_DEPENDENCIES} AND EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/extern/GLFW)
  option(GLFW_BUILD_EXAMPLES OFF)
  option(GLFW_BUILD_TESTS OFF)
  option(GLFW_BUILD_DOCS OFF)
  option(GLFW_INSTALL OFF)
  add_subdirectory(extern/glfw)
  list(APPEND EXTERN_LIBRARIES glfw)
else()
  find_package(GLFW REQUIRED)
endif()

# GLM
if(${MAGMA_BUILD_DEPENDENCIES} AND EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/extern/GLM)
  add_subdirectory(extern/glm)
  list(APPEND EXTERN_LIBRARIES glm)
else()
  find_package(GLM REQUIRED)
endif()

# spdlog
if(${MAGMA_BUILD_DEPENDENCIES} AND EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/extern/spdlog)
  add_subdirectory(extern/spdlog)
  list(APPEND EXTERN_LIBRARIES spdlog)
else()
  find_package(spdlog REQUIRED)
endif()

# Folder grouping
foreach(TARGET_NAME glm glfw spdlog)
  set_property(TARGET ${TARGET_NAME} PROPERTY FOLDER "extern")
endforeach()



###########################################    Files     ###########################################
file(GLOB_RECURSE MAGMA_SOURCES
    "src/*.cc"
    "src/*.hh"
    "data/shaders/*.vert"
    "data/shaders/*.frag"
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${MAGMA_SOURCES})

###########################################  Build magma  ##########################################

add_executable(${PROJECT_NAME} ${MAGMA_SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC src ${EXTERN_INCLUDES})
target_link_libraries(${PROJECT_NAME} PUBLIC ${EXTERN_LIBRARIES})

# Set the working directory correctly
set_target_properties(${PROJECT_NAME}
  PROPERTIES
    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
)

###########################################  Build tests  ##########################################

if(MAGMA_BUILD_TESTS)
  # Gather magmas sources without its entrypoint (main.cc)
  list(APPEND MAGMA_TEST_FILES ${MAGMA_SOURCES})
  list(REMOVE_ITEM  MAGMA_TEST_FILES ${PROJECT_SOURCE_DIR}/src/main.cc)

  # Gather all test scenarios
  file(GLOB TEST_CPPS *.cc)
    foreach(_SOURCE ${TEST_CPPS})
      get_filename_component(_NAME ${_SOURCE} NAME_WE)
      add_executable        (${_NAME} ${_SOURCE})

      target_include_directories(${_NAME}
      PUBLIC
          ${EXTERN_INCLUDES}
      )
      target_link_libraries(${_NAME}
      PUBLIC
          ${EXTERN_LIBRARIES}
      )

      set_property          (TARGET ${_NAME} PROPERTY FOLDER tests)
    endforeach()
endif()
