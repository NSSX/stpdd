#ifndef STRUCT_H
# define STRUCT_H


typedef struct          s_img
{
  void *mlx;
  void *win;
  unsigned long img_color;
  char *data;
  void *img_ptr;
  int sizeline;
  int bpp;
  int x;
  int y;
  int endian;
  void *mlx_ptr;
}                                       t_img;

typedef struct          s_event
{
  float xd;
  float yd;
}                                       t_event;

typedef struct          s_struct
{
  void *mlx;
  void *win;
  char ***coord;
  int i;
  int maxline;
  int zoom;
  t_img *img;
  t_event *event;  
  struct s_struct   *next;
  struct s_struct   *before;
}                                       t_struct;

typedef struct          s_temp
{
  int x1;
  int x2;
  int y1;
  int y2;
  int val1;
  int val2;
  int color;
}                                       t_temp;

typedef struct          s_coor
{
int index;
float xdep;
float ydep;
float xtemp;
float ytemp;
float j;
float v;
  float x;
  float y;
}                                       t_coor;

void draw_line_on_img(t_img *myimg,float xi, float yi, float xf, float yf, int color);
void place_img(t_struct *param, float xd, float yd);
void img_move(int keycode, t_struct *param);
void img_zoom(int keycode, t_struct *param);
void img_other_view(int keycode, t_struct *param);
void img_other(int keycode, t_struct *param);
int event_mlx(int keycode, t_struct *param);
char **create_tab(char *argv, char **tab);
char ***create_coord_tab(char **tab, char ***coord, int i);
t_coor *give_coor(t_coor *coor, t_struct *param);
t_coor *start_coor(t_coor *coor, int x, int y);
t_coor *else_coor(t_coor *coor, t_struct *param, int index);
char ***set_coordq(t_struct *param, float x, float y, int index);
int testa(int x1,int y1,int x2,int y2);
int color2(int val1, int val2, int color);
int give_color(int val1, int val2);
void first_part(char ***coord, int index, t_struct *param);
void second_part(char ***coord, int index, int maxline, t_struct *param);
int new_index(int index, int futurindex);
int new_futurindex(int index, int futurindex);
void draw_with_tab_on_img(char ***coord, int i, int maxline, t_struct *param);
void    my_pixel_put_to_image(t_img *myimg,int x, int y, int color);
t_struct *give(t_struct *mystruct);
int give_maxline(char **tab);
t_struct *give2(t_struct *mystruct, int i, char **tab, char ***coord);
t_img *give_img(void *mlx);
void legend(void *mlx, void *win);
int couleur(double t);
t_coor *give_coorx(t_coor *coor, t_struct *param);
t_coor *start_coorx(t_coor *coor, int x, int y);
t_coor *else_coorx(t_coor *coor, t_struct *param, int index);
char ***set_coordx(t_struct *param, float x, float y, int index);
char ***set_coordp(t_struct *param, float x, float y, int index);
t_coor *else_coorp(t_coor *coor, t_struct *param, int index);
t_coor *start_coorp(t_coor *coor, int x, int y);
t_coor *give_coorp(t_coor *coor, t_struct *param);

#endif
