/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 13:49:19 by seonyoon          #+#    #+#             */
/*   Updated: 2024/02/14 14:03:42 by sihkang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_code;

void	first_equal_separtion(t_env_node *new, char *str)
{
	int		i;
	int		len;

	i = 0;
	if (!str && !new)
		return ;
	while (str[i] != '=')
		i++;
	len = ft_strlen(str);
	new->key = (char *)ft_calloc(sizeof(char), len);
	new->value = (char *)ft_calloc(sizeof(char), len);
	ft_strlcpy(new->key, str, i + 1);
	ft_strlcpy(new->value, &str[i + 1], len - i + 1);
}

void	push_env_lst(t_env_lst *envlst, char **envp)
{
	t_env_node	*new;
	int			i;

	i = 0;
	while (envp[i])
	{
		new = (t_env_node *)ft_calloc(sizeof(t_env_node), 1);
		first_equal_separtion(new, envp[i]);
		if (i++ == 0)
		{
			envlst->head = new;
			envlst->tail = new;
			envlst->curr = new;
			new->next = NULL;
			new->prev = NULL;
		}
		else
		{
			envlst->tail->next = new;
			new->prev = envlst->tail;
			envlst->tail = new;
			new->next = NULL;
		}
		envlst->nums++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	char			*line;
	char			**tokens;
	t_lst			*lst;
	t_env_lst		envlst;
	struct termios	org_term;
	struct termios	new_term;

	if (argc != 1 && argv[1] != NULL)
		return (127);
	g_exit_code = 0;
	printf("WELCOME MINISHELL !\n");
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
	save_input_mode(&org_term);
	set_input_mode(&new_term);
	lst = (t_lst *)ft_calloc(sizeof(t_lst), 1);
	lst->curr = NULL;
	push_env_lst(&envlst, envp);
	while (TRUE)
	{
		lst->nums = 0;
		line = readline("input> ");
		if (!line)
		{
			printf("byebye\n");
			rl_on_new_line();
			exit(0);
		}
		tokens = ft_split(line, ' ');
		if (tokens)
			run_commands(tokens, lst, &envlst, envp);
		add_history(line);
		rl_replace_line("\n", 1);
		rl_on_new_line();
		free(line);
		free(tokens);
		tokens = 0;
		line = 0;
	}
	reset_input_mode(&org_term);
	exit(0);
}
