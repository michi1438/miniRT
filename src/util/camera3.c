/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:53:56 by mguerga           #+#    #+#             */
/*   Updated: 2023/12/06 16:19:32 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt_head.h"

/* expresses a 3d point relatively to point A */
t_v	get_point_canvas_rel(t_camera camera, t_v p)
{
	t_v AB_proj;
	t_v AC_proj;
	t_v A_AB_proj;
	t_v A_AC_proj;
	int	xy_mult[2];

	AB_proj = project_point_onto_line(line_c(camera.A, camera.B), p);
	AC_proj = project_point_onto_line(line_c(camera.A, camera.C), p);
	A_AB_proj = v3_sub(AB_proj, camera.A);
	A_AC_proj = v3_sub(AC_proj, camera.A);
	xy_mult[0] = 1;
	xy_mult[1] = 1;
	if (!same_side_of_line(line_c(camera.A, camera.B), camera.C, p)) {
		xy_mult[1] = -1;
	}
	if (!same_side_of_line(line_c(camera.A, camera.C), camera.B, p)) {
		xy_mult[0] = -1;
	}
	return (v3(v3_len(A_AB_proj) * xy_mult[0], v3_len(A_AC_proj) * xy_mult[1], 0));
}

t_v	camera_get_D(t_camera camera)
{
	return (v3_add(camera.B, camera_get_AC(camera)));
}
