#!/bin/sh
export DYLD_LIBRARY_PATH=.
export DYLD_INSERT_LIBRARIES="libft_malloc.dylib"
export DYLD_FORCE_FLAT_NAMESPACE=1
lldb $@