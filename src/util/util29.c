/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util26.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:53:56 by mguerga           #+#    #+#             */
/*   Updated: 2023/12/06 16:19:32 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt_head.h"

double	get_resolution(void)
{
	double	resolution;

	resolution = RESOLUTION;
	if (getenv("RESOLUTION"))
	{
		resolution = atof(getenv("RESOLUTION"));
		printf("picked up resolution from env: %f\n", resolution);
	}
	else
	{
		printf("using hardcoded resolution: %f\n", resolution);
	}
	return (resolution);
}

t_floatint_tuple	floatint(float f, int i)
{
	t_floatint_tuple	res;

	res.f = f;
	res.i = i;
	return (res);
}

enum e_ObjectType	get_item_type(t_elem *elem)
{
	if (elem->type == 's')
		return (Sphere);
	if (elem->type == 'p')
		return (Plane);
	if (elem->type == 'c')
		return (Cylinder);
	if (elem->type == 'y')
		return (Pyramid);
	if (elem->type == 'b')
		return (Cube);
	return (Sphere);
}

static void	ft_delnode(void *content)
{
	free(content);
}

void				free_items(t_list **lst)
{
	ft_lstclear(lst, ft_delnode);
}
