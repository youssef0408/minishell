#!/usr/bin/expect -f

set timeout 2
set prompt "\(minishell\) \$"

# Start minishell with valgrind
spawn make all
spawn valgrind --leak-check=full --suppressions:supp.txt ./minishell

# Wait for the prompt to appear
expect -re $prompt

# send "echo 'Hello, Minishell!'\r"
# expect -re $prompt
send "\'l\'s\r"
expect -re $prompt

send "l\"s\"\r"
expect -re $prompt

send "\'e\'c\"h\"o allo \t \r"
expect -re $prompt

send "echo \\\"Hello, World!\\\" | tr 'A-Z' 'a-z' | rev >> 1.tst \r"
expect -re $prompt

send "exit\r"
expect eof
