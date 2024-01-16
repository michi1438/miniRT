/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_head.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 11:36:11 by mguerga           #+#    #+#             */
/*   Updated: 2024/01/16 17:47:05 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_HEAD_H
# define RT_HEAD_H

# define S_WIDTH (1000)
# define S_HEIGHT (1000)

# include <stdio.h>
# include <float.h>
# ifdef __linux__
# include "../minilibx-linux/mlx.h"
# else
# include "../minilibx_opengl_20191021/mlx.h"
# endif
# include "../libft/src_libft.h"
# include <math.h>
# include <unistd.h>

# define RESOLUTION 0.006
# define SPECULAR 0.7
# define TOLERANCE 0.000001
# define ROT_SPEED 0.003

# define RED 0x00FF0000
# define GREEN 0x0000FF00
# define BLUE 0x000000FF
# define WHITE 0x00000000

# ifdef __linux__
#  define K_ENTER 65293
#  define K_SPACE 32
#  define K_TAB 65289
#  define K_ESC 65307
#  define K_UP 65362
#  define K_DOWN 65364
#  define K_LEFT 65361
#  define K_RIGHT 65363
#  define K_W 119
#  define K_S 115
#  define K_A 97
#  define K_D 100
#  define K_P 112
#  define K_MINUS 61
#  define K_PLUS 10
#  define K_R 114
#  define K_U 117
#  define K_J 106
#  define K_I 105
#  define K_K 107
#  define K_O 111
#  define K_L 108

#  define K_NUM_4 65430
#  define K_NUM_6 65432
#  define K_NUM_8 65431
#  define K_NUM_2 65433
#  define K_NUM_MINUS 65453
#  define K_NUM_PLUS 65451
# else
#  define K_ENTER 36
#  define K_SPACE 49
#  define K_TAB 48
#  define K_ESC 53
#  define K_UP 126
#  define K_DOWN 125
#  define K_LEFT 123
#  define K_RIGHT 124
#  define K_W 13
#  define K_S 1
#  define K_A 0
#  define K_D 2
#  define K_P 35
#  define K_MINUS 27
#  define K_PLUS 24
#  define K_R 15
#  define K_U 32
#  define K_J 38
#  define K_I 34
#  define K_K 40
#  define K_O 31
#  define K_L 37

#  define K_NUM_4 86
#  define K_NUM_6 88
#  define K_NUM_8 91
#  define K_NUM_2 84
#  define K_NUM_MINUS 78
#  define K_NUM_PLUS 69
# endif

typedef struct s_v3
{
	float	x;
	float	y;
	float	z;
}	t_v3;

typedef t_v3	t_v;

typedef struct s_v3_tuple
{
	t_v	v1;
	t_v	v2;
}	t_v3_tuple;

typedef struct s_elem
{
	char	type;
	float	specular;
	int		is_checker;
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

// FILL_SHAPES2_& COMPL.c
void	fill_pyramid(t_elem *elem, char **split);
void	fill_cube(t_elem *elem, char **split);
void	fill_compl(t_elem *elem, char **split, int split_seg);

// DISPLAY.C
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
	t_v	p1;
	t_v	p2;
	t_v	p3;
}	t_plane;

typedef struct s_line
{
	t_v	p1;
	t_v	p2;
}	t_line;

typedef struct s_matrix3d
{
	t_v	v1;
	t_v	v2;
	t_v	v3;
}	t_matrix3d;

typedef struct s_camera
{
	float	canvas_width;
	float	canvas_height;
	t_v		eye;
	t_v		A;
	t_v		B;
	t_v		C;
}	t_camera;

enum	e_LightType {
	Ambient,
	Point
};

typedef struct s_light
{
	enum e_LightType	type;
	t_v					color;
	t_v					pos;
}	t_light;

typedef struct s_image
{
	t_v		**pixels;
	float	target_width;
	float	width;
	float	height;
}	t_image;

typedef struct s_item
{
	enum e_ObjectType	type;
	t_v					pos;
	t_v					scale;
	t_v					color;
	float				specular;
	int					is_checker;
	t_v					z_ref_point;
	t_v					vertices[34];
	int					vertices_len;
	int					id;
	t_v					**pixel_cache;
	int					cache_width;
	int					cache_length;
	t_image				*image;
}	t_item;

typedef struct s_intersection
{
	t_v	pos;
	t_v	normal;
	t_line	ray;
	t_item	*item;
}	t_intersection;

typedef struct s_rtdata
{
	t_camera	camera;
	t_scData	*scrn;
	t_list		*items;
	t_list		*lights;

}	t_rtdata;

int		kb_mlx(int keycd,  t_rtdata *data);

typedef struct s_terms
{
	t_v				D;
	t_v				V;
	t_v				C;
	t_v				X;
	t_v				N;
	float			d_v;
	float			x_v;
	float			t;
	t_v				normal;
	t_v				intr;
	float			a;
	float			b;
	float			c;
	float			r;
	float			discriminant;
	float			t1;
	float			t2;
	t_v				point;
	t_intersection	inter;
	t_intersection	inter2;
	float			dist;
	float			dist_;
	float			d1;
	float			d2;
	float			m1;
	float			m2;
	float			tmp;
	t_v				y_axis;
	t_v				x_axis;
	t_v				z_axis;
	float			x_dist;
	float			y_dist;
	float			z_dist;
	t_v			x;
	t_v			y;
	t_v			z;
	t_v				light_color;
	t_v				specular_color;
	t_v				diffuse_color;
	t_v				color;
}	t_terms;

typedef struct s_vecfour
{
	t_v	p1;
	t_v	p2;
	t_v	p3;
	t_v	p4;
}	t_vecfour;

// UTIL1.C
t_v3	v3(float x, float y, float z);
t_v		v3_add(t_v a, t_v b);
float	clamp (float val, float min, float max);
t_v		add_colors(t_v c1, t_v c2);
t_v		mult_colors(t_v c1, t_v c2);

// UTIL2.C
t_v	modify_color_intensity(t_v color, float scalar);
t_v	intensity_to_color(float intensity);
int	same_sign(float a, float b);
t_plane	plane_c(t_v p1, t_v p2, t_v p3);
t_v	plane_normal(t_plane plane);

// UTIL3.C
int	colinear_check(t_v v1);
t_plane	plane_from_normal(t_v point, t_v normal);
t_line	line_c(t_v p1, t_v p2);
t_matrix3d	matrix3d_c(t_v v1, t_v v2, t_v v3);
int	same_side_of_line(t_line line, t_v A, t_v B);

// UTIL4.C
int	same_side_of_plane(t_plane plane, t_v A, t_v B);
t_v	rotate_point(t_v p, t_v v, t_v r);
float	vect_angle(t_v v1, t_v v2);
float	degree_to_radian(float angle);

// UTIL5.C
t_v	v3_sub(t_v a, t_v b);
t_v	v3_clone(t_v v);
t_v	v3_null();
int	v3_is_null(t_v v);
t_v	project_point(t_v point, t_camera camera);

// CAMERA.C
t_camera	camera_c(t_v pos, float eye_canv_dist, float fov);
t_v	camera_get_ac(t_camera camera);
t_v	camera_get_ab(t_camera camera);
t_plane	camera_get_canvas_plane(t_camera camera);
t_v	camera_get_center(t_camera camera);

// CAMERA2.C
t_v	camera_get_norm(t_camera camera);
void	camera_rotate(t_camera *camera, enum e_Direction direction, float amount);
void	camera_move(t_camera *camera, enum e_Direction direction, float amount);

// CAMERA3.C
t_v	get_point_canvas_rel(t_camera camera, t_v p);
t_v	camera_get_d(t_camera camera);

// ITEM.C
t_item	*create_item(enum e_ObjectType type, t_v3_tuple pos_scale, t_v3_tuple axe_color);
t_v	item_get_axis(t_item item);
void	item_draw_axes(t_rtdata data, t_item item);
unsigned int	item_color_hex(t_item item);

// UTIL6.C
t_light	light(enum e_LightType type, t_v color, t_v pos);
t_intersection	intersection(t_v pos, t_v normal, t_line ray, t_item *item);
t_v	map_point_to_physical(t_camera camera, t_v point, float physical_width, float physical_height);
t_v	map_physical_to_camera(t_camera camera, t_v point, float physical_width, float physical_height);
t_v	v3_scale(t_v a, float scale);

// UTIL7.C
t_v	v3_invert(t_v a);
t_v	v3_abs(t_v a);
float	v3_len(t_v a);
t_v	v3_norm(t_v v);
float	v3_norm_squared(t_v v);

// UTIL8.C
t_v	v3_cross(t_v a, t_v b);
float	v3_dot(t_v a, t_v b);
t_v	project_point_onto_line(t_line line, t_v point);
float	point_plane_dist(t_v point, t_plane plane);
float	signed_point_plane_dist(t_v point, t_plane plane);

// UTIL9.C
t_v	project_point_onto_plane(t_v point, t_plane plane);
t_v	matrix_mult_vec(t_matrix3d matrix, t_v v);
t_matrix3d	matrix_scale(t_matrix3d matrix, float scalar);
t_matrix3d	matrix_mult(t_matrix3d m1, t_matrix3d m2);
t_matrix3d	matrix_sub(t_matrix3d m1, t_matrix3d m2);

// UTIL 10.C
t_matrix3d	get_identity_matrix(void);
t_v	get_cylinder_top(t_item cylinder);
t_v	get_cylinder_bottom(t_item cylinder);
t_v	intersect(t_line line, t_plane plane);
int	equals_with_tolerance(float val1, float val2);

// UTIL 11.C
int		vec_color_to_int(t_v color);
void	draw_line(t_scData *scrn, t_v p1, t_v p2, t_v color);
void	draw_square(t_scData *scrn, t_v pos, float size, t_v color);
void	draw_vect(t_scData *scrn, t_v v, t_v color);
void	connect_points(t_scData *scrn, t_v p1, t_v p2, t_item item);

// DRAW_LINE.C
void	draw_line_dda(t_scData *scrn, t_v p1, t_v p2, int color);

// UTIL12.C
void	fill_screen(t_scData *scrn, t_v color);
void	draw_segment(t_rtdata data, t_v p1, t_v p2, t_v color);
void	add_item(t_item item);
void	animate(t_rtdata data);
void	draw(t_rtdata data);

// UTIL13.C
t_v		color_from_int(int color);
void	sphere_vertices(t_v pos, t_v scale, t_item *item);
void	pyramid_vertices(t_v pos, t_v scale, t_item *item);
void	cube_vertices(t_v pos, t_v scale, t_item *item);
void	cylinder_vertices(t_v pos, t_v scale, t_item *item);

// UTIL14.C
void	draw_cube_mappings(t_scData *scrn, t_v mappings[34], t_item item);
void	draw_pyramid_mappings(t_scData *scrn, t_v mappings[34], t_item item);
void	draw_sphere_mappings(t_scData *scrn, t_v mappings[34], t_item item);
void	draw_cylinder_mappings(t_scData *scrn, t_v mappings[34], t_item item);

// UTIL15.C
void	move_item(t_item *item, t_v pos);
void	move_item_to(t_item *item, t_v pos);
void	rotate_item(t_item *item, t_v rot);
void	outline_item(t_rtdata data, t_item item);

// UTIL16.C
void	draw_mappings(t_rtdata data, t_item  item, t_v mappings[34]);
t_line	*gen_rays(t_camera camera, int size, double resolution);
t_intersection	int_null();
int	int_is_null(t_intersection intersection);
t_intersection	intersect_ray_plane(t_line ray, t_plane plane);

// UTIL.17.C
t_intersection	intersect_ray_plane_item(t_line ray, t_item *plane);
t_intersection	intersect_ray_sphere(t_line ray, t_item *sphere);
int	point_inside_square(t_vecfour sqr, t_v point);
void	get_cube_squares(const t_item cube, t_v square_buffer[6][4]);
t_intersection	intersect_ray_cube(t_line ray, t_item *cube);

//UTIL18.C
t_intersection	int_create(t_v pos, t_v norm, t_line ray, t_item *item);
t_vecfour	get_vecfour(t_v p1, t_v p2, t_v p3, t_v p4);
int	point_inside_triangle(t_v s1, t_v s2, t_v s3, t_v point);
t_vecfour	get_pyramid_base_square(t_item pyramid);
void	get_pyramid_triangles(const t_item pyramid, t_v tri_buffer[4][3]);

//UTIL19.C
t_intersection	intersect_ray_pyramid(t_line ray, t_item *pyramid);
t_intersection	ray_intersection(t_line ray, t_item *object);
t_v	compute_lighting(t_rtdata data, t_intersection intr, t_list *lights);

// UTIL20.C
t_intersection	intersect_ray_cylinder(t_line ray, t_item *cylinder);

// UTIL21.C
t_v	compute_specular(t_rtdata data, t_intersection intr, t_list *lights);
t_v	uv_at_chekers(t_v color1, t_v color2, t_v checkers_wh, t_v u_v);
t_v	spherical_map(t_v point, t_item sphere);
t_v	uv_at_image(t_image *rt_image, float u, float v);

// UTIL22.C
t_v	cylindrical_map(t_v point, t_item cylinder);

// UTIL23.C
t_v	get_item_color_image(t_intersection intr);
t_v	get_item_color(t_intersection intr);

// UTIL24.C
t_v	normalize_plane_point(t_v point, t_v origin, t_v normal);
t_v	cartesian_to_sphere(t_v point, t_item sphere);
t_v	checker_pixel_for_plane(t_v3_tuple pt_orig, t_v normal, float step, t_v3_tuple colors);
t_plane	get_intersection_plane(t_intersection intr);

// UTIL25.C
float	new_image_height(t_image *img, float new_width);
t_v	**get_pixels_from_image(t_image img, float target_width);
void	free_pixel_cache(t_v **cache);
t_v3_tuple	tuple(t_v v1, t_v v2);

// UTIL 26.C
t_v	get_item_color_checkerboard(t_intersection intr);
t_intersection	cast_ray(t_rtdata data, t_line ray, int do_draw);
void	raytrace(t_rtdata data);
void	cast_ray_for_screen_coords(t_rtdata data, float x, float y);

// UTIL27.C
void	rotate_to_normal(t_item *item);

// UTIL28.C
t_line	gen_single_ray(t_camera camera, t_terms ts, double i, double j);
void	intersect_ray_cube2(t_terms *ts, t_line ray, t_v cube_squares[6][4], int i);
void	get_intersection_plane2(t_plane *nearest_plane, t_v sq[6][4], int i, t_terms *ts);
void	cast_ray2(t_terms ts, t_rtdata data);

// UTIL29.C
double	get_resolution();

#endif // RT_HEAD_H
