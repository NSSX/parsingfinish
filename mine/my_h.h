#ifndef MY_H
#define MY_H
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <unistd.h>
# include <math.h>
# define RGB(r, g, b)(256 * 256 * (int)(r) + 256 * (int)(g) + (int)(b))
# define WIDTH 400
# define HEIGHT 400
# define CONV_RAD(x)          (x * (M_PI/180))

typedef struct                                                                  s_img
{
  double cos;
  void                            *mlx;
  void                            *win;
  unsigned long           img_color;
  char                            *data;
  void                            *img_ptr;
  int                                     sizeline;
  int                                     bpp;
  int                                     x;
  int                                     y;
  int                                     endian;
  void                            *mlx_ptr;
}                                                                                               t_img;

typedef struct s_vec3d
{
  double x;
  double y;
  double z;
}		t_vec3d;

typedef struct s_effect
{
  t_vec3d bri;
  t_vec3d vec;
  double shadow;
  t_vec3d light;
}t_effect;

typedef struct                  s_obj
{

  t_vec3d                          rot;
  t_vec3d                          color;
  double                          size;
  double                          intens;
  int                            type;
  t_vec3d                          pos;
  struct s_obj            *next;
}                                               t_obj;

typedef struct                  s_env
{
  t_vec3d  sl;
  t_vec3d pos;
  t_effect effect;
  t_obj                           *obj;
  t_obj                           *obj_tmp;
  t_obj *light;
  double                          nl;
  double                          value;
  char *name;
  t_img                           *img;
  void                            *mlx;
  double v2;
  double v;
  void                            *win;
  int                                     height;
  int                                     width;
  t_vec3d color;
  t_vec3d                          eye_pos;
  t_vec3d                          eye_dir;
  t_vec3d                          ray_origin;
  t_vec3d                          ray_dir;
  double sz;

}                                               t_env;

void    pixel_put_to_img(t_env *e, int x, int y);
double  give_shadow(t_env *e);
double  inter_shadow(t_env *e, t_vec3d *lpos);
t_obj   *all_inter(t_env *e);
int             event_mlx(int keycode, t_env *e);
t_vec3d  plus(t_vec3d *a, t_vec3d *b);
  t_vec3d  mult_value(t_vec3d *a, double value);
void    ajust(t_vec3d *vec);
  double  mult(t_vec3d *a, t_vec3d *b);
  t_vec3d a_moin_b(t_vec3d *a, t_vec3d *b);
  t_vec3d x_moin_x(t_vec3d *a, t_vec3d *b);
double         lim(double x, double min, double max);
void    limit_for_vec(t_vec3d *vec, double a, double b);
t_vec3d a_x_b(t_vec3d *a, t_vec3d *b);
void give(t_env *e);
t_vec3d  light_effect(t_env *e);
double  phong_alg(t_obj *obj, t_env *e);
t_vec3d  my_light(t_env *e);
t_vec3d  lambert_alg(t_obj *obj, t_env *e);
t_vec3d  give_vec(t_obj *obj, t_env *e);
void ray_tracer(t_env *e);
void pov(t_env *e);
void init_eye(t_env *e);
void light_number(t_env *e);
t_vec3d eye_or(t_vec3d ray_or, t_vec3d pos);
void            rotate_z(double *x, double *y, double *z, double angle);
void            rotate_x(double *x, double *y, double *z, double angle);
void            rotate_y(double *x, double *y, double *z, double angle);
#endif
