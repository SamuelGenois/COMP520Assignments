#!/bin/sh

# Use case: run.sh scan|token|parse filename in the root folder
cat $2 | ./minlang $1
