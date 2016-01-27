#include "struct.h"
#include "get_next_line.h"
#include <mlx.h>
#include <stdio.h>
#include "libft/libft.h"
//Const fill_rect
#define RECTX 10
#define RECTY 10
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "struct.h"
#include <math.h>
# define RGB(r, g, b)(256 * 256 * (int)(r) + 256 * (int)(g) + (int)(b))
#define WIDTH 1500
#define HEIGTH 1500

int couleur(double t)
{
  return ((RGB(127.5 * (cos(t) + 1), 127.5 * (sin(t) + 1), 127.5 * (1 - cos(t)))));
}

t_line *give_line(float xi, float yi, float xf, float yf)
{
  t_line *line;

  line = (t_line *)malloc(sizeof(t_line) * 12);
  line->x = xi ;
  line->y = yi ;
  line->dx = xf - xi ;
  line->dy = yf - yi ;
  line->xinc = ( line->dx > 0 ) ? 1 : -1;
  line->yinc = ( line->dy > 0 ) ? 1 : -1;
  line->dx = abs(line->dx);
  line->dy = abs(line->dy);
  return (line);
}

t_line *first_while(t_line *line)
{
  line->x += line->xinc ;
  line->cumul += line->dy ;
  if (line->cumul >= line->dx)
    {
      line->cumul -= line->dx ;
      line->y += line->yinc ;
    }
  return (line);
}


t_line *second_while(t_line *line)
{
  line->y += line->yinc ;
  line->cumul += line->dx ;
  if (line->cumul >= line->dy)
    {
      line->cumul -= line->dy ;
      line->x += line->xinc ;
    }
  return (line);
}

t_line *norme_line(t_line *line)
{
  line->cumul = line->dy / 2 ;
  line->i = 1;
  return (line);
}

void draw_line_on_img(t_img *myimg,float xi, float yi, float xf, float yf, int color)
{
  t_line *line;
 
  line = give_line(xi, yi, xf, yf); 
  my_pixel_put_to_image(myimg, line->x, line->y, color);
  if (line->dx > line->dy) 
    {
      line->cumul = line->dx / 2 ;
      line->i = 1;
      while(line->i <= line->dx)
	{
	  line = first_while(line);
	  my_pixel_put_to_image(myimg, line->x, line->y, color);
	  line->i++;
	}
    }
  else 
    {
      line = norme_line(line);
      while(line->i <= line->dy)
	{
	  line = second_while(line);
	  my_pixel_put_to_image(myimg, line->x, line->y, color);
	  line->i++;
	}
    }
}

static char *ft_join(char const *s1, char const *s2, int len1, int len2)
{
  char *join;
  int i;
  int j;

  i = 0;
  j = 0;
  join = malloc(sizeof(char) * (len1 + len2) + 1);
  while (s1[i] != '\0')
    {
      join[i] = s1[i];
      i++;
    }
  while (s2[j] != '\0')
    {
      join[i] = s2[j];
      i++;
      j++;
    }
  join[i] = '\0';
  return (join);
}

char *ft_strjoins(char const *s1, char const *s2)
{
  int len1;
  int len2;
  char *join;

  if (!s1 || !s2)
    return (NULL);
  len1 = ft_strlen(s1);
  len2 = ft_strlen(s2);
  join = ft_join(s1, s2, len1, len2);
  return (join);
}

void place_img(t_struct *param, float xd, float yd)
{
  mlx_destroy_image(param->mlx, param->img->img_ptr);
  param->img->img_ptr = mlx_new_image(param->mlx, WIDTH, HEIGTH);
  set_coordq(param, xd, yd, 0);
  draw_with_tab_on_img(param->coord, param->i, param->maxline, param);
  mlx_put_image_to_window(param->mlx, param->win, param->img->img_ptr, 0, 0);
}


void img_move(int keycode, t_struct *param)
{
  if(keycode == 2)
    {
      param->event->xd += 40;
      place_img(param, param->event->xd, param->event->yd);
    }
  if(keycode == 1)
    {
      param->event->yd += 40;
      place_img(param, param->event->xd, param->event->yd);
    }
  if(keycode == 13)
    {
       param->event->yd -= 40;
      place_img(param, param->event->xd, param->event->yd);
    }
  if(keycode == 0)
    {
       param->event->xd -= 40;
      place_img(param, param->event->xd, param->event->yd);
    }
}

