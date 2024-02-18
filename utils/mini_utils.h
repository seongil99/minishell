/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonyoon <seonyoon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:46:40 by seonyoon          #+#    #+#             */
/*   Updated: 2024/02/18 15:40:43 by seonyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_UTILS_H
# define MINI_UTILS_H

# include <stdbool.h>
# include "../libft/libft.h"
# include "ft_stack.h"
# include "linked_list.h"
# include "str_buffer.h"

void	*ft_calloc2(size_t cnt, size_t size);
void	exit_err(char *message);
void	mini_assert(bool condition, char *msg);
void	*ft_realloc(void *ptr, size_t ptrsize, size_t tosize);

#endif
