 #include "my_h.h"

void give_effect(t_env *e)
{
  e->effect.vec = give_vec(e->obj_tmp, e);
  e->effect.shadow = give_shadow(e);
  e->effect.light = my_light(e);
  e->effect.bri = light_effect(e);
  e->effect.light = mult_value(&(e->effect.light), e->effect.shadow);
  e->effect.bri = a_x_b(&(e->effect.bri), &(e->effect.light));
}

void    all_effect(t_env *e)
{
  give_effect(e);
  //brillance
  e->color = plus(&(e->color), &(e->effect.bri));
  limit_for_vec(&(e->color), 0, 1);
  e->color = a_x_b(&(e->color), &(e->effect.light));
}

int             expose_hook(t_env *e)
{
  ray_tracer(e);
  return (1);
}
//REGARDE TJRS DANS LA DIRECTION
int event_mlx(int keycode, t_env *e)
{
  static int etat;

  if(!etat)
    etat = 3;
  if(keycode == 65307)
       exit(1);
   if(keycode == 65362)
     {
       //       e->eye_dir.y += 5;
       e->v2 += 0.2;
     }
  if(keycode == 65363)
    {
      //fleche droite;
      e->v += 0.2;
//      e->eye_dir.x -= 5;    
    }
  if(keycode == 65364)
    {
      e->v2 -= 0.2;
      // e->eye_dir.y -= 5;
    }
  if(keycode == 65361)
    {
            e->v -= 0.2;
      //    e->eye_dir.x += 5;
    }
  if(keycode == 100)
    {
      e->v += M_PI / 2;
      //droite
    }
    if(keycode == 97)
      e->v -= M_PI / 2;

  if(keycode == 119)
    {
      e->eye_pos.z -= 5;
      if(e->eye_pos.x > e->eye_dir.x)
	{
	  e->eye_pos.x -= 5;
	   e->eye_dir.x -= 2;
	}
      else if(e->eye_pos.x < e->eye_dir.x)
	{
	  e->eye_pos.x += 5;
	  e->eye_dir.x += 3;
	}
     }  
  if(keycode == 115)
    {     
      e->eye_pos.z += 5;
    } 
  if(keycode == 44)
    {
      t_obj   *obj;

      obj = e->obj;
      while (obj)
	{
	  if (obj->type == etat)
	    {
	      obj->rot.z += 5;
	    }
	  obj = obj->next;
	}
    }
  if(keycode == 46)
    {
      t_obj   *obj;

      obj = e->obj;
      while (obj)
        {
	      if (obj->type == etat)
		{
		  obj->rot.z -= 5;
		}
          obj = obj->next;
        }
    }
  if(keycode == 39)
    {
      t_obj   *obj;

      obj = e->obj;
      while (obj)
        {
          if (obj->type == etat)
            {
              obj->rot.x -= 5;
            }
          obj = obj->next;
        }
    }
  if(keycode == 47)
    {
      t_obj   *obj;

      obj = e->obj;
      while (obj)
        {
          if (obj->type == etat)
            {
              obj->rot.x += 5;
            }
          obj = obj->next;
        }
    }
  if(keycode == 32)
    {
      if(etat == 3)
	etat = 1;
      else
	etat++;
      printf("%d\n",etat);
    }
  printf("%d\n",keycode);
  ray_tracer(e);
  return(1);
}

int main(int ac, char **av)
{
  t_env e;

  give(&e);
  parsing(&e, ac, av[1]);
  init_eye(&e);
  light_number(&e);
  pov(&e);
  e.v = 0;
  e.v2 = 0;
  e.win =  mlx_new_window(e.mlx, e.width, e.height, e.name);
  e.nl = 1 / e.nl;
  mlx_expose_hook(e.win, expose_hook, &e);;
  mlx_key_hook(e.win, event_mlx, &e);
  mlx_loop(e.mlx);
  return(0);
}
