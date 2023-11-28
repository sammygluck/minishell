#include "minishell.h"

int	executor(t_cmd *ptr)
{
	t_cmd	*current;

	current = ptr;
	while (current->next)
	{
		// check if there is another command after the current one
		if (current->next)
			run_pipe();
		
	}
}