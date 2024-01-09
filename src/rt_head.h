/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_head.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 11:36:11 by mguerga           #+#    #+#             */
/*   Updated: 2024/01/04 16:22:19 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_HEAD_H
# define RT_HEAD_H

# define S_WIDTH (1368)
# define S_HEIGHT (912)

# include <stdio.h>
# include <float.h>
# ifdef __linux__
# include "../minilibx-linux/mlx.h"
# else
# include "../minilibx_opengl_20191021/mlx.h"
# endif
# include "../libft/src_libft.h"
# include <math.h>

# define TOLERANCE 0.000001

//typedef float vec[3];

typedef struct s_v3
{
	float	x;
	float	y;
	float	z;
}	t_v3;

typedef t_v3	vec;

typedef struct s_elem
{
	char	type;
	int		rgb[3];
	float	xyz[3];
	float	norm_xyz[3];
	float	fov;
	float	sratio;
	float	radius;
	float	height;
	float	light_ratio;
	int		status;
}	t_elem;

typedef struct s_scData
{
	void	*img;
	void	*mlx;
	void	*win;
	char	*addr;
	int		bits_pp;
	int		line_len;
	int		endian;
	t_list	**e_list_displayed;	
}	t_scData;

// MATRICES.C
void	rt_matrix(float *ret, t_elem *cam_specs);

// SCENE.C
void	set_scene(t_scData *scrn, t_list **e_list);
void	first_rays(t_scData *scrn, t_list **e_list);
void	cycle_objects(int xy[2], float pscreen[3], t_elem *cam_specs, t_scData *scrn, t_list **e_list);
int		cycle_shadow(float n_vec[3], float orig_xyz[3], t_list **e_list, float n_len);

// FETCH_ELEM.C
t_elem	*findcam(t_list **e_list);
t_elem	*findamb(t_list **e_list);
t_elem	*findlight(t_list **e_list);

// INTERSECTING.C
float	intersect_sp(float *normal_dir, float orig_xyz[3], t_elem *obj);
int		solve_discriminent(float a, float b, float c, float *intersect_dist);

// VEC_MATH.C
float	dotprod(float *vec1, float *vec2);
void	vec_substract(float *res_vec, float *vec1, float *vec2);
void	normalize(float *xyz);

// FILL_CONTROL.c
void	set_uvalue(t_elem *elem);
void	init_elem(t_elem *elem, char *str);
int		add_element(t_list	**e_list, char *str);

// FILL_LIGHTSNCAMERA.c
void	fill_err(char type);
void	fill_ambiant(t_elem *elem, char **splited);
void	fill_camera(t_elem *elem, char **splited);
void	fill_light(t_elem *elem, char **splited);

// FILL_SHAPES.c
void	fill_arrays(t_elem *elem, char **xyz, char **rgb, char **norm);
void	fill_cylinder(t_elem *elem, char **split);
void	fill_sphere(t_elem *elem, char **split);
void	fill_plane(t_elem *elem, char **split);

// DISPLAY.C
int		kb_mlx(int keycd, t_scData *scrn);
int		put_to_screen(t_list **e_list);
void	mlx_pp(t_scData *img, int x, int y, int color);

// SCENE_PARSING.C
t_list 	*scene_parsing(int ac, char **av);
t_list 	*in_scene_parsing(int fd);
void	musthave_elem(t_list *e_list);

// UTILS.C (maybe put this in libft)
float	ft_atof(char *str);
int		mix_color(t_elem *objects, t_list **e_list, float pscr[3]);
float	diffused(t_elem *objects, t_elem *light, float pscreen[3], t_list **e_list);

// ERR_HANDLING.C
int		print_err(char *str);

// TESTING.C
void	print_elem(t_elem *elem);

enum	e_Direction {
	Forward,
	Backward,
	Left,
	Right,
	Up,
	Down
};

enum	e_ObjectType {
	Plane,
	Sphere,
	Cube,
	Pyramid,
	Cylinder
};

typedef struct s_plane
{
	vec	p1;
	vec	p2;
	vec	p3;
}	t_plane;

typedef struct s_line
{
	vec	p1;
	vec	p2;
}	t_line;

typedef struct s_matrix3d
{
	vec	v1;
	vec	v2;
	vec	v3;
}	t_matrix3d;

typedef struct s_camera
{
	float	canvas_width;
	float	canvas_height;
	vec		eye;
	vec		A;
	vec		B;
	vec		C;
}	t_camera;

enum	e_LightType {
	Ambient,
	Point
};

typedef struct s_light
{
	enum e_LightType	type;
	vec					color;
	vec					pos;
}	t_light;

typedef struct s_image
{

}	t_image;

typedef struct s_item
{
	enum e_ObjectType	type;
	vec					pos;
	vec					scale;
	vec					color;
	float				specular;
	int					is_checker;
	vec					z_ref_point;
	vec					vertices[34];
	int					vertices_len;
	int					id;
	vec					*pixel_cache;
	int					cache_width;
	int					cache_length;
	t_image				*image;
}	t_item;

typedef struct s_intersection
{
	vec	pos;
	vec	normal;
	t_line	ray;
	t_item	item;
}	t_intersection;

// UTIL1.C
t_v3	v3(float x, float y, float z);
vec		v3_add(vec a, vec b);
float	clamp (float val, float min, float max);
vec		add_colors(vec c1, vec c2);
vec		mult_colors(vec c1, vec c2);

// UTIL2.C
vec	modify_color_intensity(vec color, float scalar);
vec	intensity_to_color(float intensity);
int	same_sign(float a, float b);
t_plane	plane_c(vec p1, vec p2, vec p3);
vec	plane_normal(t_plane plane);

// UTIL3.C
int	colinear_check(vec v1, vec v2);
t_plane	plane_from_normal(vec point, vec normal);
t_line	line_c(vec p1, vec p2);
t_matrix3d	matrix3d_c(vec v1, vec v2, vec v3);
int	same_side_of_line(t_line line, vec A, vec B);

// UTIL4.C
int	same_side_of_plane(t_plane plane, vec A, vec B);
vec	rotate_point(vec p, vec v, vec r);
float	vect_angle(vec v1, vec v2);
float	degree_to_radian(float angle);

// UTIL5.C
vec	v3_sub(vec a, vec b);
vec	v3_clone(vec v);
vec	v3_null();
int	v3_is_null(vec v);
vec	project_point(vec point, t_camera camera);

// CAMERA.C
t_camera	camera_(float eye_canv_dist, float screen_width, float screen_height);
vec	camera_get_AC(t_camera camera);
vec	camera_get_AB(t_camera camera);
t_plane	camera_get_canvas_plane(t_camera camera);
vec	camera_get_center(t_camera camera);

// CAMERA2.C
vec	camera_get_norm(t_camera camera);
void	camera_rotate(t_camera camera, enum e_Direction direction, float amount);
void	camera_move(t_camera camera, enum e_Direction direction, float amount);

// CAMERA3.C
vec	get_point_canvas_rel(t_camera camera, vec p);
vec	camera_get_D(t_camera camera);

// ITEM.C
t_item	create_item(enum e_ObjectType type, vec pos, vec scale, vec color);
vec	item_get_axis(t_item item);
void	item_draw_axes(t_item item);
unsigned int	item_color_hex(t_item item);

// UTIL6.C
t_light	light(enum e_LightType type, vec color, vec pos);
t_intersection	intersection(vec pos, vec normal, t_line ray, t_item item);
vec	map_point_to_physical(t_camera camera, vec point, float physical_width, float physical_height);
vec	map_physical_to_camera(t_camera camera, vec point, float physical_width, float physical_height);
vec	v3_scale(vec a, float scale);

// UTIL7.C
vec	v3_invert(vec a);
vec	v3_abs(vec a);
float	v3_len(vec a);
vec	v3_norm(vec v);
float	v3_norm_squared(vec v);

// UTIL8.C
vec	v3_cross(vec a, vec b);
float	v3_dot(vec a, vec b);
vec	project_point_onto_line(t_line line, vec point);
float	point_plane_dist(vec point, t_plane plane);
float	signed_point_plane_dist(vec point, t_plane plane);

// UTIL9.C
vec	project_point_onto_plane(vec point, t_plane plane);
vec	matrix_mult_vec(t_matrix3d matrix, vec v);
t_matrix3d	matrix_scale(t_matrix3d matrix, float scalar);
t_matrix3d	matrix_mult(t_matrix3d m1, t_matrix3d m2);
t_matrix3d	matrix_sub(t_matrix3d m1, t_matrix3d m2);

// UTIL 11.C
t_matrix3d	get_identity_matrix(void);
vec	get_cylinder_top(t_item cylinder);
vec	get_cylinder_bottom(t_item cylinder);
vec	intersect(t_line line, t_plane plane);
int	equals_with_tolerance(float val1, float val2);

// DRAW_LINE.C
void	draw_line_dda(t_scData *scrn, vec p1, vec p2, int color);

#endif // RT_HEAD_H
