cmake_minimum_required(VERSION 3.10)
project(Octree)
set(CMAKE_CXX_STANDARD 14)

## List of options:
option(BUILD_EXAMPLE "Builds the example" OFF)
option(SILENCE_DEBUG_OUTPUT "Silence debugs" OFF)

# Include directories for header files
include_directories("${CMAKE_CURRENT_LIST_DIR}/Componentes/Octree")
include_directories("${CMAKE_CURRENT_LIST_DIR}/Componentes/Reader")
include_directories("${CMAKE_CURRENT_LIST_DIR}/Componentes/Vec3D")

# List source files for Octree
file(GLOB_RECURSE OCTREE_SRC CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/Components/Octree/*.cpp")
file(GLOB_RECURSE OCTREE_HEADERS CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/Components/Octree/*.hpp")

# List source files for Reader
file(GLOB_RECURSE READER_SRC CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/Components/Reader/*.cpp")
file(GLOB_RECURSE READER_HEADERS CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/Components/Reader/*.hpp")

# List source files for Vec3D
file(GLOB_RECURSE VEC3D_SRC CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/Components/Vec3D/*.cpp")
file(GLOB_RECURSE VEC3D_HEADERS CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/Components/Vec3D/*.hpp")

# Create libraries for Octree, Reader, and Vec3D
add_library(Octree ${OCTREE_SRC} ${OCTREE_HEADERS})
add_library(Reader ${READER_SRC} ${READER_HEADERS})
add_library(Vec3D ${VEC3D_SRC} ${VEC3D_HEADERS})

# Set compile definitions
if(SILENCE_DEBUG_OUTPUT)
    target_compile_definitions(Octree PRIVATE "SILENCE_DEBUG")
    target_compile_definitions(Reader PRIVATE "SILENCE_DEBUG")
    target_compile_definitions(Vec3D PRIVATE "SILENCE_DEBUG")
endif()

# Link libraries as needed
if(BUILD_EXAMPLE)
    add_executable(example "${CMAKE_CURRENT_LIST_DIR}/main.cpp")
    target_link_libraries(example PRIVATE Octree Reader Vec3D)
    set_target_properties(example PROPERTIES OUTPUT_NAME "program")
endif()
