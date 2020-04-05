#!/usr/bin/env sh

export VARNAME="my value"
export BUILD_DIR=build
export TARGET="libft_malloc_$(uname -m)_$(uname -s).so"

cmake -B "$(BUILD_DIR)"
cmake -DLIBTARGETNAME=$(TARGET) --build "$(BUILD_DIR)"

