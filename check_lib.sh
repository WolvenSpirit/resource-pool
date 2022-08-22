#!/bin/bash

# Debugging missing symbols

readelf -s build/libresource-pool.a # | grep Pool

objdump -aTtRr build/libresource-pool.a 