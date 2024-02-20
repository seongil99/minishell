/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 13:43:40 by seonyoon          #+#    #+#             */
/*   Updated: 2024/02/20 16:15:56 by sihkang          ###   ########seoul.kr  */
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
# include "expansions/expansions.h"
# include "envir.h"

extern int	g_exit_code;

// tokens lst
typedef struct s_cmd_lst
{
	struct s_cmd_node	*head;
	struct s_cmd_node	*tail;
	struct s_cmd_node	*curr;
	int				nums;
}			t_cmd_lst;

typedef struct s_cmd_node
{
	char			*token;
	char			*file_heredoc;
	int				pipefd[2];
	struct s_cmd_node	*next;
	struct s_cmd_node	*prev;
}			t_cmd_node;

typedef struct s_list_gnl
{
	long long			*buf_info;
	char				*buf;
	struct s_list_gnl	*next;
}			t_list_gnl;

void		clear_lst(t_cmd_lst *lst);
t_cmd_lst	*convert_cmd(t_lst	*lst);

// utils
void		*ft_calloc2(size_t cnt, size_t size);

int			builtin_env(t_env_lst *envlst);
int			builtin_cd(t_cmd_lst *lst, t_env_lst *envlst);
int			builtin_pwd(void);
int			builtin_echo(t_cmd_lst *lst);
void		builtin_exit(t_cmd_lst	*lst);
int			builtin_unset(t_env_lst *envlst, char *remove_key);
int			builtin_export(t_env_lst *envlst, char *keyvalue);
int			builtin_choice(t_cmd_lst *lst, t_env_lst *envlst);
void		run_commands(t_cmd_lst *lst, t_env_lst *envlst, char **envp);

void		logic_control(t_cmd_lst *lst, t_env_lst *envlst, char **envp);
int			logic_stop(t_cmd_lst *lst);
void		redi_right(t_cmd_lst *lst, t_env_lst *envlst, char **envp);
void		redi_left(t_cmd_lst *lst, t_env_lst *envlst, char **envp);
void		redi_heredoc(t_cmd_lst *lst, char *file_name, char *deli);
void		get_heredoc(t_cmd_lst *lst);
int			is_cmd(t_cmd_node *node);
int			is_cmd2(t_cmd_node *node);
t_cmd_node	*get_next_cmd2(t_cmd_lst *lst);
char 		**get_cmd_args(t_cmd_lst *lst);
t_cmd_node	*get_prev_cmd(t_cmd_lst *lst);
t_cmd_node	*get_next_cmd(t_cmd_lst *lst);
void		push_cmd(t_cmd_lst *lst, char **tokens);
void		init_pipe(t_cmd_lst *lst);
void		close_pipe(t_cmd_lst *lst);
void		pipe_exec(t_cmd_lst *lst, t_env_lst *envlst, char *envp[]);
void		exec_subshell(t_cmd_lst *lst);
void		move_to_close_subshell(t_cmd_lst *lst);

int			is_cmd_for_heredoc(t_cmd_node *node);
t_cmd_node	*get_next_cmd_for_heredoc(t_cmd_node *node);
t_cmd_node	*get_next_cmd_pp(t_cmd_lst *lst);
t_cmd_node	*get_prev_cmd_pp(t_cmd_lst *lst);
// terminal signal
void		sigint_handler();
void		sigquit_handler();
void 		save_input_mode(struct termios *org_term);
void		set_input_mode(struct termios *new_term);
void		reset_input_mode(struct termios *org_term);

// cmds
void		move_to_next_cmd(t_cmd_lst *lst);

t_cmd_node	*get_next_cmd_after_lr(t_cmd_lst *lst);
int			is_cmd_after_lr(t_cmd_node *node);

// get_next_line_setting
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

char		*ft_find_next_line(t_list_gnl *node, int fd);
char		*ft_make_str(t_list_gnl *node, char *str, size_t str_index, size_t str_max);
t_list_gnl	*ft_find_node(t_list_gnl *head, int fd);
char		*get_next_line(int fd);
char		*ft_realloc_gnl(char *str, size_t str_index, size_t	*str_max, int option);

int			is_cmd_for_rr(t_cmd_node *node);
t_cmd_node	*get_prev_cmd_rr(t_cmd_lst *lst);



int		exec_program(t_env_lst *envlst, char **args, char **envp);

#endif
