cmake_minimum_required(VERSION 3.8)
project(TransportConcept2D)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

if (APPLE)
    find_library(COCOA Cocoa)
    find_library(OPENGL OpenGL)
    find_library(IOKIT IOKit)
    find_library(COREVIDEO CoreVideo)
    set(EXTRA_LIBS ${COCOA} ${OPENGL} ${IOKIT} ${COREVIDEO})
endif (APPLE)

# Set GLFW build variables
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Build GLFW examples" FORCE)
set(GLFW_BUILD_TESTS    OFF CACHE BOOL "Build GLFW tests" FORCE)
set(GLFW_BUILD_DOCS     OFF CACHE BOOL "Build GLFW docs" FORCE)
set(GLFW_INSTALL        OFF CACHE BOOL "Generate GLFW instilation target" FORCE)

# Setup GLFW
add_subdirectory(lib/glfw)
include_directories(lib/glfw/include)

# Set GLBinding build variables
set(BUILD_SHARED_LIBRARIES  OFF CACHE BOOL "Build GLBinding shared library" FORCE)
set(OPTION_BUILD_TESTS      OFF CACHE BOOL "Build GLBinding tests" FORCE)
set(OPTION_BUILD_GPU_TESTS  OFF CACHE BOOL "Build GLBinding tests that require a GPU" FORCE)
set(OPTION_BUILD_DOCS       OFF CACHE BOOL "Build GLBinding docs" FORCE)
set(OPTION_BUILD_TOOLS      OFF CACHE BOOL "Build GLBinding tools" FORCE)

# Setup GLBinding
add_subdirectory(lib/glbinding)
include_directories(lib/glbinding/sources/include)

# Set cppfs build variables
set(BUILD_SHARED_LIBS   OFF CACHE BOOL "Build cppfs shared library" FORCE)
set(OPTION_BUILD_TESTS  OFF CACHE BOOL "Build cppfs tests" FORCE)

# Setup cppfs
#add_subdirectory(lib/cppfs)
#include_directories(lib/cppfs/source/cppfs/include)


file(GLOB SOURCE_FILES "src/*.cpp")
file(GLOB HEADRE_FILES "src/*.hpp")
add_executable(TransportConcept2D ${HEADER_FILES} ${SOURCE_FILES})

# Link GLFW
target_link_libraries(TransportConcept2D PUBLIC glfw ${EXTRA_LIBS})
# Link GLBinding
target_link_libraries(TransportConcept2D PUBLIC glbinding)
# Link cppfs
#target_link_libraries(TransportConcept2D PUBLIC cppfs)
