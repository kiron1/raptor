#=============================================================================
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
# http://www.boost.org/LICENSE_1_0.txt
#=============================================================================

add_library(raptor_utility
    ${CMAKE_SOURCE_DIR}/include/raptor/char_array.hpp
    ${CMAKE_SOURCE_DIR}/include/raptor/hexdump.hpp
    ${CMAKE_SOURCE_DIR}/include/raptor/sha.hpp
    ${CMAKE_SOURCE_DIR}/include/raptor/file_size.hpp
    ${CMAKE_SOURCE_DIR}/include/raptor/enable_refcount.hpp
    ${CMAKE_SOURCE_DIR}/include/raptor/nullbuf.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/file_size.cpp
)
add_library(${PROJECT_NAME}::utility ALIAS raptor_utility)
target_include_directories(raptor_utility
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}
)
target_compile_options(raptor_utility
    PUBLIC
        $<$<CXX_COMPILER_ID:Clang>:-stdlib=libc++>
)
target_link_libraries(raptor_utility
    PUBLIC
        $<$<CXX_COMPILER_ID:Clang>:c++>
        adobe::source_libraries
)
set_target_properties(raptor_utility PROPERTIES
    EXPORT_NAME "utility"
)

install(TARGETS raptor_utility EXPORT ${PROJECT_NAME}
    RUNTIME       DESTINATION ${CMAKE_INSTALL_BINDIR}     COMPONENT "${PROJECT_NAME}"
    LIBRARY       DESTINATION ${CMAKE_INSTALL_LIBDIR}     COMPONENT "${PROJECT_NAME}"
    ARCHIVE       DESTINATION ${CMAKE_INSTALL_LIBDIR}     COMPONENT "${PROJECT_NAME}-dev"
    INCLUDES      DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

