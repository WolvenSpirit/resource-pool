#!/bib/bash

# Our homegrown ports file needs to be in a place where vcpkg sees it.
ln -s ${PWD}/resource-pool vcpkg/ports/resource-pool

# Then just use the normal install 
./vcpkg/vcpkg install resource-pool:x64-linux