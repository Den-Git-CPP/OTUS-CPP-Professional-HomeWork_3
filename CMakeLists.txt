cmake_minimum_required(VERSION 3.15)

if ($ENV{GITHUB_RUN_NUMBER})
    project (Allocator VERSION 0.0.$ENV{GITHUB_RUN_NUMBER})
else()
    project (Allocator VERSION 0.0.1)
endif()

configure_file(version.h.in version.h)

add_executable(Allocator_cli 
main_allocator.cpp
allocator.h
fwlist.h
pretty.h
)

set_target_properties(Allocator_cli  
    PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)
target_include_directories(Allocator_cli
    PRIVATE 
    "${CMAKE_BINARY_DIR}"
)

if (MSVC)
    target_compile_options(Allocator_cli 
        PRIVATE
        /W3
    )

else ()
    target_compile_options(Allocator_cli 
        PRIVATE
        -Werror -Wall -Wimplicit-fallthrough -pedantic-errors
    )

endif()

install(TARGETS Allocator_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT madim-neodart@rambler.ru)
include(CPack)

