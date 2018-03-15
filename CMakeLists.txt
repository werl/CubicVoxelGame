cmake_minimum_required(VERSION 3.8)
project(TransportConcept2D)

set(CMAKE_CXX_STANDARD 14)
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
message(STATUS ${GLFW_INCLUDE_DIRS})

# Find GLBinding
find_package(glbinding REQUIRED)
include_directories(${glbinding_INCLUDE_DIRS})
message(STATUS ${glbinding_INCLUDE_DIRS})

# Find Assimp
pkg_search_module(assimp REQUIRED assimp)
include_directories(${assimp_INCLUDE_DIRS})
message(STATUS ${assimp_INCLUDE_DIRS})

# Find Boost
find_package(Boost 1.66.0 REQUIRED COMPONENTS filesystem system container)
include_directories(${Boost_INCLUDE_DIRS})

file(GLOB SOURCE_FILES "src/*.cpp")
file(GLOB HEADRE_FILES "src/*.hpp")
add_executable(TransportConcept2D ${HEADER_FILES} ${SOURCE_FILES})

add_custom_command(TARGET TransportConcept2D POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:TransportConcept2D>/assets)

# Link GLBinding
target_link_libraries(TransportConcept2D PUBLIC glbinding::glbinding)
# Link GLFW
target_link_libraries(TransportConcept2D PUBLIC ${GLFW_STATIC_LIBRARIES} ${EXTRA_LIBS})
message(STATUS ${GLFW_LIBRARIES})
# Link Assimp
target_link_libraries(TransportConcept2D PUBLIC ${assimp_LIBRARIES})
# Link Boost
target_link_libraries(TransportConcept2D PUBLIC ${Boost_LIBRARIES})
