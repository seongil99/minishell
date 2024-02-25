/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 13:49:19 by seonyoon          #+#    #+#             */
/*   Updated: 2024/02/25 15:03:13 by sihkang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_code;

void check(void)
{
	system("leaks minishell");
}

int	main(int argc, char **argv, char **envp)
{
	int				parse_code;
	char			*line;
	t_lst			*tkn_lst;
	t_cmd_lst		*cmd_lst;
	t_env_lst		envlst;
	struct termios	org_term;
	struct termios	new_term;

	// atexit(check);
	if (argc != 1 && argv[1] != NULL)
		return (127);
	g_exit_code = 0;
	init_action_tablev2();
	init_goto_tablev2();
	printf("WELCOME MINISHELL !\n");
	save_input_mode(&org_term);
	init_env_lst(&envlst, envp);
	while (true)
	{
		set_input_mode(&new_term);
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, sigquit_handler);
		line = readline("minishell$ ");
		if (!line)
		{
			printf("byebye\n");
			break ;
		}
		tkn_lst = tokenize(line);
		parse_code = parse_line(tkn_lst);
		tkn_lst = word_expantion(&tkn_lst, &envlst);
		cmd_lst = convert_cmd(tkn_lst);
		if (parse_code == ACC && cmd_lst)
			run_commands(cmd_lst, &envlst, envp, org_term);
		else if (parse_code == REJECT && tkn_lst)
		{
			ft_putstr_fd("minishell: syntax error occured\n", STDERR_FILENO);
			g_exit_code = 258;
		}
		add_history(line);
		rl_replace_line("\n", 1);
		rl_on_new_line();
		clear_lst(cmd_lst);
		cmd_lst = 0;
		free(line);
		lst_clear(&tkn_lst, token_del);
		line = 0;
	}
	rl_clear_history();
	reset_input_mode(&org_term);
	exit(0);
}
