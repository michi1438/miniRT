/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 16:46:15 by mguerga           #+#    #+#             */
/*   Updated: 2022/11/03 14:42:33 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))

{
	t_list	*nxt;
	t_list	*snxt;

	nxt = *lst;
	while (nxt != NULL)
	{
		snxt = nxt;
		nxt = snxt->next;
		ft_lstdelone(snxt, del);
	}
	if (*lst != NULL)
		*lst = NULL;
}
