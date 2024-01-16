/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:53:56 by mguerga           #+#    #+#             */
/*   Updated: 2023/12/06 16:19:32 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt_head.h"

t_v	camera_get_norm(t_camera camera)
{
	return (v3_norm(v3_sub(camera_get_center(camera), camera.eye)));
}

static void	camera_rotate_(t_camera *camera,
					enum e_Direction direction, float amount)
{
	t_v	rot_vect;

	if (direction == Up)
	{
		rot_vect = v3_scale(v3_norm(camera_get_ab(*camera)), amount);
		camera->A = rotate_point(camera->A, rot_vect, camera->eye);
		camera->B = rotate_point(camera->B, rot_vect, camera->eye);
		camera->C = rotate_point(camera->C, rot_vect, camera->eye);
	}
	else
	{
		rot_vect = v3_scale(v3_norm(camera_get_ab(*camera)), -amount);
		camera->A = rotate_point(camera->A, rot_vect, camera->eye);
		camera->B = rotate_point(camera->B, rot_vect, camera->eye);
		camera->C = rotate_point(camera->C, rot_vect, camera->eye);
	}
}

void	camera_rotate(t_camera *camera,
					enum e_Direction direction, float amount)
{
	t_v	rot_vect;

	if (direction == Right)
	{
		rot_vect = v3_scale(v3(0, 1, 0), -amount);
		camera->A = rotate_point(camera->A, rot_vect, camera->eye);
		camera->B = rotate_point(camera->B, rot_vect, camera->eye);
		camera->C = rotate_point(camera->C, rot_vect, camera->eye);
	}
	else if (direction == Left)
	{
		rot_vect = v3_scale(v3(0, 1, 0), amount);
		camera->A = rotate_point(camera->A, rot_vect, camera->eye);
		camera->B = rotate_point(camera->B, rot_vect, camera->eye);
		camera->C = rotate_point(camera->C, rot_vect, camera->eye);
	}
	else
	{
		camera_rotate_(camera, direction, amount);
	}
}

static t_v	camera_move_(t_camera camera,
					enum e_Direction direction, float amount)
{
	if (direction == Right)
		return (v3_scale(v3_norm(camera_get_ab(camera)), amount));
	else if (direction == Left)
		return (v3_scale(v3_norm(camera_get_ab(camera)), -amount));
	else if (direction == Up)
		return (v3_scale(v3(0, 1, 0), amount));
	else
		return (v3_scale(v3(0, 1, 0), -amount));
}

void	camera_move(t_camera *camera, enum e_Direction direction, float amount)
{
	t_v	move_vect;
	t_v	vct;

	if (direction == Forward)
	{
		vct = v3_sub(camera_get_center(*camera), camera->eye);
		vct.y = 0;
		vct = v3_norm(vct);
		move_vect = v3_scale(vct, amount);
	}
	else if (direction == Backward)
	{
		vct = v3_norm(v3_sub(camera_get_center(*camera), camera->eye));
		vct.y = 0;
		move_vect = v3_scale(vct, -amount);
	}
	else
		move_vect = camera_move_(*camera, direction, amount);
	camera->eye = v3_add(move_vect, camera->eye);
	camera->A = v3_add(move_vect, camera->A);
	camera->B = v3_add(move_vect, camera->B);
	camera->C = v3_add(move_vect, camera->C);
}
