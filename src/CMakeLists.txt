#########################################    Executable     ########################################
add_executable(${PROJECT_NAME} ${MAGMA_FILES})

##########################################    Targets     ##########################################
target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${EXTERN_INCLUDES}
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        ${EXTERN_LIBRARIES}
)

# Set the working directory correctly
set_target_properties(${PROJECT_NAME}
  PROPERTIES
    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
)