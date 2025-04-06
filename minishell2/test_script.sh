#!/bin/bash

# Function to run command in both shells and compare results
run_command() {
    echo "Command: $1"
    echo "$1" | tcsh
    echo "tcsh exit status: $?"
    echo "$1" | ./mysh
    echo "./mysh exit status: $?"
    echo ""
}

echo "Running basic commands..."
run_command "ls"
run_command "pwd"
run_command "cd .."
run_command "pwd"

echo "Testing env, setenv, and unsetenv..."
run_command "env"
run_command "setenv TEST_VAR test_value"
run_command "env"
run_command "unsetenv TEST_VAR"
run_command "env"

echo "Testing error handling..."
run_command "nonexistent_command"

echo "Testing exit conditions..."
run_command "exit"
run_command "exit 1"

echo "Testing other commands..."
run_command "echo Hello, World!"
run_command "which ls"
run_command "cat /etc/hosts"

echo "Testing multiple commands..."
run_command "ls"
run_command "pwd"
run_command "echo Done"

echo "Testing input/output redirection..."
run_command "echo Test > test.txt"
run_command "cat test.txt"
run_command "rm test.txt"

echo "Testing background processes..."
run_command "sleep 2"

echo "Testing command substitution..."
run_command 'echo Current directory: `pwd`'
