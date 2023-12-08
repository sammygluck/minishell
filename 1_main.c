#include <minishell.h>

// int	is_char(char to_check, char against);
void free_token_list(t_token **head);
void print_command_table(t_cmd *cmd);
void print_redirections(t_redir *redir);

int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_token *token_head;
	t_env_var *envs;
	t_cmd	*parsed;

	envs = environment_var_handler(env);
	if (argc > 1)
		printf("Minishell: too many arguments\n");
	(void) argv;

	//int i = 0;
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			break ;
		add_history(input);
		//printf("You entered: %s\n", input);
		token_head = tokenizer(input);
		expander(&token_head, envs);
		parsed = parser(token_head);
		print_command_table(parsed);
		//print_list(token_head);
		executor(&parsed, env);
		free(input);
		free_token_list(&token_head);
		//i++;
	}
	return (0);
}



void free_token_list(t_token **head)
{
	t_token *old_head;
	t_token *new_head;

	old_head = *head;
	while (old_head)
	{
		new_head = old_head->next;
		free(old_head->string);
		free(old_head);
		old_head = new_head;
	}
}
//free tokens
//get head of token
//set new head
//free old head and all in it
//do this as long as there is head

// Assuming the definitions of t_redir and t_cmd are given as you provided.

void print_redirections(t_redir *redir) {
    while (redir != NULL) {
        printf("\tType: %d, File: %s\n", redir->type, redir->file);
        redir = redir->next;
    }
}

void print_command_table(t_cmd *cmd) {
    printf("Command Table:\n");
    printf("-------------------------------------------------\n");
    while (cmd != NULL) {
        printf("Command Number: %d\n", cmd->cmd_nr);
        printf("Arguments Count: %d\n", cmd->argc);
        printf("Arguments: ");
        for (int i = 0; i < cmd->argc; ++i) {
            printf("[\"%s\"] ", cmd->argv[i]);
        }
        printf("\nRedirections:\n");
        print_redirections(cmd->redir);
        printf("-------------------------------------------------\n");
        cmd = cmd->next;
    }
}

