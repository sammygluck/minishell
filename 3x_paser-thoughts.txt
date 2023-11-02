/* 
We've just created our most basic lexer, now let's move on to the parser:
1. We get a linked list with all the parsed words and also indicating the type.
2. We must be able to create commandsd that will be robust in all cases
3. Note, not all cases are success, how bash handles errors is also important
4. Perhaps the trickiest part is to handle edge cases, whose existence might be obscure

One of the ways of building up to more complicated cases, is to begin with easier cases and slowly build on
top of that. So let's give ourselves excercises that reflect that. Let's begin with super simple:
lets start with basic cases
basic case: 
command < infile > outfile

MY_ANSWER:
code: 
while we're iterating over the list
    if the string is <
        take note of the next word, which will be "infile"
        redirect input to infile
    if the string is > 
        take note of the next word,which will be "outfile"
        redirect output to outfile
    if the string is a word
        consider it a command
        all subsequent words until redirect or pipe are considered arguments

result:
command: <command>
in: <infile>
out: <outfile>

execution:
for each command:
    fork the parent
    set the input fd to 'in'
    set the output fd to 'out' (write mode)
    execute with execve
*/