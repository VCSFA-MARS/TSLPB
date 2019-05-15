#!/bin/bash

doxygen Doxyfile

make -f Makefile -C latex clean
make -f Makefile -C latex

open latex/refman.pdf

