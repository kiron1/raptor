#=============================================================================
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
# http://www.boost.org/LICENSE_1_0.txt
#=============================================================================

if(BUILD_TESTING AND TARGET boost::unit_test_framework)

    set(_tests
        test_var.cpp
        test_var_stream.cpp
    )

    foreach(_test IN LISTS _tests)
        get_filename_component(_target "${_test}" NAME_WE)
        add_executable(${_target} ${_test})
        target_include_directories(${_target}
            PRIVATE
                $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
        )
        target_link_libraries(${_target}
            PRIVATE
                boost::unit_test_framework
                ${PROJECT_NAME}::b
        )
        add_test(NAME ${_target} COMMAND $<TARGET_FILE:${_target}>)
    endforeach()

endif()

