/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 13:43:40 by seonyoon          #+#    #+#             */
/*   Updated: 2024/03/05 09:08:05 by sihkang          ###   ########seoul.kr  */
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
# include <sys/stat.h>
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
	int					nums;
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

typedef struct s_data
{
	int				parse_code;
	char			*line;
	t_lst			*tkn_lst;
	t_cmd_lst		*cmd_lst;
	t_env_lst		envlst;
}	t_data;

void		argu_cleaner(char **args);
pid_t		fork2(void);
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
int			is_cmd_for_check_logic(t_cmd_node *node);
int			is_cmd_pp(t_cmd_node *node);
int			is_cmd_for_move(t_cmd_node *node);
char		*last_args(t_cmd_lst *lst);
int			redirect_check(t_cmd_node *tmp);
char		**need_realloc_chk(char **args, int nums, int *size);
char		**push_args(t_cmd_lst *lst, char **args, int *nums, int *size);
t_cmd_node	*get_next_cmd_for_heredoc(t_cmd_node *node);
t_cmd_node	*get_next_cmd_pp(t_cmd_lst *lst);
t_cmd_node	*get_next_cmd_after_lr(t_cmd_lst *lst);
t_cmd_node	*get_prev_cmd_rr(t_cmd_lst *lst);
t_cmd_node	*get_next_cmd_for_move(t_cmd_lst *lst);
char		**get_cmd_args(t_cmd_lst *lst);
char		**get_cmd_args_pp(t_cmd_lst *lst);
void		clear_lst(t_cmd_lst *lst);
t_cmd_lst	*convert_cmd(t_lst	*lst);
void		*ft_calloc2(size_t cnt, size_t size);
void		run_commands(t_cmd_lst *lst, t_env_lst *envlst, \
						char **envp, struct termios org_term);
void		logic_control(t_cmd_lst *lst, t_env_lst *envlst, \
						char **envp, pid_t *proc_id);
int			logic_stop(t_cmd_lst *lst);
void		redi_right(t_cmd_lst *lst, t_env_lst *envlst, char **envp);
void		redi_left(t_cmd_lst *lst);
void		get_heredoc(t_cmd_lst *lst, t_env_lst *envlst);
int			redirect_check(t_cmd_node *tmp);
t_cmd_node	*right_condition(t_cmd_lst *lst);
void		init_pipe(t_cmd_lst *lst);
void		close_pipe(t_cmd_lst *lst);
void		pipe_exec(t_cmd_lst *lst, t_env_lst *envlst, char *envp[]);
int			is_cmd_close_ss(t_cmd_node *node);
int			redi_heredoc(t_cmd_lst *lst, t_env_lst *envlst, \
						char *file_name, char *deli);
char		*get_pwd(void);
void		sigint_handler(int sig);
void		sigquit_handler(int sig);
void		signal_exec(int sig);
void		sigint_handler_heredoc(int a);
void		save_input_mode(struct termios *org_term);
void		set_input_mode(struct termios *new_term);
void		reset_input_mode(struct termios *org_term);
void		move_to_next_cmd(t_cmd_lst *lst);
t_cmd_node	*get_next_cmd_after_lr(t_cmd_lst *lst);
void		exec_program(t_env_lst *envlst, char **args, char **envp);
void		logic_post_processing(t_cmd_lst *lst, pid_t pid);
int			open_file_option(t_cmd_lst *lst);
t_cmd_node	*new_get_prev_cmd(t_cmd_lst *lst);
t_cmd_node	*new_get_next_cmd(t_cmd_lst *lst);
int			is_logical(t_cmd_node *ret);
void		exec_with_dir(t_env_lst *envlst, char **args, char **envp);
void		cmd_pre_process(t_cmd_lst *lst, t_env_lst *envlst);
void		set_program_envir(t_cmd_lst *lst, t_env_lst *envlst, \
					struct termios org_term);
void		cmd_post_process(t_cmd_lst *lst, pid_t proc_id);
void		process_io_exec(t_cmd_lst *lst, t_env_lst *envlst, \
					char **envp, pid_t *proc_id);
void		move_to_next_cmd_heredoc(t_cmd_lst *lst);
int			is_cmd_for_logic(t_cmd_node *node);
t_cmd_node	*left_redirect_condition(t_cmd_lst *lst);
t_cmd_node	*right_redirect_condition(t_cmd_lst *lst);
int			align_pl_location_condition(t_cmd_node *curr);
void		lst_reordering(t_cmd_lst *lst);
void		close_pipe_re(t_cmd_lst *lst);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

char		*ft_find_next_line(t_list_gnl *node, int fd);
char		*ft_make_str(t_list_gnl *node, char *str, \
					size_t str_index, size_t str_max);
t_list_gnl	*ft_find_node(t_list_gnl *head, int fd);
char		*get_next_line(int fd);
char		*ft_realloc_gnl(char *str, size_t str_index, \
					size_t	*str_max, int option);

#endif
