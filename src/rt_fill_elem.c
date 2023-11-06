/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_fill_elem.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 13:25:07 by mguerga           #+#    #+#             */
/*   Updated: 2023/11/02 13:35:19 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_head.h"

void	fill_ambiant(t_elem *elem, char **splited)
{
	elem->light_ratio = ft_atof(splited[1]);
}
