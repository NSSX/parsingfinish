#include "libft.h"
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

typedef struct s_vec3d
{
	double x;
	double y;
	double z;

}t_vec3d;

typedef struct s_obj
{
	double type;
	double size;
	t_vec3d *color;
	t_vec3d *pos;
  	t_vec3d *rot;
  	struct s_obj *next;
}		t_obj;

typedef struct s_main
{
	t_obj *obj;
}		t_main;

t_obj *create(void)
{
	t_obj *obj;

	obj = malloc(sizeof(t_obj));
	obj->type = 0;
	obj->size = 0;
	obj->pos = &(t_vec3d){0,0,0};
	obj->color = &(t_vec3d){0,0,0};
	obj->rot = &(t_vec3d){0,0,0};
	obj->next = NULL;
	return(obj);
}

t_obj *add_list(t_main *main)
{
	t_obj *actual;
	t_obj *new_obj;
	int i ;

	if (!main)
	  return NULL;
        actual = main->obj;
	i = 0;
	if (!actual)
	  {
	    main->obj = create();
	    return (main->obj);
	  }
	while(actual->next)
	{
	  actual = actual->next;
	}
	new_obj = create();
	actual->next = new_obj;
	return(new_obj);
}

char *chaine(char *ch)
{
	int i;

	i = 0;
	while(ch[i] != '\0')
	  {
	    if(ch[i] == '}')
	      {
		ch = ft_strsub(ch, 0, i);
		return(ch);
	      }
	    i++;
	  }
	return (NULL);
}

char *chaine2(char *ch)
{
  int i;
 
  i = 0;
  while(ch[i] != '\0')
    {
      if(ch[i] == ')')
	{
	  ch = ft_strsub(ch, 0, i + 1);
	  return(ch);
	}
      i++;
    }
  return (NULL);
}

char    *ft_strjoin_carac(char const *s1, char s2)
{
  char            *chaine;
  int                     index;
  int                     index2;

  index2 = 0;
  index = 0;
  if (!s1 || !s2)
    return (NULL);
  chaine = ft_memalloc(sizeof(char) * (ft_strlen(s1) + 10));
  if (chaine == NULL)
    return (NULL);
  while (s1[index] != '\0')
    {
      chaine[index] = s1[index];
      index++;
    }
  chaine[index] = s2;
  index++;
  index2++;
  chaine[index] = '\0';
  return (chaine);
}

void err(void)
{
  ft_putstr("BAD PARSING POTO\n");
  exit(1);
}

t_vec3d *vec3d(t_main *main, char *chaine)
{
  int i;
  char *val1;
  char *val2;
  char *val3;
  t_vec3d *tab;


  tab = malloc(sizeof(int) * 4);
  val1 = ft_memalloc(ft_strlen(chaine));
  val2 =  ft_memalloc(ft_strlen(chaine));
  val3 = ft_memalloc(ft_strlen(chaine));
  i = 0;
  while(chaine != '\0')
    {
      if(chaine[i] == '(')
	{
	  if(chaine[i + 1] >= '0' && chaine[i + 1] <= '9')
	      i++;
	  else 
	      err();
	  while(chaine[i] != ',' && chaine[i] != '\0')
	    {
      	      val1 = ft_strjoin_carac(val1, chaine[i]);
	      i++;
	    }
	  if(chaine[i + 1] >= '0' && chaine[i + 1] <= '9')
	    i++;
          else
	    err();
          while(chaine[i] != ',' && chaine[i] != '\0')
            {
              val2 = ft_strjoin_carac(val2, chaine[i]);
              i++;
            }
	  if(chaine[i + 1] >= '0' && chaine[i + 1] <= '9')
            i++;
          else
            err();
          while(chaine[i] != ',' && chaine[i] != '\0' && chaine[i] != ')')
            {
              val3 = ft_strjoin_carac(val3, chaine[i]);
              i++;
            }
	  tab->x = ft_atoi(val1);
	  tab->y = ft_atoi(val2);
	  tab->z = ft_atoi(val3);
	  return(tab);
	}
      i++;
    }
  return (NULL);
}

