/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 13:20:05 by sihkang           #+#    #+#             */
/*   Updated: 2024/02/17 13:16:35 by sihkang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	builtin_pwd1(void)
{
	char 	*tmp;
	size_t	size;

	size = 100;
	tmp = (char *)ft_calloc(sizeof(char), size);
	while (!getcwd(tmp, size))
		size *= 2;
	printf("%s\n", tmp);
	free(tmp);
	return (1);
}
int main()
{
	DIR *dir;
	struct dirent *files;
	int i;
	char 	*tmp;
	size_t	size;

	size = 100;
	tmp = (char *)ft_calloc(sizeof(char), size);
	while (!getcwd(tmp, size))
		size *= 2;
	i = 0;
	dir = opendir(tmp);
	files = readdir(dir);
	while (files)
	{
		if (files->d_type == DT_REG)
			printf("file : %s\n", files->d_name);
		files = readdir(dir);
	}
	closedir(dir);
	chdir(getenv("HOME"));
	builtin_pwd1();
	return 0;
}