void img_zoom(int keycode, t_struct *param)
{
  if(keycode == 12)
    {
      if(param->zoom < 5)
        {
          param->zoom += 1;
        }
      else
        param->zoom += 5;
      place_img(param, param->event->xd, param->event->yd);
    }
  if(keycode == 14)
    {
      if(param->zoom >= 10)
        param->zoom -= 5;
      else
        param->zoom -= 0.5;
      place_img(param, param->event->xd, param->event->yd);
    }
}

void img_other_view(int keycode, t_struct *param)
{
  if(keycode == 124)
    {
      mlx_destroy_image(param->mlx, param->img->img_ptr);
      param->img->img_ptr = mlx_new_image(param->mlx, WIDTH, HEIGTH);
      set_coordp(param, 10, 10, 0);
      draw_with_tab_on_img(param->coord, param->i, param->maxline, param);
      mlx_put_image_to_window(param->mlx, param->win, param->img->img_ptr, 0, 0);
    }
  if(keycode == 123)
    {
      mlx_destroy_image(param->mlx, param->img->img_ptr);
      param->img->img_ptr = mlx_new_image(param->mlx, WIDTH, HEIGTH);
      set_coordp(param, param->event->xd, param->event->yd, 0);
      draw_with_tab_on_img(param->coord, param->i, param->maxline, param);
      mlx_put_image_to_window(param->mlx, param->win, param->img->img_ptr, 0, 0);
    }
}

void img_other(int keycode, t_struct *param)
{
  if(keycode == 17)
    {
      mlx_destroy_image(param->mlx, param->img->img_ptr);
      param->img->img_ptr = mlx_new_image(param->mlx, WIDTH, HEIGTH);
      set_coordx(param, param->event->xd, param->event->yd, 0);      
      draw_with_tab_on_img(param->coord, param->i, param->maxline, param);
      mlx_put_image_to_window(param->mlx, param->win, param->img->img_ptr, 0, 0);
    }
  if(keycode == 36)
    {
      place_img(param, param->event->xd, param->event->yd);
    }
}

int event_mlx(int keycode, t_struct *param)
{
  if(keycode == 53)
    exit(1); 
  img_move(keycode, param);
  img_zoom(keycode, param);
  img_other_view(keycode, param);
  img_other(keycode, param);
  return (0);
}

char **create_tab(char *argv, char **tab)
{
  char *line;
  char *yt;
  int fd;
  int ret;

  fd = 0;
  ret = 0;
  fd = open(argv, O_RDONLY);
  line = (char *)malloc(sizeof(char) * 2);
  while((ret = get_next_line(fd,&yt)))
    {
      line = ft_strjoins(line,yt);
      line = ft_strjoins(line, " \n ");
    }
  tab = ft_strsplit(line, ' ');
  return (tab);
}

char ***create_coord_tab(char **tab, char ***coord, int i)
{
  int index;
  
  index = 0;
  coord = (char ***)malloc(sizeof(char **) * i + 1);
  while(index < i)
    {
      coord[index] = (char **)malloc(sizeof(char *) * 5);
      index++;
    }
  index = 0;
  while(index < i)
    {
      coord[index][0] = (char *)malloc(sizeof(char) * 5);
      coord[index][1] = (char *)malloc(sizeof(char) * 5);
      coord[index][2] = tab[index];
      index++;
    }
  return (coord);
}

t_coor *give_coor(t_coor *coor, t_struct *param)
{
 coor->x = coor->xdep;
  coor->y = coor->ydep;
  coor->x -= param->zoom * 0.86;
  coor->y += param->zoom * 0.5;
  coor->xdep = coor->x;
  coor->ydep = coor->y;
  return (coor);
}

t_coor *start_coor(t_coor *coor, int x, int y)
{
  coor = (t_coor *)malloc(sizeof(t_coor) * 12);  
  coor->v = 0;
  coor->j = 0;
  coor->x = x;
  coor->y = y;
  coor->xdep =  x;
  coor->ydep =  y;
  return (coor);
}

