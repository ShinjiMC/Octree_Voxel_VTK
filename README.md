# Octree with VTK

A simple Octree structure that can build up on the Point Clouds

## Build

```
    mkdir build
    cd build
    cmake -DBUILD_EXAMPLE=ON ..
    cmake --build .
    ./program
```

There are only 2 parameters for CMake at the moment:

```
BUILD_EXAMPLE
SILENCE_DEBUG_OUTPUT
```