double get_single_var(char *chaine)
{
  int i;
  double val;
  char *tmp;


  tmp = ft_memalloc(sizeof(char) * ft_strlen(chaine));
  i = 0;
  val = 0;
  while(chaine[i] != '\0')
    {
      if(chaine[i] == '(')
	{
	  if(chaine[i + 1] >= '0' && chaine[i + 1] <= '9')
	    i++;
	  while(chaine[i] >= '0' && chaine[i] <= '9' && chaine[i] != '\0')
	    {
	      tmp = ft_strjoin_carac(tmp, chaine[i]);
	      i++;
	    }
	  return(ft_atoi(tmp));
	}
      i++;
    }
  return (val);
}

void traitement(char *file, t_main *main)
{
	char *here;
	char *here2;
	char *temp;
	t_vec3d *pos;
	int end;
	t_obj *obj;

	end = 0;
	if((here = ft_strstr(file,"sphere{\n")) && here != NULL)
	{
	  obj = add_list(main);
		temp = chaine(here);
		here[0] = 'W';
		if(temp == NULL)
			return;
		if((here2 = ft_strstr(temp,"pos(")) && here2 != NULL)
		  {
		    here2 = chaine2(here2);
		    obj->pos = vec3d(main, here2);
		  }
		if((here2 = ft_strstr(temp,"color(")) && here2 != NULL)
		  {
		    here2 = chaine2(here2);
		    obj->color = vec3d(main, here2);
		  }
		if((here2 = ft_strstr(temp,"size(")) && here2 != NULL)
		  {
		    here2 = chaine2(here2);
		    obj->size = get_single_var(here2);
		  }
		if((here2 = ft_strstr(temp,"rot(")) && here2 != NULL)
		  {
		    here2 = chaine2(here2);
		     obj->rot = vec3d(main, here2);
		  }
		obj->type = 1;
		end++;
	}
	if((here = ft_strstr(file,"plane{\n")) && here != NULL)
	  {
	    obj = add_list(main);
	    temp = chaine(here);
	    here[0] = 'W';
	    if(temp == NULL)
	      return;
	    if((here2 = ft_strstr(temp,"pos(")) && here2 != NULL)
	      {
		here2 = chaine2(here2);
		obj->pos = vec3d(main, here2);
	      }
	    if((here2 = ft_strstr(temp,"color(")) && here2 != NULL)
	      {
		here2 = chaine2(here2);
		obj->color = vec3d(main, here2);
	      }
	    if((here2 = ft_strstr(temp,"size(")) && here2 != NULL)
	      {
		here2 = chaine2(here2);
		obj->size = get_single_var(here2);
	      }
	    if((here2 = ft_strstr(temp,"rot(")) && here2 != NULL)
	      {
		here2 = chaine2(here2);
		obj->rot = vec3d(main, here2);
	      }
	    obj->type = 0;
	    end++;
	  }
	if(end != 0)
		traitement(file, main);
}

void ultimate_read(t_main *main)
{
  t_obj *tmp;
  int i;

  i = 1;
  tmp = main->obj;
  while(tmp)
    {
      printf("\n\n----- OBJET NUMERO %d -------\n\n",i);
      printf("POS : (%f,%f,%f)\n",tmp->pos->x, tmp->pos->y,tmp->pos->z);
      printf("COLOR : (%f,%f,%f)\n",tmp->color->x, tmp->color->y,tmp->color->z);
      printf("ROTATION : (%f,%f,%f)\n",tmp->rot->x, tmp->rot->y,tmp->rot->z);
      printf("TYPE : %f\n",tmp->type);
      printf("SIZE : %f\n",tmp->size);
      printf("----------------------");
	i++;
      tmp = tmp->next;
    }
}

int main(int argc, char **argv)
{
	int             fd;
	char *yt;
	char *file;
	int ret;
	t_main main;


      	main.obj = NULL;
	ret = 0;
	file = (char *)malloc(sizeof(char) * 1);
	if(argc != 2)
	{
		ft_putstr("bad arg\n");
		exit(1);
	}
	fd = 0;
	fd = open(argv[1], O_RDONLY);
	while ((ret = get_next_line(fd, &yt)) && ret != -1)
	{
		file = ft_strjoin(file, yt);
		file = ft_strjoin(file, "\n");
	}
	traitement(file, &main);
	ultimate_read(&main);
	return (0);
}