t_coor *else_coor(t_coor *coor, t_struct *param, int index)
{
  coor->x += param->zoom * 0.86;
  coor->y += param->zoom * 0.5;
  if(param->coord[index][2][0] != '0')
    {
      coor->v = ft_atoi(param->coord[index][2]);
      coor->xtemp  = coor->x;
      coor->ytemp = coor->y - (coor->v * param->zoom);
      coor->j++;
    }
  return (coor);
}

char ***set_coordq(t_struct *param, float x, float y, int index)
{
  t_coor *coor;

  coor = start_coor(coor, x, y);
  while(index < param->i)
    {
      if(param->coord[index][2][0] == '\n')
	coor = give_coor(coor, param);
      else
	else_coor(coor, param, index);
      if(coor->j == 0)
	{
	  param->coord[index][0] = ft_itoa(coor->x);
	  param->coord[index][1] = ft_itoa(coor->y);
	}
      else
	{
	  param->coord[index][0] = ft_itoa(coor->xtemp);
	  param->coord[index][1] = ft_itoa(coor->ytemp);
	  coor->j = 0;
	}
      index++;
    }
  free(coor);
  return (param->coord);
}

t_coor *give_coorx(t_coor *coor, t_struct *param)
{
  coor->x = coor->xdep;
  coor->y = coor->ydep;
  coor->x -= param->zoom;
  coor->y += param->zoom;
  coor->xdep = coor->x;
  coor->ydep = coor->y;
  return (coor);
}

t_coor *start_coorx(t_coor *coor, int x, int y)
{
  coor = (t_coor *)malloc(sizeof(t_coor) * 12);
  coor->v = 0;
  coor->j = 0;
  coor->x = x;
  coor->y = y;
  coor->xdep =  x;
  coor->ydep =  y;
  return (coor);
}

t_coor *else_coorx(t_coor *coor, t_struct *param, int index)
{
  coor->x += param->zoom;
  coor->y += param->zoom;
  if(param->coord[index][2][0] != '0')
    {
      coor->v = ft_atoi(param->coord[index][2]);
      coor->xtemp  = coor->x;
      coor->ytemp = coor->y - ((coor->v * 2)  + 1);;
      coor->j++;
    }
  return (coor);
}

char ***set_coordx(t_struct *param, float x, float y, int index)
{
  t_coor *coor;

  coor = start_coorx(coor, x, y);
  while(index < param->i)
    {
      if(param->coord[index][2][0] == '\n')
        coor = give_coorx(coor, param);
      else
        else_coorx(coor, param, index);
      if(coor->j == 0)
        {
          param->coord[index][0] = ft_itoa(coor->x);
          param->coord[index][1] = ft_itoa(coor->y);
        }
      else
        {
          param->coord[index][0] = ft_itoa(coor->xtemp);
          param->coord[index][1] = ft_itoa(coor->ytemp);
          coor->j = 0;
        }
      index++;
    }
  free(coor);
  return (param->coord);
}

t_coor *give_coorp(t_coor *coor, t_struct *param)
{
  coor->x = coor->xdep;
  coor->y = coor->ydep;
  coor->y += param->zoom;
   coor->xdep = coor->x;
  coor->ydep = coor->y;
  return (coor);
}

t_coor *start_coorp(t_coor *coor, int x, int y)
{
  coor = (t_coor *)malloc(sizeof(t_coor) * 12);
  coor->v = 0;
  coor->j = 0;
  coor->x = x;
  coor->y = y;
  coor->xdep =  x;
  coor->ydep =  y;
  return (coor);
}

t_coor *else_coorp(t_coor *coor, t_struct *param, int index)
{
  coor->x += param->zoom;
  if(param->coord[index][2][0] != '0')
    {
      coor->v = ft_atoi(param->coord[index][2]);
      coor->xtemp  = coor->x + coor->v;
      coor->ytemp = coor->y - ((coor->v * 2)  + 1);
      coor->j++;
    }
  return (coor);
}

char ***set_coordp(t_struct *param, float x, float y, int index)
{
  t_coor *coor;

  coor = start_coorp(coor, x, y);
  while(index < param->i)
    {
       if(param->coord[index][2][0] == '\n')
	 coor = give_coorp(coor, param);
       else
	 else_coorp(coor, param, index);
       if(coor->j == 0)
	 {
	   param->coord[index][0] = ft_itoa(coor->x);
	   param->coord[index][1] = ft_itoa(coor->y);
	 }
       else
	 {
	   param->coord[index][0] = ft_itoa(coor->xtemp);
	   param->coord[index][1] = ft_itoa(coor->ytemp);
	   coor->j = 0;
	 }
      index++;
    }
  free(coor);
  return (param->coord);
}

