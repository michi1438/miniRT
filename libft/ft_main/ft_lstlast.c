/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 11:11:13 by mguerga           #+#    #+#             */
/*   Updated: 2022/11/02 11:08:47 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*fwd;
	int		lastn;
	int		i;

	fwd = lst;
	i = 0;
	lastn = ft_lstsize(fwd);
	while (i < (lastn - 1))
	{
		fwd = fwd->next;
		i++;
	}
	return (fwd);
}
