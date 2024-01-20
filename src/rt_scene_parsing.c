/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_scene_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:54:04 by mguerga           #+#    #+#             */
/*   Updated: 2024/01/18 11:29:42 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_head.h"

t_list	*scene_parsing(int ac, char **av)
{
	int	av_size;
	int	fd;

	if (ac != 2)
		return (print_err("You must have 1 scene as argument !\n"), NULL);
	av_size = ft_strlen(av[1]);
	if (av_size < 4 || ft_strncmp(&av[1][av_size - 3], ".rt", 4))
		return (print_err("The scene must be in the \".rt\" format !\n"), NULL);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (print_err("The scene does not exist !\n"), NULL);
	return (in_scene_parsing(fd));
}

t_list	*in_scene_parsing(int fd)
{
	char	*str;
	t_list	*e_list;	
	char	*temp;

	str = get_next_line(fd);
	ft_lstadd_front(&e_list, ft_lstnew(NULL));
	while (str != NULL)
	{
		temp = str;
		if (add_element(&e_list, str) != 0)
		{
			free(temp);
			return (NULL);
		}
		str = get_next_line(fd);
		free (temp);
	}
	musthave_elem(e_list);
	return (e_list);
}

void	musthave_elem(t_list *e_list)
{
	t_elem	*elem;
	int		c;

	c = 0;
	while (e_list->content != NULL)
	{
		elem = e_list->content;
		if (elem->type == 'C')
			c++;
		if (elem->type == 'L')
			c++;
		if (elem->type == 'A')
			c++;
		e_list = e_list->next;
	}
	if (c != 3)
	{
		print_err(
			"The .rt file must contain 1 of each \"Capital element\" !\n");
		exit (1);
	}
}
