/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 13:43:40 by seonyoon          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/02/17 17:36:26 by seonyoon         ###   ########.fr       */
=======
/*   Updated: 2024/02/13 13:46:58 by sihkang          ###   ########seoul.kr  */
>>>>>>> add: builtins
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

// int	g_exit_code = 0;

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

void	builtin_env(char *envp[]);
void	builtin_cd(t_lst *lst);
void	builtin_pwd(void);
void	builtin_echo(t_lst *lst);
void	builtin_exit(t_lst	*lst);
void	run_commands(char **tokens, t_lst *lst, char **envp);


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
char		*ft_realloc(char *str, size_t str_index, size_t	*str_max, int option);


#endif
