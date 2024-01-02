/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_fetch_elem.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 11:11:03 by mguerga           #+#    #+#             */
/*   Updated: 2024/01/02 17:48:30 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_head.h" 

t_elem	*findcam(t_list **e_list)
{
	t_elem	*cam;
	t_list	*list;	

	list = *e_list;
	while (list != NULL)
	{
		cam = (list)->content;
		if (cam->type == 'C')
			return (cam);
		list = list->next;
	}
	return (NULL);
}

t_elem	*findamb(t_list **e_list)
{
	t_elem	*amb;
	t_list	*list;	

	list = *e_list;
	while (list != NULL)
	{
		amb = (list)->content;
		if (amb->type == 'A')
			return (amb);
		list = list->next;
	}
	return (NULL);
}

t_elem	*findlight(t_list **e_list)
{
	t_elem	*amb;
	t_list	*list;	

	list = *e_list;
	while (list != NULL)
	{
		amb = (list)->content;
		if (amb->type == 'L')
			return (amb);
		list = list->next;
	}
	return (NULL);
}
