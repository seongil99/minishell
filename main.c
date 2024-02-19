/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonyoon <seonyoon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 13:49:19 by seonyoon          #+#    #+#             */
/*   Updated: 2024/02/19 13:20:13 by seonyoon         ###   ########.fr       */
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
	char			*line;
	char			**tokens;
	t_lst			*tmp;
	t_cmd_lst		*lst;
	t_env_lst		envlst;
	struct termios	org_term;
	struct termios	new_term;

	// atexit(check);
	if (argc != 1 && argv[1] != NULL)
		return (127);
	g_exit_code = 0;
	printf("WELCOME MINISHELL !\n");
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
	save_input_mode(&org_term);
	set_input_mode(&new_term);
	lst = (t_cmd_lst *)ft_calloc2(sizeof(t_cmd_lst), 1);
	lst->curr = NULL;
	init_env_lst(&envlst, envp);
	while (true)
	{
		lst->nums = 0;
		line = readline("input> ");
		if (!line)
		{
			printf("byebye\n");
			exit(0);
		}
		tmp = tokenize(line);
		lst = convert_cmd(tmp);
		if (lst)
			run_commands(lst, &envlst, envp);
		add_history(line);
		rl_replace_line("\n", 1);
		rl_on_new_line();
		clear_lst(lst);
		free(line);
		tokens = 0;
		line = 0;
	}
	free(lst);
	rl_clear_history();
	reset_input_mode(&org_term);
	exit(0);
}
