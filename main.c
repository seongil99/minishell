/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 13:49:19 by seonyoon          #+#    #+#             */
/*   Updated: 2024/03/04 09:35:47 by sihkang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_code;

void	check(void)
{
	system("leaks minishell");
}

void	minishell_pre_process(t_env_lst *envlst, char **envp, \
							struct termios *org_term)
{
	g_exit_code = 0;
	init_action_tablev2();
	init_goto_tablev2();
	printf("WELCOME MINISHELL !\n");
	save_input_mode(org_term);
	init_env_lst(envlst, envp);
}

void	minishell_line_clear(char *line, t_cmd_lst *cmd_lst, t_lst *tkn_lst)
{
	add_history(line);
	rl_replace_line("\n", 1);
	rl_on_new_line();
	clear_lst(cmd_lst);
	cmd_lst = 0;
	free(line);
	lst_clear(&tkn_lst, token_del);
	line = 0;
}

typedef struct s_data
{
	int				parse_code;
	char			*line;
	t_lst			*tkn_lst;
	t_cmd_lst		*cmd_lst;
	t_env_lst		envlst;
}	t_data;

void	exec(t_data *data, char **envp, struct termios org_term)
{
	data->tkn_lst = tokenize(data->line);
	data->parse_code = parse_line(data->tkn_lst);
	data->tkn_lst = word_expantion(&data->tkn_lst, &data->envlst);
	data->cmd_lst = convert_cmd(data->tkn_lst);
	if (data->parse_code == ACC && data->cmd_lst)
		run_commands(data->cmd_lst, &data->envlst, envp, org_term);
	else if (data->parse_code == REJECT && data->tkn_lst)
	{
		ft_putstr_fd("minishell: syntax error occured\n", STDERR_FILENO);
		g_exit_code = 258;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data			data;
	struct termios	org_term;
	struct termios	new_term;

	if (argc != 1 && argv[1] != NULL)
		return (127);
	minishell_pre_process(&data.envlst, envp, &org_term);
	while (true)
	{
		set_input_mode(&new_term);
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, sigquit_handler);
		data.line = readline("minishell$ ");
		if (!data.line)
		{
			printf("byebye\n");
			break ;
		}
		exec(&data, envp, org_term);
		minishell_line_clear(data.line, data.cmd_lst, data.tkn_lst);
	}
	rl_clear_history();
	reset_input_mode(&org_term);
	exit(0);
}
