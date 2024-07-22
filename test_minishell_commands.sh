#!/bin/bash

# Create a file with the commands to be tested
cat <<EOL > commands.txt
ls
ls -lathr
ls | wc
ls -l | wc -l
echo salut > test.txt
cat < test.txt
exit
EOL

# Run the minishell with the commands from the file
./minishell < commands.txt

# Clean up
rm commands.txt
