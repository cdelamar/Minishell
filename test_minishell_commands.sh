#!/bin/bash

# Create a file with the commands to be tested
cat <<EOL > commands.txt
ls
ls -lathr
ls | wc
ls -l | wc -l
echo salut > test.txt
cat < test.txt
echo coucou >> test.txt
cat < test.txt
env
export LOUISE=mafille
env
unset LOUISE
env
wc << fin
this is a test
true neutral human fighter
lvl 50
fin
echo effacer > test.txt
cat < test.txt
pwd
cd src
ls
cd ..
lsdfk
exit
EOL

# Run the minishell with the commands from the file
./minishell < commands.txt

# Clean up
rm commands.txt
