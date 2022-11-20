FILE(GLOB TEST_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.c
)

foreach(file ${TEST_FILES})
    get_filename_component(barefile ${file} NAME_WE)
    # message(STATUS testfile->${barefile})
    add_executable(${barefile} ${file} ${SOURCE_FILE})
    enable_testing()
    target_include_directories(${barefile} PUBLIC ${DEPEN_DIR})
    add_test(NAME ${barefile} COMMAND ${barefile})
    target_link_libraries(${barefile} PUBLIC 
        m
    )
endforeach()
