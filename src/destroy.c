/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_kb_and_pp_mlx.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 12:15:26 by mguerga           #+#    #+#             */
/*   Updated: 2024/01/18 12:15:30 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_head.h"

int	destroy(t_rtdata *data)
{
	mlx_destroy_window(data->scrn->mlx, data->scrn->win);
	free_items(&data->items);
	exit(0);
}
