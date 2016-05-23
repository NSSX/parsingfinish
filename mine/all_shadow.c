#include "my_h.h"

int ret_val2(double a, double b, double det, t_env *e)
{
  det = (-b - sqrt(det)) / a;
  return ((det > 0.001) && (det < e->sz));
}

int             shadow_cyl(t_obj *obj, t_env *e)
{
  t_vec3d  eye_origin;
  double  a;
  double  b;
  double  c;
  double  det;
  t_vec3d sl;

  sl = (t_vec3d){e->sl.x,e->sl.y,e->sl.z};
  eye_origin = eye_or(e->pos, obj->pos);
   rotate_x(&(eye_origin.x), &(eye_origin.y), &(eye_origin.z),
	   -obj->rot.x);
  rotate_y(&(eye_origin.x), &(eye_origin.y), &(eye_origin.z),
	   -obj->rot.y);
  rotate_z(&(eye_origin.x), &(eye_origin.y), &(eye_origin.z),
	   -obj->rot.z);
  rotate_x(&(sl.x), &(sl.y), &(sl.z),
	   -obj->rot.x);
  rotate_y(&(sl.x), &(sl.y), &(sl.z),
	   -obj->rot.y);
  rotate_z(&(sl.x), &(sl.y), &(sl.z),
  -obj->rot.z);
  a = sl.x * sl.x + sl.z * sl.z;
  b = sl.x * eye_origin.x + sl.z * eye_origin.z;
  c = eye_origin.x * eye_origin.x + eye_origin.z * eye_origin.z - obj->size * obj->size;
  det = b * b - a * c;
  if (det > 0.001)
    return(ret_val2(a,b,det,e));
  return (0);
}

int             shadow_sphere(t_obj *obj, t_env *e)
{
  t_vec3d  eye_origin;
  double  a;
  double  b;
  double  c;
  double  det;
  t_vec3d sl;

  sl = (t_vec3d){e->sl.x,e->sl.y,e->sl.z};
  eye_origin = eye_or(e->pos, obj->pos);
  rotate_x(&(eye_origin.x), &(eye_origin.y), &(eye_origin.z),
           -obj->rot.x);
  rotate_y(&(eye_origin.x), &(eye_origin.y), &(eye_origin.z),
           -obj->rot.y);
  rotate_z(&(eye_origin.x), &(eye_origin.y), &(eye_origin.z),
           -obj->rot.z);
  rotate_x(&(sl.x), &(sl.y), &(sl.z),
           -obj->rot.x);
  rotate_y(&(sl.x), &(sl.y), &(sl.z),
           -obj->rot.y);
  rotate_z(&(sl.x), &(sl.y), &(sl.z),
	   -obj->rot.z);
  a = mult(&(sl), &(sl));
  b = mult(&eye_origin, &(sl));
  c = mult(&eye_origin, &eye_origin) - obj->size * obj->size;
  det = b * b - a * c;
  if (det > 0.001)
    return(ret_val2(a,b,det,e));
  return (0);
}

int             shadow_cone(t_obj *obj, t_env *e)
{
  t_vec3d  eye_origin;
  double  a;
  double  b;
  double  c;
  double  det;
  t_vec3d sl;

  sl = (t_vec3d){e->sl.x,e->sl.y,e->sl.z};
  eye_origin = eye_or(e->pos, obj->pos);
  rotate_x(&(eye_origin.x), &(eye_origin.y), &(eye_origin.z),
           -obj->rot.x);
  rotate_y(&(eye_origin.x), &(eye_origin.y), &(eye_origin.z),
           -obj->rot.y);
  rotate_z(&(eye_origin.x), &(eye_origin.y), &(eye_origin.z),
           -obj->rot.z);
  rotate_x(&(sl.x), &(sl.y), &(sl.z),
           -obj->rot.x);
  rotate_y(&(sl.x), &(sl.y), &(sl.z),
           -obj->rot.y);
  rotate_z(&(sl.x), &(sl.y), &(sl.z),
	   -obj->rot.z);
  a = sl.x * sl.x - sl.y * sl.y + sl.z * sl.z;
  b = sl.x * eye_origin.x - sl.y * eye_origin.y + sl.z * eye_origin.z;
  c = eye_origin.x * eye_origin.x + eye_origin.z * eye_origin.z - eye_origin.y * eye_origin.y;
  det = b * b - a * c;
  if (det > 0.001)
    return(ret_val2(a,b,det,e));
  return (0);
}

double  give_shadow(t_env *e)
{
  t_obj   *obj;
  double  my_shadow;
  double  give;

  obj = e->obj;
  my_shadow = 1;
  while (obj)
    {
      if (obj->type == 8)
        {
          give = inter_shadow(e, &obj->pos);
          if (give == 1)
            my_shadow -= (obj->intens + e->nl) / 2;
        }
      obj = obj->next;
    }
  return (lim(my_shadow, 0, 1));
}


double  inter_shadow(t_env *e, t_vec3d *my_pos)
{
  t_obj   *subs;
  int             give;
  int             my_shadow;

  subs = e->obj;
  give = 0;
  my_shadow = 0;
  e->sl = a_moin_b(my_pos, &(e->pos));
  e->sz = sqrt(e->sl.x * e->sl.x + e->sl.y * e->sl.y + e->sl.z * e->sl.z);
  e->sl.x = e->sl.x / e->sz;
  e->sl.y = e->sl.y / e->sz;
  e->sl.z = e->sl.z / e->sz;
  while (subs)
    {
      if (subs->type == 1)
          give = shadow_sphere(subs, e);
      else if (subs->type == 3)
        give = shadow_cyl(subs, e);
      else if (subs->type == 2)
	give = shadow_cone(subs, e);
      if(give == 1)
	  my_shadow = 1;
      subs = subs->next;
    }
  return (my_shadow);
}

