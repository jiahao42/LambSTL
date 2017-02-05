#!/bin/bash

find . | grep -E '^*(\.h|\.cpp)$' | xargs wc -l
