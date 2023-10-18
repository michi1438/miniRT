/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 23:13:12 by mguerga           #+#    #+#             */
/*   Updated: 2022/11/02 11:10:41 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{	
	new->next = *lst;
	*lst = new;
}
/*
		
int main()
{
	int a = 42;
	int b = 43;
	t_list	list = {&a, NULL};
	t_list	*vlist = &list;
	t_list	nlist = {&b, NULL};
	
	printf("%d", (int)*vlist);
	ft_lstadd_front( &vlist, &nlist );
}	
*/
