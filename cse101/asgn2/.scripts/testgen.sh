#!/bin/bash

MYDIR="$(dirname $0)"
EXIT=0

# Make a temp directory
DIR=$(mktemp)
rm $DIR
mkdir $DIR
[[ $? -ne 0 ]] && exit 1
echo Using temporary directory $DIR

# Generate examples in that dir
echo Attempting to generate same examples
"$MYDIR/mkexamples.sh" $DIR

# Check ppm images for exact matches besides whitespace
echo Checking images
for file in ./examples/*.ppm; do
    BASE=$(basename $file)
    diff -bB "./examples/$BASE" "$DIR/$BASE" 2>&1 >/dev/null
    [[ $? -ne 0 ]] && echo Failure in test $BASE && EXIT=1
done

# Check serialized dump for diffs after sorting
# NOTE: If you print UP/LEFT edges, this test will fail
# NOTE: Whitespace must be exact
echo Checking serialized files
for file in ./examples/*.dat; do
    BASE=$(basename $file)
    diff <(sort "./examples/$BASE") <(sort "$DIR/$BASE") 2>&1 >/dev/null
    [[ $? -ne 0 ]] && echo Failure in test $BASE && EXIT=1
done

exit $EXIT

