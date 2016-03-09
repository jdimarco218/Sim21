#!/bin/sh

echo "Cleaning files that end with .gcov .gcno .gcda from `pwd`"
rm `find . -name '*.gcov'`
rm `find . -name '*.gcno'`
rm `find . -name '*.gcda'`
echo "Done."
