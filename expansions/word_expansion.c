/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_expansion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonyoon <seonyoon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:54:41 by seonyoon          #+#    #+#             */
/*   Updated: 2024/02/21 18:01:56 by seonyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

/**
 * t_lst *token_lst를 받아 word expansion을 수행
 * @param tknlst 토큰 리스트
 * @param envlst 환경변수 리스트
 * @return 토큰 리스트
*/
t_lst	*word_expantion(t_lst *tknlst, t_env_lst *envlst)
{
	if (!tknlst || !envlst)
		return (NULL);
	lst_tilde_expansion(tknlst, envlst);
	lst_param_expansion(tknlst, envlst);
	lst_path_expansion(tknlst);
	lst_quote_removal(tknlst);
	return (tknlst);
}
