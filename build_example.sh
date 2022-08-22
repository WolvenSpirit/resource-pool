#!/bin/bash

# If the library fails to link then run the test file and see if this links.
# If example links then it's CMake config issue, if it doesn't then the library has a missmatch between header and  symbols in library.

g++ example/main.cpp -Lbuild -lresource-pool -o main