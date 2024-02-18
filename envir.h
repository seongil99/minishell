/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envir.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 14:33:47 by sihkang           #+#    #+#             */
/*   Updated: 2024/02/18 14:34:55 by sihkang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

// env elements lst
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
	int					nums;
}			t_env_lst;

// envir setting
void		first_equal_separtion(t_env_node *new, char *str);
void		init_env_lst(t_env_lst *envlst, char **envp);
void		create_new_node(t_env_lst *envlst, char *keyval);
void		remove_env_node(t_env_lst *envlst, char *delkey);
void		put_env_node(t_env_lst *envlst, char *str);
t_env_node	*search_env_node(t_env_lst *envlst, char *tofind);
