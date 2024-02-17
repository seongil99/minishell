/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonyoon <seonyoon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 16:36:53 by seonyoon          #+#    #+#             */
<<<<<<< Updated upstream
/*   Updated: 2024/02/11 20:46:08 by seonyoon         ###   ########.fr       */
=======
/*   Updated: 2024/02/17 12:40:18 by seonyoon         ###   ########.fr       */
>>>>>>> Stashed changes
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STACK_H
# define FT_STACK_H

# include <stdlib.h>
# include "linked_list.h"

typedef struct s_stack
{
	t_lst	*_btm;
	t_lst	*_top;
	int		size;
	void	(*push)(struct s_stack *self, int val);
	void	(*pop)(struct s_stack *self, void (*del_func)(void *));
	int		(*top)(struct s_stack *self);
}	t_stack;

t_stack	*stack_new(void);
void	stack_del(t_stack *st, void (*del_func)(void *));
int		stack_top(t_stack *st);
void	stack_pop(t_stack *st, void (*del_func)(void *));
void	stack_push(t_stack *st, int n);

#endif
