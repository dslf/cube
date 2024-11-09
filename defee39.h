#ifndef DEFEE39_H
#define DEFEE39_H

#define P_NAME "skrambilka" 
#define S_PNAME "scrambles.txt"
#define C_DATE __DATE__
#define C_TIME __TIME__
#define P_VER "v0.09"

#define L 0
#define R 1
#define F 2
#define B 3
#define U 4
#define D 5

void show_help(int argc, char *argv[]);
void parse_argc(int argc, char *argv[]);
void reset_color();
void rotate_cube(const char *str);
void init_cube();
void draw_cube();
void draw_color_cube();
void set_color(int n);
void rotate_side(int n);
void read_line(const char *filename_to_open, int n);

#endif