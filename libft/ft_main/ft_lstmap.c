/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 20:55:52 by mguerga           #+#    #+#             */
/*   Updated: 2022/11/03 17:01:33 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*add;
	t_list	*first;
	t_list	*temp;

	first = NULL;
	while (lst)
	{
		temp = ((*f)(lst->content));
		add = ft_lstnew(temp);
		if (add == NULL)
		{
			del(temp);
			ft_lstclear(&first, (*del));
		}
		ft_lstadd_back(&first, add);
		lst = lst->next;
	}
	return (first);
}
