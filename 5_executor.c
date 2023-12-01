#include <minishell.h>

/*
    command struct
    for each command
        create command struct
            

*/

/*
    redirection logic
    if there's no redirect and no pipes:
        stdin/stdout
    if there are pipes:
        pipe-in/pipe-out
    if there are redirects:
        last redirect of each is the one we'll use
*/

/*
    redirection nodes;

    for each redirection node
        if it's input 
          saved =  opened file
          if permission issue or file doesn't exist
            error: give error + new prompt
        else
            continue;
    
    for each redirection node
        if it's output
            if it's write
                saved = opened new write file
                if error 
                    give error
            if it's append
                saved = open fd in append mode
                if error 
                    give error        
*/

/*
    handle path variables
        if it's absolute
            path = the path
        if it's a relative path
            path = create path based on relative
        if there's no path given
            iterate through the path options

*/

/*
    int pipe[2];
    int fd_in;

    fd_in = STDIN;

    for each command
        if (there is another command)
            create pipe and save to pipe[2];
        fork
        if we're in child
            set up signal handler to get ....
            set correct input fd
                iterate over all input files and set the last one as the acutal fd
            set correct output fd
                iterate over all output files and set the last one as the actual fd
            make sure to close the right fds
            find if command is self_built/relative/absolute path
            execute
            get exit status
*/

/*
    correct input fd

    redir = cmd->redir;
    while (redir)
        try to open file
        if failed to open file
        report
*/
