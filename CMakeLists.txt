cmake_minimum_required(VERSION 3.15)
project(_fastts_demo LANGUAGES CXX) # change name

# One place to define the Python module name
set(PY_MODULE_NAME _fastts_demo) # change name

# Define name package name
set(PACKAGE_NAME fastts_demo) # change name

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(pybind11 CONFIG QUIET)

# Find homebrew on system intel mac /usr/local/
# If not found, try Homebrew fallback (mac)
if(NOT pybind11_FOUND)
    message(STATUS "pybind11 not found, trying Homebrew prefix...")
    execute_process(
        COMMAND brew --prefix
        OUTPUT_VARIABLE HOMEBREW_PREFIX
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    message(STATUS "Using Homebrew prefix: ${HOMEBREW_PREFIX}")
    set(pybind11_DIR "${HOMEBREW_PREFIX}/lib/cmake/pybind11")
    find_package(pybind11 CONFIG REQUIRED)
endif()

# If still not found, fail with a clear message
if(NOT pybind11_FOUND)
    message(FATAL_ERROR "pybind11 not found. Install it (pip/conda/system) or via Homebrew on macOS.")
endif()

# add module to my script
pybind11_add_module(${PY_MODULE_NAME}

    # (PYBIND11_MODULE + submodules)
    src/module.cpp

    # definitions
    src/functions.cpp

    # bindings
    bindings/bind_functions.cpp)
target_include_directories(${PY_MODULE_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/headers)

# So Clang can find pybind11 for autocomplite
target_link_libraries(${PY_MODULE_NAME} PRIVATE pybind11::module)

# Warnings / optimization depending on compiler
if(MSVC)
    target_compile_options(${PY_MODULE_NAME} PRIVATE /W4)
else()
    target_compile_options(${PY_MODULE_NAME} PRIVATE -Wall -Wextra)
endif()

# ---- IMPORTANT: install the extension into the wheel ----
# This is what makes the compiled .so/.pyd end up inside the wheel.
install(TARGETS ${PY_MODULE_NAME}
    LIBRARY DESTINATION ${PACKAGE_NAME} # Unix-like shared libs / extension modules
    RUNTIME DESTINATION ${PACKAGE_NAME} # Windows .pyd/.dll
    ARCHIVE DESTINATION ${PACKAGE_NAME} # in case of static/archive bits
)
