#!/bin/sh

# Use case: run.sh scan|token|parse|pretty|symbol|typecheck|codegen filename in the root folder
cat $2 | ./minlang $1