int testa(int x1,int y1,int x2,int y2)
{
  if((x1 >= WIDTH) || (x2 >= WIDTH) || (y1 >= WIDTH) || (y2 >= WIDTH) || (y1 <= 0) || (y2 <= 0) || (x1 <= 0) || (x2 <= 0))
    return (0);
  return (1);
}

int color2(int val1, int val2, int color)
{
  if(val1 + val2 >= 30 && val1 + val2 <= 60)
    color = 0x167341;
  else if(val1 + val2 >= 61 && val1 + val2 <= 90)
    color = 0xDE5A39;
  else if(val1 + val2 >= 91 && val1 + val2 <= 130)
    color = 0x5D6ADC;
  else if(val1 + val2 >= 131 && val1 + val2 <= 200)
    color = 0xFF99CC;
  else if(val1 + val2 >= 201 && val1 + val2 <= 350)
    color = 0xDF571D;
  else
    color = 0xFFFFFF;
  return (color);
}

int give_color(int val1, int val2)
{
  int color;

  color = 0;
  if(val1 + val2 < 0)
    color = 255 + (val1 + val2);
  else if(val1 + val2 >= 0 && val1 + val2 <= 3)
    color = 0xCCCC00;
  else if(val1 + val2 >= 4 && val1 + val2 <= 8)
    color = 0x4C9900;
  else if(val1 + val2 >= 9 && val1 + val2 <= 13)
    color = 0xFF8000;
  else if(val1 + val2 >= 14 && val1 + val2 <= 21)
    color = 0xFF6666;
  else if(val1 + val2 >= 22 && val1 + val2 <= 29)
    color = 0x6600CC;
   else
     color = color2(val1, val2, color);
  return (color);
}

void first_part(char ***coord, int index, t_struct *param)
{
  t_temp *temp;

  temp = (t_temp *)malloc(sizeof(t_temp) * 12);
  temp->x1 = ft_atoi(coord[index][0]);
  temp->y1 = ft_atoi(coord[index][1]);
  temp->x2 = ft_atoi(coord[index + 1][0]);
  temp->y2 = ft_atoi(coord[index + 1][1]);
  temp->val1 = ft_atoi(coord[index][2]);
  temp->val2 = ft_atoi(coord[index + 1][2]);
  temp->color = give_color(temp->val1, temp->val2);
  if(testa(temp->x1,temp->y1,temp->x2,temp->y2))
    draw_line_on_img(param->img,temp->x1, temp->y1, temp->x2, temp->y2, temp->color);
  free(temp);
}


void second_part(char ***coord, int index, int maxline, t_struct *param)
{
  t_temp *temp;
  
  temp = (t_temp *)malloc(sizeof(t_temp) * 12);
  temp->x1 = ft_atoi(coord[index][0]);
  temp->y1 = ft_atoi(coord[index][1]);
  temp->x2 = ft_atoi(coord[index + maxline + 1][0]);
  temp->y2 = ft_atoi(coord[index + maxline + 1][1]);
  temp->val1 = ft_atoi(coord[index][2]);
  temp->val2 = ft_atoi(coord[index + maxline + 1][2]);
  temp->color = give_color(temp->val1, temp->val2);
  if(testa(temp->x1,temp->y1,temp->x2,temp->y2))
    draw_line_on_img(param->img,temp->x1, temp->y1, temp->x2, temp->y2, temp->color);
  free(temp);
}


int new_index(int index, int futurindex)
{
  if(futurindex > 0)
    {
      index += 2;
      futurindex = 0;
    }
  else
    index++;
  return (index);
}

int new_futurindex(int index, int futurindex)
{
  if(futurindex > 0)
    {
      index += 2;
      futurindex = 0;
    }
  else
    index++;
  return (futurindex);
}

