###########################################    Tests     ###########################################
if(MAGMA_BUILD_TESTS)

file(GLOB TEST_CPPS *.cc)
  foreach(_SOURCE ${TEST_CPPS})
    get_filename_component(_NAME ${_SOURCE} NAME_WE)
    add_executable        (${_NAME} ${_SOURCE} ${MAGMA_FILES})
    set_property          (TARGET ${_NAME} PROPERTY FOLDER tests)
  endforeach()
endif()