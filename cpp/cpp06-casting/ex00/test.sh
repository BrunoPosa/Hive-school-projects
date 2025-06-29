#!/bin/bash

BINARY="./convert"
TEST_FILE="test_values.txt"

clear
if ! make; then
	echo "Error: could not make"
	exit 1;
fi
sleep 2

if [[ ! -x "$BINARY" ]]; then
	echo "Error: $BINARY not found or not executable"
	exit 1
fi

if [[ ! -f "$TEST_FILE" ]]; then
	echo "Error: $TEST_FILE not found"
	exit 1
fi

while IFS= read -r line || [[ -n "$line" ]]; do
	echo ">>> Input: $line"
	$BINARY $line
	echo "----------------------------------------"
	sleep 0.05
done < "$TEST_FILE"

echo "return status: "
echo -n $?

# script does not check for stderr, only stdout
# 