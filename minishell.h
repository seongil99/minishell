/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 13:43:40 by seonyoon          #+#    #+#             */
<<<<<<< HEAD
<<<<<<< HEAD
/*   Updated: 2024/02/17 17:36:26 by seonyoon         ###   ########.fr       */
=======
/*   Updated: 2024/02/13 13:46:58 by sihkang          ###   ########seoul.kr  */
>>>>>>> add: builtins
=======
/*   Updated: 2024/02/14 13:33:35 by sihkang          ###   ########seoul.kr  */
>>>>>>> add: signal handling
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

# define TRUE 1
# define FALSE 0

extern int	g_exit_code;

typedef struct s_env_node
{
	char				*key;
	char				*value;
	struct s_env_node	*next;
	struct s_env_node	*prev;
}			t_env_node;

typedef struct s_env_lst
{
	struct s_env_node	*head;
	struct s_env_node	*tail;
	struct s_env_node	*curr;
	int				nums;
}			t_env_lst;

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
	int				type; // cmd arguments pipe redirection heredoc and_if or_if parentheses
	int				pipefd[2];
	struct s_node	*next;
	struct s_node	*prev;
}			t_node;

int		builtin_env(t_env_lst *envlst);
int		builtin_cd(t_lst *lst);
int		builtin_pwd(void);
int		builtin_echo(t_lst *lst);
void	builtin_exit(t_lst	*lst);
int		builtin_unset(t_env_lst *envlst, char *remove_key);
int		builtin_export(t_env_lst *envlst, char *keyvalue);
int		builtin_choice(t_lst *lst, t_env_lst *envlst);
void	run_commands(char **tokens, t_lst *lst, t_env_lst *envlst, char **envp);

void	redi_right(t_lst *lst, t_env_lst *envlst, char **envp);
void	redi_left(t_lst *lst, t_env_lst *envlst, char **envp);
void	redi_heredoc(t_lst *lst, char **envp);


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


# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

typedef struct s_list_gnl
{
	long long		*buf_info;
	char			*buf;
	struct s_list_gnl	*next;
}			t_list_gnl;

char		*ft_find_next_line(t_list_gnl *node, int fd);
char		*ft_make_str(t_list_gnl *node, char *str, size_t str_index, size_t str_max);
t_list_gnl	*ft_find_node(t_list_gnl *head, int fd);
char		*get_next_line(int fd);
char		*ft_realloc_gnl(char *str, size_t str_index, size_t	*str_max, int option);


void	first_equal_separtion(t_env_node *new, char *str);

#endif
