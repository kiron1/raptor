#=============================================================================
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
# http://www.boost.org/LICENSE_1_0.txt
#=============================================================================

set(commonsrc
    ${CMAKE_CURRENT_SOURCE_DIR}/info_hash.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/info_hash.cpp
)

add_executable(raptor_mktorrent
    ${CMAKE_CURRENT_SOURCE_DIR}/mktorrent.cpp
    ${commonsrc}
)
add_executable(${PROJECT_NAME}::mktorrent ALIAS raptor_mktorrent)
target_compile_options(raptor_mktorrent
    PRIVATE
        $<$<CXX_COMPILER_ID:Clang>:-stdlib=libc++>
)
target_link_libraries(raptor_mktorrent
    PRIVATE
        $<$<CXX_COMPILER_ID:Clang>:c++>
        ${PROJECT_NAME}::b
        ${PROJECT_NAME}::utility
        boost::program_options
)
set_target_properties(raptor_mktorrent PROPERTIES
    EXPORT_NAME "mktorrent"
)

add_executable(raptor_dumptorrent
    ${CMAKE_CURRENT_SOURCE_DIR}/dumptorrent.cpp
    ${commonsrc}
)
add_executable(${PROJECT_NAME}::mktorrent ALIAS raptor_mktorrent)
target_compile_options(raptor_dumptorrent
    PRIVATE
        $<$<CXX_COMPILER_ID:Clang>:-stdlib=libc++>
)
target_link_libraries(raptor_dumptorrent
    PRIVATE
        $<$<CXX_COMPILER_ID:Clang>:c++>
        ${PROJECT_NAME}::b
        ${PROJECT_NAME}::utility
        boost::program_options
)
set_target_properties(raptor_dumptorrent PROPERTIES
    EXPORT_NAME "dumptorrent"
)


install(TARGETS raptor_mktorrent raptor_dumptorrent EXPORT ${PROJECT_NAME}
    RUNTIME       DESTINATION ${CMAKE_INSTALL_BINDIR}     COMPONENT "${PROJECT_NAME}"
    LIBRARY       DESTINATION ${CMAKE_INSTALL_LIBDIR}     COMPONENT "${PROJECT_NAME}"
    ARCHIVE       DESTINATION ${CMAKE_INSTALL_LIBDIR}     COMPONENT "${PROJECT_NAME}-dev"
    INCLUDES      DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

