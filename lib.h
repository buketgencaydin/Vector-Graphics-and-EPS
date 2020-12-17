#ifndef lib_h
#define lib_h

typedef struct
{
    int c1, c2, c3;
    /*
        1   0   0 setrgbcolor -->   red
        0   1   0 setrgbcolor -->   green
        0   0   1 setrgbcolor -->   dark blue
        0   1   1 setrgbcolor -->   light blue
        1   0   1 setrgbcolor -->   magenta
        1   1   0 setrgbcolor -->   yellow
        1   1   1 setrgbcolor -->   white
        0   0   0 setrgbcolor -->   black
    */
}Color;
typedef struct Point2D
{
    double x, y;
    struct Point2D *next;
    int flag;
}Point2D;
typedef struct Text
{
    int number;
    double x, y;
    struct Text *next;

}Text;
typedef struct Tree
{
    Text *text;
    double x, y;
    struct Tree *left_node;
    struct Tree *right_node;
}Tree;

typedef struct
{
    int trx, try; // top-right corner
    int blx, bly; // bottom-left corner
    double th, res; // thickness, resolution
    Color color;
    Point2D *point; 
    Tree *root;
}Figure;

Figure * start_figure(double width, double height);
void set_thickness_resolution(Figure * fig, double thickness, double resolution);
void set_color(Figure * fig, Color c);
void draw_fx(Figure * fig, double f(double x), double start_x, double end_x, double step_size);
void draw_polyline(Figure * fig, Point2D * poly_line, int n);
void draw_polygon(Figure * fig, Point2D * poly_line);
void draw_ellipse(Figure * fig, Point2D * centre, Point2D * width_height);
void draw_circle(Figure *fig, Point2D *centre, double r);
void draw_binary_tree(Figure * fig, Tree * root);
void scale_figure(Figure * fig, double scale_x, double scale_y);
void resize_figure(Figure * fig, Point2D *start_roi, Point2D *end_roi);
void append_figures(Figure * fig1, Figure * fig2);
void export_eps(Figure * fig, char * file_name);
double my_func(double x);
Tree * create_node(Figure *fig, Point2D *centre, int node_num, Text *pp);
Point2D * find_last(Figure *fig);

#endif 