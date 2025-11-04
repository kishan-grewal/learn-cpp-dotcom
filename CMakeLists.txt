cmake_minimum_required(VERSION 3.15)
project(learn_cpp_dotcom)

# -------------------------------------------------------------
# Basic configuration
# -------------------------------------------------------------
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_COLOR_DIAGNOSTICS ON)   # Enable coloured compiler output

# Strong warnings
if (MSVC)
    add_compile_options(/W4 /permissive-)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

# -------------------------------------------------------------
# Folder exclusions (e.g. sub-projects you manage separately)
# -------------------------------------------------------------
set(EXCLUDE_DIRS
    "projects"
    "sandbox"
    "experiments"
)

# -------------------------------------------------------------
# Recursively find all .cpp files
# -------------------------------------------------------------
file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "*.cpp")

set(_target_count 0)

foreach(source ${SOURCES})
    # Skip any file in excluded directories
    set(skip_file OFF)
    foreach(excluded ${EXCLUDE_DIRS})
        string(FIND "${source}" "${excluded}/" found)
        if(NOT found EQUAL -1)
            set(skip_file ON)
        endif()
    endforeach()
    if(skip_file)
        message(STATUS "Skipping ${source} (excluded folder)")
        continue()
    endif()

    # Skip if the folder has its own CMakeLists.txt
    get_filename_component(dir ${source} DIRECTORY)
    if(EXISTS "${CMAKE_SOURCE_DIR}/${dir}/CMakeLists.txt")
        message(STATUS "Skipping ${source} (local CMakeLists.txt present)")
        continue()
    endif()

    # ---------------------------------------------------------
    # Build only if file contains a real main()
    # ---------------------------------------------------------
    file(READ ${source} contents)
    string(FIND "${contents}" "main(" has_main)
    if(NOT has_main EQUAL -1)
        get_filename_component(target ${source} NAME_WE)
        message(STATUS "Adding target: ${target} (${source})")
        add_executable(${target} ${source})
        math(EXPR _target_count "${_target_count} + 1")
    endif()
endforeach()

# -------------------------------------------------------------
# Summary
# -------------------------------------------------------------
message(STATUS "----------------------------------------")
message(STATUS "Total executables added from throughout: ${_target_count}")
message(STATUS "----------------------------------------")
