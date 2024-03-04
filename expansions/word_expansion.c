/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_expansion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonyoon <seonyoon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:54:41 by seonyoon          #+#    #+#             */
/*   Updated: 2024/03/04 16:41:45 by seonyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

/**
 * t_lst *token_lst를 받아 word expansion을 수행
 * @param tknlst 토큰 리스트
 * @param envlst 환경변수 리스트
 * @return 0 성공, 1 실패
*/
int	word_expantion(t_lst **tknlst, t_env_lst *envlst)
{
	int	ret;

	ret = 0;
	if (!tknlst || !*tknlst || !envlst)
		return (0);
	lst_tilde_expansion(*tknlst, envlst);
	lst_param_expansion(*tknlst, envlst);
	ret = lst_path_expansion(tknlst);
	lst_quote_removal(*tknlst);
	return (ret);
}
