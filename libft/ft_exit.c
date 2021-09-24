/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkim <youkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 15:50:07 by youkim            #+#    #+#             */
/*   Updated: 2021/09/24 18:33:09 by youkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_error(char *error)
{
	char	*e;
	char	*s;

	e = ft_strjoin(error, "\n");
	s = ft_strjoin("Error\n: ", e);
	ft_putstr_fd(2, s);
	if (e)
		free(e);
	if (s)
		free(s);
	exit(0);
}

int	ft_chkasn(int statement, char *error)
{
	if (statement == ERROR)
		ft_error(error);
	return (statement);
}
