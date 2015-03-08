#=============================================================================
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
# http://www.boost.org/LICENSE_1_0.txt
#=============================================================================

add_library(raptor_b
    ${CMAKE_SOURCE_DIR}/include/raptor/b/detail/generate.hpp
    ${CMAKE_SOURCE_DIR}/include/raptor/b/detail/generator_grammar.hpp
    ${CMAKE_SOURCE_DIR}/include/raptor/b/detail/parse.hpp
    ${CMAKE_SOURCE_DIR}/include/raptor/b/detail/parser_grammar.hpp
    ${CMAKE_SOURCE_DIR}/include/raptor/b/var.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/var.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/var_istream_operator.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/var_ostream_operator.cpp
)
add_library(${PROJECT_NAME}::b ALIAS raptor_b)
target_include_directories(raptor_b
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}
)
target_compile_options(raptor_b
    PUBLIC
        $<$<CXX_COMPILER_ID:Clang>:-stdlib=libc++>
)
target_link_libraries(raptor_b
    PUBLIC
        $<$<CXX_COMPILER_ID:Clang>:c++>
        boost::boost
)
set_target_properties(raptor_b PROPERTIES
    EXPORT_NAME "b"
)

install(TARGETS raptor_b EXPORT ${PROJECT_NAME}
    RUNTIME       DESTINATION ${CMAKE_INSTALL_BINDIR}     COMPONENT "${PROJECT_NAME}"
    LIBRARY       DESTINATION ${CMAKE_INSTALL_LIBDIR}     COMPONENT "${PROJECT_NAME}"
    ARCHIVE       DESTINATION ${CMAKE_INSTALL_LIBDIR}     COMPONENT "${PROJECT_NAME}-dev"
    INCLUDES      DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

