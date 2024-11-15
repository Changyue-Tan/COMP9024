#!/bin/bash

# Define the files to store the outputs
OUTPUT1="output_env_vars.txt"
OUTPUT2="output_do_while.txt"

# Run the first command and save the output
make runOne SCC_SRC_FILE=tests/EnvVars.scc > "$OUTPUT1" 2>&1
if [ $? -ne 0 ]; then
    echo "Error: Failed to run 'make runOne SCC_SRC_FILE=tests/EnvVars.scc'"
    exit 1
fi

# Run the second command and save the output
make runOne SCC_SRC_FILE=tests/DoWhile.scc > "$OUTPUT2" 2>&1
if [ $? -ne 0 ]; then
    echo "Error: Failed to run 'make runOne SCC_SRC_FILE=tests/DoWhile.scc'"
    exit 1
fi

# Compare the two outputs
diff "$OUTPUT1" "$OUTPUT2" > diff_result.txt

if [ $? -eq 0 ]; then
    echo "The outputs are identical."
else
    echo "The outputs differ. See 'diff_result.txt' for details."
fi

# Clean up (optional)
rm "$OUTPUT1" "$OUTPUT2"
