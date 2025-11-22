cmake_minimum_required(VERSION 3.16)

project(hello_world LANGUAGES CXX)

# ---- C++23 standard ----
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ---- Warning flags (cross-platform) ----
function(enable_all_warnings target)
    if (MSVC)
        # MSVC (including clang-cl)
        target_compile_options(${target} PRIVATE
            /W4            # High warning level
            /permissive-   # Stricter standard conformance
            /w44265        # Consistent override warnings
            /w44062        # Switch missing cases
            /w44145        # Implicit conversion warnings
            /WX            # Treat warnings as errors
        )
    else()
        # GCC / Clang
        target_compile_options(${target} PRIVATE
            -Wall
            -Wextra
            -Wpedantic
            -Wconversion
            -Wsign-conversion
            -Wshadow
            -Wimplicit-fallthrough
            -Werror
        )
    endif()
endfunction()

# ---- EXTERNAL LIBS -----
include(FetchContent)

# > ---- MATPLOT ----
# Disable heavy optional stuff in Matplot++
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(MATPLOT_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(MATPLOT_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(MATPLOT_USE_BLAS_LAPACK OFF CACHE BOOL "" FORCE)


FetchContent_Declare(
    matplot
    GIT_REPOSITORY https://github.com/alandefreitas/matplotplusplus.git
    GIT_TAG origin/master
)

FetchContent_MakeAvailable(matplot)

# > ---- CLI11 ----

FetchContent_Declare(
  cli11
  GIT_REPOSITORY https://github.com/CLIUtils/CLI11.git
  GIT_TAG v2.4.2
)
FetchContent_MakeAvailable(cli11)

# Add the CPP files
set(SOURCES src/main.cpp)
add_subdirectory(src/configuration)
add_subdirectory(src/datamodel)
add_subdirectory(src/signalcapturer)
add_subdirectory(src/graphvisualizer)

# ---- Executable ----
add_executable(fastfouriervis ${SOURCES})
# Apply warnings
enable_all_warnings(fastfouriervis)

target_link_libraries(fastfouriervis PRIVATE matplot)
target_link_libraries(fastfouriervis PRIVATE CLI11::CLI11)