#include "my_h.h"

t_vec3d eye_or(t_vec3d ray_or, t_vec3d pos)
{
  t_vec3d ret;

  ret.x = ray_or.x - pos.x;
  ret.y = ray_or.y - pos.y;
  ret.z = ray_or.z - pos.z;
  return(ret);
}

double ret_val(double a, double b, double det)
{
  return ((-b - sqrt(det)) / a);
}

double  inter_sphere(t_obj *obj, t_env *e)
{
  t_vec3d eye_origin;
  double  a;
  double  b;
  double  c;
  double  det;
  t_vec3d ray_dir;


  ray_dir = (t_vec3d){e->ray_dir.x,e->ray_dir.y,e->ray_dir.z};
  eye_origin = eye_or(e->ray_origin, obj->pos);
  rotate_x(&(eye_origin.x), &(eye_origin.y), &(eye_origin.z),
	   -obj->rot.x);
  rotate_y(&(eye_origin.x), &(eye_origin.y), &(eye_origin.z),
	   -obj->rot.y);
  rotate_z(&(eye_origin.x), &(eye_origin.y), &(eye_origin.z),
	   -obj->rot.z);
  rotate_x(&(ray_dir.x), &(ray_dir.y), &(ray_dir.z),
	   -obj->rot.x);
  rotate_y(&(ray_dir.x), &(ray_dir.y), &(ray_dir.z),
	   -obj->rot.y);
  rotate_z(&(ray_dir.x), &(ray_dir.y), &(ray_dir.z), -obj->rot.z);
  a = mult(&(ray_dir), &(ray_dir));
  b = mult(&eye_origin, &(ray_dir));
  c = mult(&eye_origin, &eye_origin) - obj->size * obj->size;
  det = b * b - a * c;
  if (det < 0.0001)
    return (-1);
  return (ret_val(a,b,det));
}


double  inter_plan(t_obj *obj, t_env *e)
{
  double  value;

  value = -((mult(&obj->rot, &(e->ray_origin)) - mult(&obj->rot, &obj->pos)) \
	    / mult(&obj->rot, &(e->ray_dir)));
  if (value < 0.0001)
    return (-1);
  return (value);
}

double  inter_cyl(t_obj *obj, t_env *e)
{
  t_vec3d  eye_origin;
  double  a;
  double  b;
  double  c;
  double  det;
  double angle = 90;
  t_vec3d ray_dir;


  ray_dir = (t_vec3d){e->ray_dir.x,e->ray_dir.y,e->ray_dir.z}; 
  eye_origin = eye_or(e->ray_origin, obj->pos);
  rotate_x(&(eye_origin.x), &(eye_origin.y), &(eye_origin.z),
  	         -obj->rot.x);
   rotate_y(&(eye_origin.x), &(eye_origin.y), &(eye_origin.z),
         -obj->rot.y);
   rotate_z(&(eye_origin.x), &(eye_origin.y), &(eye_origin.z),
         -obj->rot.z);
   rotate_x(&(ray_dir.x), &(ray_dir.y), &(ray_dir.z),
       -obj->rot.x);
   rotate_y(&(ray_dir.x), &(ray_dir.y), &(ray_dir.z),
         -obj->rot.y);
   rotate_z(&(ray_dir.x), &(ray_dir.y), &(ray_dir.z), -obj->rot.z);
  a = ray_dir.x * ray_dir.x + ray_dir.z * ray_dir.z;
  b = ray_dir.x * eye_origin.x + ray_dir.z * eye_origin.z;
  c = eye_origin.x * eye_origin.x + eye_origin.z * eye_origin.z - obj->size * obj->size;
  det = b * b - a * c;
  if (det < 0.0001)
    return (-1);
  return (ret_val(a,b,det));
}

double  inter_cone(t_obj *obj, t_env *e)
{
  t_vec3d  eye_origin;
  double  a;
  double  b;
  double  c;
  double  det;
  t_vec3d ray_dir;


  ray_dir = (t_vec3d){e->ray_dir.x,e->ray_dir.y,e->ray_dir.z};
  eye_origin = eye_or(e->ray_origin, obj->pos);
  rotate_x(&(eye_origin.x), &(eye_origin.y), &(eye_origin.z),
	   -obj->rot.x);
  rotate_y(&(eye_origin.x), &(eye_origin.y), &(eye_origin.z),
	   -obj->rot.y);
  rotate_z(&(eye_origin.x), &(eye_origin.y), &(eye_origin.z),
	   -obj->rot.z);
  rotate_x(&(ray_dir.x), &(ray_dir.y), &(ray_dir.z),
	   -obj->rot.x);
  rotate_y(&(ray_dir.x), &(ray_dir.y), &(ray_dir.z),
  -obj->rot.y);
  rotate_z(&(ray_dir.x), &(ray_dir.y), &(ray_dir.z), -obj->rot.z);
  a = ray_dir.x * ray_dir.x - ray_dir.y * ray_dir.y + ray_dir.z * ray_dir.z;
  b = ray_dir.x * eye_origin.x - ray_dir.y * eye_origin.y + ray_dir.z * eye_origin.z;
  c = eye_origin.x * eye_origin.x + eye_origin.z * eye_origin.z - eye_origin.y * eye_origin.y;
  det = b * b - a * c;
  if (det < 0.0001)
    return (-1);
  return (ret_val(a,b,det));
}

t_obj   *all_inter(t_env *e)
{
  t_obj   *my_obj;
  t_obj   *obj;
  double  value;

  obj = NULL;
  my_obj = e->obj;
  value = e->value;
  while (my_obj)
    {
      if (my_obj->type == 0)
	value = inter_plan(my_obj, e);
      else if (my_obj->type == 1)
	value = inter_sphere(my_obj, e);
      else if (my_obj->type == 3)
        value = inter_cyl(my_obj, e);
      else if (my_obj->type == 2)
        value = inter_cone(my_obj, e);
      if (value > 0.0001 && value < e->value)
        {
          obj = my_obj;
          e->value = value;
        }
      my_obj = my_obj->next;
    }
  return (obj);
}
