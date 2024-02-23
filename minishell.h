/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 13:43:40 by seonyoon          #+#    #+#             */
/*   Updated: 2024/02/23 18:54:11 by sihkang          ###   ########seoul.kr  */
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
	char				*token;
	char				*file_heredoc;
	int					pipefd[2];
	t_gmr_var			type;
	struct s_cmd_node	*next;
	struct s_cmd_node	*prev;
}			t_cmd_node;

typedef struct s_list_gnl
{
	long long			*buf_info;
	char				*buf;
	struct s_list_gnl	*next;
}			t_list_gnl;

int			builtin_env(t_cmd_lst *lst, t_env_lst *envlst);
int			builtin_cd(t_cmd_lst *lst, t_env_lst *envlst);
int			builtin_pwd(void);
int			builtin_echo(t_cmd_lst *lst);
void		builtin_exit(t_cmd_lst	*lst);
int			builtin_unset(t_cmd_lst *lst, t_env_lst *envlst);
int			builtin_export(t_cmd_lst *lst, t_env_lst *envlst);
int			builtin_choice(t_cmd_lst *lst, t_env_lst *envlst);
int			is_builtin(t_cmd_lst *lst);
void		update_underbar(t_cmd_lst *lst, t_env_lst *envlst);
void		update_oldpwd(t_env_lst *envlst);
void		update_pwd(t_env_lst *envlst);
int			is_cmd(t_cmd_node *node);
int			is_cmd_for_move(t_cmd_node *node);
int			is_cmd_for_heredoc(t_cmd_node *node);
int			is_cmd_after_lr(t_cmd_node *node);
int			is_cmd_for_rr(t_cmd_node *node);
int			is_cmd_for_args(t_cmd_node *node);
int			is_cmd_for_check_logic(t_cmd_node *node);
int			is_cmd_pp(t_cmd_node *node);
int			is_cmd_for_move(t_cmd_node *node);
char		*last_args(t_cmd_lst *lst);
int			redirect_check(t_cmd_node *tmp);
char		**need_realloc_chk(char **args, int nums, int *size);
void		push_args(t_cmd_lst *lst, char **args, int *nums, int *size);
t_cmd_node	*get_next_cmd(t_cmd_lst *lst);
t_cmd_node	*get_next_cmd2(t_cmd_lst *lst); // erase
t_cmd_node	*get_next_cmd_for_heredoc(t_cmd_node *node);
t_cmd_node	*get_next_cmd_pp(t_cmd_lst *lst);
t_cmd_node	*get_next_cmd_for_check_logic(t_cmd_lst *lst);
t_cmd_node	*get_next_cmd_after_lr(t_cmd_lst *lst);
t_cmd_node	*get_prev_cmd(t_cmd_lst *lst);
t_cmd_node	*get_prev_cmd_pp(t_cmd_lst *lst);
t_cmd_node	*get_prev_cmd_rr(t_cmd_lst *lst);
t_cmd_node	*get_next_cmd_for_move(t_cmd_lst *lst);
char 		**get_cmd_args(t_cmd_lst *lst);
char 		**get_cmd_args_pp(t_cmd_lst *lst);
void		clear_lst(t_cmd_lst *lst);
t_cmd_lst	*convert_cmd(t_lst	*lst);
void		*ft_calloc2(size_t cnt, size_t size);
void		sigint_handler_stdin(int a);
void		sigquit_handler_stdin(int a);
void		run_commands(t_cmd_lst *lst, t_env_lst *envlst, char **envp);
void		update_underbar(t_cmd_lst *lst, t_env_lst *envlst);
void		logic_control(t_cmd_lst *lst, t_env_lst *envlst, char **envp);
int			logic_stop(t_cmd_lst *lst);
void		redi_right(t_cmd_lst *lst, t_env_lst *envlst, char **envp);
void		redi_left(t_cmd_lst *lst, t_env_lst *envlst, char **envp);
void		get_heredoc(t_cmd_lst *lst, t_env_lst *envlst);
int			redirect_check(t_cmd_node *tmp);
void		init_pipe(t_cmd_lst *lst);
void		close_pipe(t_cmd_lst *lst);
void		pipe_exec(t_cmd_lst *lst, t_env_lst *envlst, char *envp[]);
void		exec_subshell(t_cmd_lst *lst);
void		move_to_close_subshell(t_cmd_lst *lst);
int			redi_heredoc(t_cmd_lst *lst, t_env_lst *envlst, char *file_name, char *deli);
char		*get_pwd(void);
void		sigint_handler();
void		sigquit_handler();
void		sigint_handler_child(int a);
void		sigquit_handler_child(int a);
void 		save_input_mode(struct termios *org_term);
void		set_input_mode(struct termios *new_term);
void		reset_input_mode(struct termios *org_term);
void		move_to_next_cmd(t_cmd_lst *lst);
t_cmd_node	*get_next_cmd_after_lr(t_cmd_lst *lst);
int			exec_program(t_env_lst *envlst, char **args, char **envp);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

char		*ft_find_next_line(t_list_gnl *node, int fd);
char		*ft_make_str(t_list_gnl *node, char *str, size_t str_index, size_t str_max);
t_list_gnl	*ft_find_node(t_list_gnl *head, int fd);
char		*get_next_line(int fd);
char		*ft_realloc_gnl(char *str, size_t str_index, size_t	*str_max, int option);



#endif
