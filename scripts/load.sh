#!/bin/sh
# generate manual pages, and Makefiles.

cat src/libfilter.h examples/strings.c     | \
    docgen-extractor-c                     | \
    docgen-compiler-c                      | \
    docgen-backend-manpage --section cware --date "`date +'%B %d, %Y'`" --title "C-Ware Manuals"

m4 -Itemplate template/Makefile.m4 > Makefile
