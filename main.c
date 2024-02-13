/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 13:49:19 by seonyoon          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/02/12 18:02:46 by seonyoon         ###   ########.fr       */
=======
/*   Updated: 2024/02/13 13:58:37 by sihkang          ###   ########seoul.kr  */
>>>>>>> add: builtins
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// org_term에 초기 터미널 세팅 저장
void save_input_mode(struct termios *org_term)
{
	tcgetattr(STDIN_FILENO, org_term); // STDIN으로부터 터미널 속성을 받아온다
}

// new_term에 원하는 터미널 속성 설정
void set_input_mode(struct termios *new_term)
{
	tcgetattr(STDIN_FILENO, new_term); // STDIN으로부터 터미널 속성을 받아온다
	new_term->c_lflag &= ~(ICANON | ECHO);  // ICANON, ECHO 속성을 off
	new_term->c_cc[VMIN] = 1;               // 1 바이트씩 처리
	new_term->c_cc[VTIME] = 0;              // 시간은 설정하지 않음
	tcsetattr(STDIN_FILENO, TCSANOW, new_term); // 변경된 속성의 터미널을 STDIN에 바로 적용
}

// 기존의 터미널 세팅으로 다시 변경
void reset_input_mode(struct termios *org_term)
{
	tcsetattr(STDIN_FILENO, TCSANOW, org_term);  // STDIN에 기존의 터미널 속성을 바로 적용
}

void	term_input_loop(void)
{
	int	idx;
	int key;

	idx = -1;
	key = 0;
	
	while (read(0, &key, 1) > 0)
	{
		if (key == 3)
		{
			write(0, "\n", 1);
		}
		else if (key == 4)
		{
			if (idx == -1)
				exit(0);
			else
				continue;
		}		
		else if (key == 127)
		{
			if (idx >= 0)
			{
				--idx;
				write(0, "\b \b", 3);
			}
		}
		else if (key == '\n')
			break;
		else
		{
			++idx;
			write(0, &key, sizeof(int));
		}
		key = 0;
	}
}

// void	push_env_lst(t_env_lst *envlst, char **envp)
// {
// 	t_env_node	*new;
// 	int			i;
// 	char		**tmp;

// 	i = 0;
// 	new = (t_env_node *)ft_calloc(sizeof(t_env_node), 1);
// 	tmp = ft_split(envp[i], '\n');
// 	new->key = tmp[0];
// 	new->value = tmp[1];
// 	if (i++ == 0)
// 	{
// 		envlst->head = new;
// 		envlst->tail = new;
// 		envlst->curr = new;
// 		new->next = NULL;
// 		new->prev = NULL;
// 	}
// 	else
// 	{
// 		envlst->tail->next = new;
// 		new->prev = envlst->tail;
// 		envlst->tail = new;
// 		new->next = NULL;
// 	}
// 	envlst->nums++;
// }

int	main(int argc, char **argv, char **envp)
{
	char			*line;
	char			**tokens;
	t_lst			*lst;
	t_env_lst			envlst;
	struct termios	org_term;
	struct termios	new_term;

	if (argc != 1 && argv[1] != NULL)
		return (127);
	printf("WELCOME MINISHELL !\n");
	save_input_mode(&org_term);
	set_input_mode(&new_term);
	lst = (t_lst *)ft_calloc(sizeof(t_lst), 1);
	lst->curr = NULL;
	while (TRUE)
	{
		lst->nums = 0;
		line = readline("input> ");
		term_input_loop();
		if (!line)
			exit(0);
		tokens = ft_split(line, ' ');
		if (tokens)
			run_commands(tokens, lst, envp);
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
