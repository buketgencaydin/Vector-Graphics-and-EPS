#include "lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

Figure * start_figure(double width, double height)
{
    Figure *fig = (Figure *)malloc(sizeof(Figure));

    fig->trx =  width/2.0;  fig->try =  height/2.0;
    fig->blx = -width/2.0;  fig->bly = -height/2.0;

    return fig;
}
void set_thickness_resolution(Figure * fig, double thickness, double resolution)
{
    fig->th = thickness;
    fig->res = resolution;
}
void set_color(Figure * fig, Color c)
{
    fig->color.c1 = c.c1;
    fig->color.c2 = c.c2;
    fig->color.c3 = c.c3;
}
void draw_fx(Figure * fig, double f(double x), double start_x, double end_x, double step_size)
{
    double i;
    Point2D *pp; //previous pointer
    Point2D *cp; //current pointer

    cp = (Point2D*)malloc(sizeof(Point2D));
    cp->x = start_x; cp->y = f(start_x);
    fig->point = cp;
    pp=cp;

    for(i=start_x+step_size ; i<end_x ; i+=step_size)
    {
        cp = (Point2D*)malloc(sizeof(Point2D));
        cp->x = i; cp->y = f(i);
        pp->next = cp;
        pp = cp;
    }
    pp->next = NULL;
}
void draw_polyline(Figure * fig, Point2D * poly_line, int n)
{
    int i=0;

    Point2D *pp; //previous pointer
    Point2D *cp; //current pointer

    cp = (Point2D*)malloc(sizeof(Point2D));
    cp->x = poly_line[i].x;
    cp->y = poly_line[i].y;
    fig->point = cp;
    pp=cp;

    for(i=1 ; i<n ; i++)
    {
        cp = (Point2D*)malloc(sizeof(Point2D));
        cp->x = poly_line[i].x;
        cp->y = poly_line[i].y;
        pp->next = cp;
        pp=cp;
    }
    pp->next = NULL;
}
void export_eps(Figure * fig, char * file_name)
{
    Point2D *ptr;
    Text *tptr;
    FILE *fp = fopen(file_name, "w");
    
    fprintf(fp, "%%!PS-Adobe-3.0 EPSF-3.0\n");
    fprintf(fp, "%%%%BoundingBox: %d %d %d %d\n",fig->blx, fig->bly, fig->trx, fig->try);
    fprintf(fp, "%%%%Creator: Buket Gencaydin\n") ;
    fprintf(fp, "%%%%Title: CSE102 Term Project PART-1\n");
    fprintf(fp, "%.1f setlinewidth\n",fig->th);
    fprintf(fp, "%d %d %d setrgbcolor\n",fig->color.c1, fig->color.c2, fig->color.c3);
    

    if(strcmp(file_name,"draw_binary_tree.eps")==0)
    {
        fprintf(fp,"/Times-Roman findfont\n"); 
        fprintf(fp,"10 scalefont\n");
        fprintf(fp,"setfont\n");
        
        tptr = fig->root->text;
        while(tptr != NULL)
        {
            fprintf(fp,"%f %f moveto\n", tptr->x-6, tptr->y-2);
            fprintf(fp,"(%d) show\n",tptr->number);
            tptr = tptr->next; 
        }
    }
    ptr = fig->point;
    
    fprintf(fp, "%f %f moveto\n",ptr->x, ptr->y);
    
    ptr = ptr->next;

    while(ptr != NULL)
    {
        if(ptr->flag==1)
        {
            fprintf(fp, "%f %f moveto\n", ptr->x, ptr->y);
        }
        else if(ptr->flag==2)
        {
            fprintf(fp, "closepath\n" );
        }
        else
        {
            fprintf(fp, "%f %f lineto\n",ptr->x, ptr->y);
        }
        ptr = ptr->next;
    }
    fprintf(fp, "stroke\n");
}
void draw_polygon(Figure * fig, Point2D * poly_line)
{
    int i=0;
    Point2D *pp; //previous pointer
    Point2D *cp; //current pointer

    cp = (Point2D*)malloc(sizeof(Point2D));
    cp->x = poly_line[i].x;
    cp->y = poly_line[i].y;
    fig->point = cp;
    pp=cp;

    for(i=1 ; i<7; i++)
    {
        cp = (Point2D*)malloc(sizeof(Point2D));
        cp->x = poly_line[i].x;
        cp->y = poly_line[i].y;
        pp->next = cp;
        pp=cp;
    }
    pp->next = NULL;
    pp->flag=2;
}
void draw_ellipse(Figure * fig, Point2D * centre, Point2D * width_height)
{
    /*
        ELLIPSE EQUATION = (x-h)^2 / a^2 + (y-k)^2 / b^2 
        centre coordinates = (h,k)
        width = a, height = b
    */

    double h = centre->x, k = centre->y, a = width_height->x/2.0, b = width_height->y/2.0;
    double step_size=0.002;

    Figure *fig2 = (Figure *)malloc(sizeof(Figure));

    Point2D *pp; //previous pointer
    Point2D *cp; //current pointer
    
    cp = (Point2D*)malloc(sizeof(Point2D));
    cp->x = h-a;
    cp->y = k;
    fig->point = cp;
    pp=cp;

    for(double i=step_size ; i<2*a ; i+=step_size)
    {
        cp = (Point2D*)malloc(sizeof(Point2D));
        cp->x = h-a + i;
        cp->y = sqrt(b*b * (1 - ((cp->x - h)*(cp->x - h) / (a*a)))) + k;
        pp->next = cp;
        pp = cp;
    }
    cp = (Point2D*)malloc(sizeof(Point2D));
    cp->x = h+a;
    cp->y = k;
    pp->next=cp;
    pp=cp;

    for(double i=0 ; i< 2*a ; i+=step_size)
    {
        cp = (Point2D*)malloc(sizeof(Point2D));
        if(i==0) cp->flag=1;
        cp->x = h-a + i;
        cp->y = -sqrt(b*b * (1 - ((cp->x - h)*(cp->x - h) / (a*a)))) + k;
        pp->next = cp;
        pp = cp;
    }
    cp = (Point2D*)malloc(sizeof(Point2D));
    cp->x = h+a;
    cp->y = k;
    pp->next=cp;
    pp=cp;

    pp->next=NULL;
}
double my_func(double x)
{
    return 25*(sin(x/3))+7;
}
void append_figures(Figure * fig1, Figure * fig2)
{
    Point2D *cp = fig1->point;

    while(cp->next != NULL)
    {
        cp = cp->next;
    }
    cp->next=fig2->point;
    cp->next->flag=1;
}
void scale_figure(Figure * fig, double scale_x, double scale_y)
{
    Point2D *cp = fig->point;

    fig->trx *= scale_x; fig->try *= scale_y;
    fig->blx *= scale_x; fig->bly *= scale_y;
    
    while(cp != NULL)
    {
        cp->x *= scale_x;
        cp->y *= scale_y;
        cp = cp->next;
    }
}
void resize_figure(Figure * fig, Point2D *start_roi, Point2D *end_roi)
{
    fig->blx = start_roi->x; fig->bly = start_roi->y;
    fig->trx = end_roi->x;   fig->try = end_roi->y;
}
void draw_binary_tree(Figure *fig, Tree *root)
{
    Figure *fig2=start_figure(300,300);
    Text *pp=(Text *)malloc(sizeof(Text));
    Point2D *last = (Point2D *)malloc(sizeof(Point2D));

    Point2D *centre = (Point2D *)malloc(sizeof(Point2D));
    centre->x=5.0; centre->y=6.0;
    double radius=20;

    fig->root = create_node(fig, centre, 1,pp); 
    draw_circle(fig, centre, radius);
    pp=fig->root->text;
    
    last = find_last(fig);
    last->next = (Point2D *)malloc(sizeof(Point2D));
    last->next->flag=1;
    last->next->x = centre->x-10;
    last->next->y =  -sqrt((radius*radius - ((centre->x-10 - centre->x)*(centre->x-10 - centre->x) ))) + centre->y;
    last->next->next=NULL;

    centre->x = 5.0 -20*3; centre->y = 6.0 - 3*20; //left

    last = find_last(fig);
    last->next = (Point2D *)malloc(sizeof(Point2D));
    last->next->x = centre->x;
    last->next->y = centre->y + radius;
    last->next->next=NULL;

    fig->root->left_node = create_node(fig, centre, 2, pp);
    draw_circle(fig2, centre, 20.0);
    append_figures(fig,fig2);
    pp=fig->root->text->next;
/************************************************************/
    centre->x=5.0; centre->y=6.0; //root

    last = find_last(fig);
    last->next = (Point2D *)malloc(sizeof(Point2D));
    last->next->flag=1;
    last->next->x = centre->x+10;
    last->next->y =  -sqrt((radius*radius - ((centre->x+10 - centre->x)*(centre->x+10 - centre->x) ))) + centre->y;
    last->next->next=NULL;

    centre->x = 5.0 +20*3; centre->y = 6.0 - 3*20; //right

    last = find_last(fig);
    last->next = (Point2D *)malloc(sizeof(Point2D));
    last->next->x = centre->x;
    last->next->y = centre->y + radius;
    last->next->next=NULL;

    fig->root->right_node = create_node(fig, centre, 3, pp);
    draw_circle(fig2, centre, 20.0);
    append_figures(fig,fig2);
    pp=fig->root->text->next->next;
/************************************************************/

    centre->x = 5.0 -20*3; centre->y = 6.0 - 3*20; //left

    last = find_last(fig);
    last->next = (Point2D *)malloc(sizeof(Point2D));
    last->next->flag=1;
    last->next->x = centre->x-10;
    last->next->y =  -sqrt((radius*radius - ((centre->x-10 - centre->x)*(centre->x-10 - centre->x) ))) + centre->y;
    last->next->next=NULL;


    centre->x = 5.0 -20*5; centre->y = 6.0 - 6*20; //left-left

    last = find_last(fig);
    last->next = (Point2D *)malloc(sizeof(Point2D));
    last->next->x = centre->x;
    last->next->y = centre->y + radius;
    last->next->next=NULL;

    fig->root->left_node->left_node = create_node(fig, centre, 4, pp);
    draw_circle(fig2, centre, 20.0);
    append_figures(fig,fig2);
    pp=fig->root->text->next->next->next;
/****************************************************************************/
    centre->x = 5.0 -20*3; centre->y = 6.0 - 3*20; //left

    last = find_last(fig);
    last->next = (Point2D *)malloc(sizeof(Point2D));
    last->next->flag=1;
    last->next->x = centre->x+10;
    last->next->y =  -sqrt((radius*radius - ((centre->x-10 - centre->x)*(centre->x-10 - centre->x) ))) + centre->y;
    last->next->next=NULL;

    centre->x = 5.0 -20; centre->y = 6.0 - 6*20; //left-right

    last = find_last(fig);
    last->next = (Point2D *)malloc(sizeof(Point2D));
    last->next->x = centre->x;
    last->next->y = centre->y + radius;
    last->next->next=NULL;

    fig->root->left_node->right_node = create_node(fig, centre, 5, pp);
    draw_circle(fig2, centre, 20.0);
    append_figures(fig,fig2);
    pp=fig->root->text->next->next->next->next;

/**********************************************************************/

    centre->x = 5.0 +20*3; centre->y = 6.0 - 3*20; //right

    last = find_last(fig);
    last->next = (Point2D *)malloc(sizeof(Point2D));
    last->next->flag=1;
    last->next->x = centre->x+10;
    last->next->y =  -sqrt((radius*radius - ((centre->x-10 - centre->x)*(centre->x-10 - centre->x) ))) + centre->y;
    last->next->next=NULL;

    centre->x = 5.0 +20*5; centre->y = 6.0 - 6*20;

    last = find_last(fig);
    last->next = (Point2D *)malloc(sizeof(Point2D));
    last->next->x = centre->x;
    last->next->y = centre->y + radius;
    last->next->next=NULL;

    fig->root->right_node->right_node = create_node(fig, centre, 6, pp);
    draw_circle(fig2, centre, 20.0);
    append_figures(fig,fig2);
    pp=fig->root->text->next->next->next->next->next;
}
Tree * create_node(Figure *fig, Point2D *centre, int node_num, Text *pp)
{
    Tree *node = (Tree *)malloc(sizeof(Tree));
    
    node->text = (Text *)malloc(sizeof(Text));
    node->text->number = rand() % 1000;
    node->text->x = centre->x;
    node->text->y = centre->y;

    if(node_num == 1) pp=node->text;
    else
    {
        pp->next=node->text;
        pp=node->text;
        pp->next=NULL;
    }
    return node;
}
void draw_circle(Figure *fig, Point2D *centre, double r)
{
    /*
        CIRCLE EQUATION =  (x-h)^2 + (y-k)^2 =  r^2
        centre coordinates = (h,k)
        r = radius
    */
    double h = centre->x, k = centre->y;
    double step_size=0.002;

    Point2D *pp; //previous pointer
    Point2D *cp; //current pointer
    
    cp = (Point2D*)malloc(sizeof(Point2D));
    cp->x = h-r;
    cp->y = k;
    fig->point = cp;
    pp=cp;

    for(double i=step_size ; i< 2*r ; i += step_size)
    {
        cp = (Point2D*)malloc(sizeof(Point2D));
        cp->x = h-r + i;
        cp->y = sqrt((r*r - ((cp->x - h)*(cp->x - h) ))) + k;
        pp->next = cp;
        pp = cp;
    }

    cp = (Point2D*)malloc(sizeof(Point2D));
    cp->x = h+r;
    cp->y = k;
    pp->next = cp;
    pp=cp;

    for(double i=0  ; i< 2*r ; i+=step_size)
    {
        cp = (Point2D*)malloc(sizeof(Point2D));
        if(i==0) cp->flag=1;
        cp->x = h-r + i;
        cp->y = -sqrt((r*r - ((cp->x - h)*(cp->x - h) ))) + k;
        pp->next = cp;
        pp = cp;
    }
    cp = (Point2D*)malloc(sizeof(Point2D));
    cp->x = h+r;
    cp->y = k;
    pp->next = cp;
    pp=cp;
    pp->next=NULL;

}

Point2D * find_last(Figure *fig)
{
    Point2D *ptr;

    ptr = fig->point;
    while(ptr->next != NULL)
    {
        ptr = ptr->next;
    }
    return ptr;
}