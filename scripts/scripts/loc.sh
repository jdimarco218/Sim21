#!/bin/sh

echo "Lines of source code in `pwd`: "
cat `find . -name '*.cpp'` `find . -name '*.h'` | grep -v '^$' | wc | awk '{print $1}'
