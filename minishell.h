/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 13:43:40 by seonyoon          #+#    #+#             */
/*   Updated: 2024/02/18 14:45:13 by sihkang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <dirent.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <term.h>
# include <fcntl.h>
# include <unistd.h>
# include <termios.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include "./libft/libft.h"
# include "parsing/mini_parsing.h"
# include "utils/mini_utils.h"
# include "envir.h"

# define TRUE 1
# define FALSE 0

extern int	g_exit_code;

// tokens lst
typedef struct s_lst
{
	struct s_node	*head;
	struct s_node	*tail;
	struct s_node	*curr;
	int				nums;
}			t_lst;

typedef struct s_node
{
	char			*token;
	int				pipefd[2];
	struct s_node	*next;
	struct s_node	*prev;
}			t_node;

typedef struct s_list_gnl
{
	long long			*buf_info;
	char				*buf;
	struct s_list_gnl	*next;
}			t_list_gnl;

void	clear_lst(t_lst *lst);

// utils
void	*ft_calloc2(size_t cnt, size_t size);

int		builtin_env(t_env_lst *envlst);
int		builtin_cd(t_lst *lst, t_env_lst *envlst);
int		builtin_pwd(void);
int		builtin_echo(t_lst *lst);
void	builtin_exit(t_lst	*lst);
int		builtin_unset(t_env_lst *envlst, char *remove_key);
int		builtin_export(t_env_lst *envlst, char *keyvalue);
int		builtin_choice(t_lst *lst, t_env_lst *envlst);
void	run_commands(char **tokens, t_lst *lst, t_env_lst *envlst, char **envp);

void	logic_control(t_lst *lst, t_env_lst *envlst, char **envp);
int		logic_stop(t_lst *lst);
void	redi_right(t_lst *lst, t_env_lst *envlst, char **envp);
void	redi_left(t_lst *lst, t_env_lst *envlst, char **envp);
void	redi_heredoc(t_lst *lst);
int		is_op(t_node *node);

char 	**get_cmd_args(t_lst *lst);
t_node	*get_prev_cmd(t_lst *lst);
t_node	*get_next_cmd(t_lst *lst);
void	push_cmd(t_lst *lst, char **tokens);
void	init_pipe(t_lst *lst);
void	close_pipe(t_lst *lst);
void	pipe_exec(t_lst *lst, t_env_lst *envlst, char *envp[]);

// terminal signal
void	sigint_handler();
void	sigquit_handler();
void 	save_input_mode(struct termios *org_term);
void	set_input_mode(struct termios *new_term);
void	reset_input_mode(struct termios *org_term);

// get_next_line_setting
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

char		*ft_find_next_line(t_list_gnl *node, int fd);
char		*ft_make_str(t_list_gnl *node, char *str, size_t str_index, size_t str_max);
t_list_gnl	*ft_find_node(t_list_gnl *head, int fd);
char		*get_next_line(int fd);
char		*ft_realloc_gnl(char *str, size_t str_index, size_t	*str_max, int option);

#endif