void draw_with_tab_on_img(char ***coord, int i, int maxline, t_struct *param)
{
  int index;
  int futurindex;

  futurindex = 0;
  index = 0;
  while(index + 1 < i)
    {
      if(index + 1 < i)
	{
	  if(coord[index + 1][2][0] != '\n')
	    first_part(coord, index, param);
	  else
	    futurindex++;	 
	}
      if(index + maxline + 1 < i)
	{
	  if(coord[index + maxline + 1][2][0] != '\n')
	    second_part(coord, index, maxline, param);
	  else
	    futurindex++;
	}
      index = new_index(index, futurindex);
      futurindex = new_futurindex(index, futurindex);
    }
}  

void    my_pixel_put_to_image(t_img *myimg,int x, int y, int color)
{

  int i;
  unsigned char color1;
  unsigned char color2;
  unsigned char color3;
  myimg->data = mlx_get_data_addr(myimg->img_ptr, &myimg->bpp, &myimg->sizeline, &myimg->endian);

  myimg->data[y * myimg->sizeline + x * myimg->bpp / 8 ] = color % 256;
  color /= 256;
  myimg->data[y * myimg->sizeline + x * myimg->bpp / 8 + 1] = color % 256;
  color /= 256;
  myimg->  data[y * myimg->sizeline + x * myimg->bpp / 8 + 2] = color % 256;
}

t_struct *give(t_struct *mystruct)
{
  mystruct = (t_struct *)malloc(sizeof(t_struct) * 20);
  mystruct->mlx = mlx_init();
  mystruct->win = mlx_new_window(mystruct->mlx, WIDTH, HEIGTH, "42");
  mystruct->zoom = 20;
  return (mystruct);
}

int give_maxline(char **tab)
{
  int maxline;
  int index;

  maxline = 0;
  index = 0;
  while(tab[index][0] != '\n')
    {
      if(tab[index][0] != ' ')
        maxline++;
      index++;
    }
  return (maxline);
}


t_struct *give2(t_struct *mystruct, int i, char **tab, char ***coord)
{
  mystruct->i = i;
  mystruct->maxline = give_maxline(tab);;
  mystruct->coord = coord;
  return (mystruct);
}



t_img *give_img(void *mlx)
{
  t_img *myimg;

  myimg = (t_img *)malloc(sizeof(t_img) * 10);
  myimg->img_ptr = mlx_new_image(mlx, WIDTH, HEIGTH);
  myimg->mlx_ptr = mlx;
  return (myimg);
}

void legend(void *mlx, void *win)
{
  int sizeH;
  int sizeW;

  sizeH = HEIGTH /3;
  sizeW = WIDTH / 3;
  mlx_string_put(mlx, win, sizeH, sizeW, 0x00FFFF, "HOW TO USE ?");
  mlx_string_put(mlx, win, sizeH, sizeW + 40, 0x00FFFF, "Q : ZOOM + | ZOOM - : E");
  mlx_string_put(mlx, win, sizeH, sizeW + 80, 0x00FFFF, "A : MOVE LEFT | MOVE RIGHT : D");
  mlx_string_put(mlx, win, sizeH, sizeW + 120, 0x00FFFF, "W : MOVE UP | MOVE DOWN : S");
  mlx_string_put(mlx, win, sizeH, sizeW + 160, 0x00FFFF, "T : SMALL SCALE");
  mlx_string_put(mlx, win, sizeH, sizeW + 210, 0x00FFFF, "PRESS RETURN FOR START");
}



t_event *give_myevent()
{
  t_event *myevent;

  myevent = (t_event *)malloc(sizeof(t_event) * 4);
  myevent->xd = 300;
  myevent->yd = 60;
  return (myevent);
}

int error(int argc)
{
  if(argc != 2)
    {
      printf("Bug arg");
      return (0);
    }
  return (1);
}

int main(int argc, char **argv)
{ 
  char *line;
  int i;
  t_struct *mystruct;
  char ***coord;
  char **tab;

  i = 0;
  if(error(argc) == 0)
    return (0);
  mystruct = give(mystruct);
  legend(mystruct->mlx, mystruct->win);  
  tab = create_tab(argv[1], tab);
  while(tab[i])
    i++;
  coord = create_coord_tab(tab, coord, i);
  mystruct = give2(mystruct, i, tab, coord);
  mystruct->img = give_img(mystruct->mlx);
  mystruct->event = give_myevent();;
  mlx_key_hook(mystruct->win, event_mlx, mystruct);
  mlx_loop(mystruct->mlx);
  return(0);
}
