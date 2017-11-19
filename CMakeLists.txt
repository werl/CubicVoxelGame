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

# Set Assimp build variables
set(BUILD_SHARED_LIBS           OFF CACHE BOOL "Build Assimp shared library" FORCE)
set(ASSIMP_BUILD_ASSIMP_TOOLS   OFF CACHE BOOL "Build Assimp tools" FORCE)
set(ASSIMP_BUILD_TESTS          OFF CACHE BOOL "Build Assimp tests" FORCE)

# Setup Assimp
add_subdirectory(lib/assimp)
include_directories(lib/assimp/include)

# Find Boost
find_package(Boost 1.65.0 REQUIRED COMPONENTS filesystem system)
include_directories(${Boost_INCLUDE_DIRS})

file(GLOB SOURCE_FILES "src/*.cpp")
file(GLOB HEADRE_FILES "src/*.hpp")
add_executable(TransportConcept2D ${HEADER_FILES} ${SOURCE_FILES})

add_custom_command(TARGET TransportConcept2D POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:TransportConcept2D>/assets)

# Link GLFW
target_link_libraries(TransportConcept2D PUBLIC glfw ${EXTRA_LIBS})
# Link GLBinding
target_link_libraries(TransportConcept2D PUBLIC glbinding)
# Link Assimp
target_link_libraries(TransportConcept2D PUBLIC assimp)
# Link Boost
target_link_libraries(TransportConcept2D PUBLIC ${Boost_LIBRARIES})
