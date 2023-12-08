# minishell

1- create propmt:
* the form will be (pwd) (user) ($) (cmd + option) (DONE)

2- Parsing command into table:
* read the prompt (DONE)
<!-- * parse the part right after the ($)xm -->
* split the (cmd with spaces and save it an array) (DONE)

3- create builtin:
* echo(read the line and print it in the next line of stdoutput)
* cd(and cd options)
* pwd(current path) (DONE)
* env()

4- implement shortcuts:
* ctr + c
* ctr + d
* ctr + \
* possibility to add arrows (up and down) to navigate in the history table (optional)
* possibility to add arrows (left and right) to move the prompt cursor (optional)

5- implement the pipes with heredoc