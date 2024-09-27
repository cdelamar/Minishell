#!/bin/bash

# Command list to test, written as a script and piped into the shell.
commands="
ls
ls | wc
dfweewf
ls -l | wc
ls -fwewef | wc
wfefwe | wewef
"

echo "Running minishell tests..."

# Memory leak testing with Valgrind
echo "Running memory leak tests with Valgrind..."
echo "$commands" | valgrind --leak-check=full --show-leak-kinds=all \
    --track-origins=yes --trace-children=yes \
    ./minishell 2>&1 | grep -E "ERROR SUMMARY|Invalid read|Invalid write|definitely lost|indirectly lost"
echo "======================================================="

# Write commands to a file for file-based command test
echo "$commands" > commands.txt

# Run the minishell with commands from the file
echo "Running command tests using input from commands.txt..."
./minishell < commands.txt

# Clean up
rm commands.txt

echo "Tests completed."
