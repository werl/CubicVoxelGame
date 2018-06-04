cmake_minimum_required(VERSION 3.8)
project(CubicVoxelGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

include_directories(include)

if (APPLE)
    find_library(COCOA Cocoa)
    find_library(OPENGL OpenGL)
    find_library(IOKIT IOKit)
    find_library(COREVIDEO CoreVideo)
    set(EXTRA_LIBS ${COCOA} ${OPENGL} ${IOKIT} ${COREVIDEO})
endif (APPLE)

# Find PkgConfig
find_package(PkgConfig REQUIRED)

# Find GLFW
pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIRS})

# Find GLBinding
find_package(glbinding REQUIRED)
include_directories(${glbinding_INCLUDE_DIRS})

# Find Assimp
find_package(ASSIMP 4.1 REQUIRED)
include_directories(${ASSIMP_INCLUDE_DIRS})

# Find Boost
find_package(Boost 1.66 REQUIRED COMPONENTS system container)
include_directories(${Boost_INCLUDE_DIRS})

file(GLOB SOURCE_FILES "src/*.cpp")
file(GLOB HEADRE_FILES "src/*.hpp")
add_executable(CubicVoxelGame ${HEADER_FILES} ${SOURCE_FILES})

add_custom_command(TARGET CubicVoxelGame POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:CubicVoxelGame>/assets)

# Link GLBinding
target_link_libraries(CubicVoxelGame PUBLIC glbinding::glbinding)
# Link GLFW
target_link_libraries(CubicVoxelGame PUBLIC ${GLFW_STATIC_LIBRARIES} ${EXTRA_LIBS})
# Link Assimp
target_link_libraries(CubicVoxelGame PUBLIC ${ASSIMP_LIBRARIES})
# Link Boost
target_link_libraries(CubicVoxelGame PUBLIC ${Boost_LIBRARIES})
