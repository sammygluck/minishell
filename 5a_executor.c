/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5a_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteenpu <jsteenpu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 12:32:00 by jsteenpu          #+#    #+#             */
/*   Updated: 2024/01/25 10:27:11 by jsteenpu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_last_exit_code;

static int	handle_command(t_cmd *command, t_fds pipes[2], \
				t_env_var **envs, t_process *p)
{
	if (!p->pipe_count && command->argv \
			&& is_builtin(command->argv))
	{
		p->builtin = 1;
		if (!redirection_check(command, p))
		{
			g_last_exit_code = 1;
			return (0);
		}
		connect_redirections(p);
		g_last_exit_code = execute_builtin(command, p, envs);
	}
	else
		execute_cmd_in_child(command, pipes, p, envs);
	return (1);
}

static void	executor_loop(t_cmd **command, t_env_var **envs, t_process *p)
{
	t_cmd			*current_cmd;
	static t_fds	pipes[2];
	int				std_fds[2];

	current_cmd = *command;
	while (current_cmd)
	{
		save_stdin_out(std_fds);
		if (p->pipe_count && pipe(pipes[CURRENT]) == ERROR)
			exit_error("pipe", 1);
		if (!heredoc_check(current_cmd, p, envs))
			break ;
		signal_handler(PARENT);
		if (!handle_command(current_cmd, pipes, envs, p))
		{
			reset_std_redirection(std_fds, p);
			break ;
		}
		close_pipe_ends(current_cmd, pipes, p);
		swap((int **)pipes);
		reset_std_redirection(std_fds, p);
		current_cmd = current_cmd->next;
	}
}

static t_process	*init_process_struct(char ***env)
{
	t_process	*p;

	p = malloc(sizeof(t_process));
	if (!p)
		return (NULL);
	p->fd_in = -1;
	p->fd_out = -1;
	p->input_redir = 0;
	p->output_redir = 0;
	p->pipe_count = 0;
	p->cmds_count = 0;
	p->builtin = 0;
	p->pid = NULL;
	p->paths = NULL;
	p->envp = *env;
	p->env = env;
	p->heredoc = NULL;
	return (p);
}

t_process	*executor_prep(t_cmd **command, char ***env)
{
	t_process	*p;
	t_cmd		*current_cmd;

	p = init_process_struct(env);
	if (!p)
		return (NULL);
	current_cmd = *command;
	while (current_cmd)
	{
		p->cmds_count = current_cmd->cmd_nr;
		if (current_cmd->next)
			p->pipe_count++;
		current_cmd = current_cmd->next;
	}
	if (p->cmds_count)
	{
		p->pid = malloc(sizeof(pid_t) * p->cmds_count);
		if (!p->pid)
			return (NULL);
	}
	return (p);
}

void	executor(t_cmd **command, char ***env, t_env_var **envs)
{
	t_process	*p;

	if (!command || !*command)
		return ;
	g_last_exit_code = 0;
	p = executor_prep(command, env);
	if (!p)
	{
		free_process(p);
		return ;
	}
	executor_loop(command, envs, p);
	parent_wait(p);
	free_process(p);
}
