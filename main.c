#include "lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

int main()
{
	srand(time(NULL));

	Figure *fig1=start_figure(200,100);
	set_thickness_resolution(fig1,1,0.8);
	Color c;
	c.c1=1;
	c.c2=0;
	c.c3=0;
	set_color(fig1,c);
	draw_fx(fig1, my_func, -100.0, 50.0, 0.02);
	export_eps(fig1, "draw_fx.eps");

	/***************************************/

	Point2D *poly_line = (Point2D *)calloc(50, sizeof(Point2D));

	int k=1;

	for(int i=0 ; i<50 ; i++)
	{
		if(i % 2 == 0) 
		{
			poly_line[i].x = k; poly_line[i].y = k*k/2;
		}
		else poly_line[i].x = -k; poly_line[i].y = -k*k;
		k++;
	}

	Figure *fig2=start_figure(100,100);
	set_thickness_resolution(fig2,0.5,0.8);
	c.c1=0;
	c.c2=1;
	c.c3=0;
	set_color(fig2,c);
	draw_polyline(fig2, poly_line, 50);
	export_eps(fig2, "draw_polyline.eps");

	scale_figure(fig2, 5.0,5.0);
	export_eps(fig2, "scaled_polyline.eps");

	free(poly_line);

	/*****************************************/
	
	Point2D *centre = (Point2D *)malloc(sizeof(Point2D));

	centre->x = 0.0;
	centre->y = 0.0;

	Point2D *width_height = (Point2D *)malloc(sizeof(Point2D));

	width_height->x = 70.0; width_height->y = 50.0 ;

	Figure *fig3=start_figure(300,300);
	set_thickness_resolution(fig3,0.5,0.8);
	c.c1=1;
	c.c2=0;
	c.c3=1;
	set_color(fig3,c);
	draw_ellipse(fig3, centre, width_height);
	export_eps(fig3, "draw_ellipse.eps");

	Point2D *start_roi = (Point2D *)malloc(sizeof(Point2D));
	Point2D *end_roi = (Point2D *)malloc(sizeof(Point2D));

	start_roi->x=-50.0; start_roi->y = -50.0;
	end_roi->x = 50.0 ; end_roi->y=50.0;

	resize_figure(fig3,start_roi,end_roi);

	export_eps(fig3, "resized_ellipse.eps");

	/*********************************************/

	poly_line = (Point2D *)calloc(7, sizeof(Point2D));

	poly_line[0].x = -50.0;  poly_line[0].y =  50*sqrt(3.0); poly_line[5].next = &poly_line[1];
	poly_line[1].x =  50.0;  poly_line[1].y =  50*sqrt(3.0); poly_line[5].next = &poly_line[2];
	poly_line[2].x =  100.0; poly_line[2].y =  0.0;			 poly_line[5].next = &poly_line[3];
	poly_line[3].x =  50.0;  poly_line[3].y = -50*sqrt(3.0); poly_line[5].next = &poly_line[4];
	poly_line[4].x = -50.0;  poly_line[4].y = -50*sqrt(3.0); poly_line[5].next = &poly_line[5];
	poly_line[5].x = -100.0; poly_line[5].y =  0.0;			 poly_line[5].next = &poly_line[6];
	poly_line[6].next = NULL;
	
	Figure *fig4=start_figure(300,300);
	set_thickness_resolution(fig4,0.5,0.8);
	c.c1=1;
	c.c2=0;
	c.c3=1;
	set_color(fig4,c);
	draw_polygon(fig4, poly_line);
	export_eps(fig4, "draw_polygon.eps");

	append_figures(fig4,fig3);
	export_eps(fig4, "append_figures.eps"); //appended figures

	/*****************************************/
	
	Figure *fig5=start_figure(300,300);
	set_thickness_resolution(fig5,0.5,0.8);
	c.c1=1;
	c.c2=0;
	c.c3=1;
	set_color(fig5,c);

	Tree *root = (Tree *)malloc(sizeof(Tree));

	draw_binary_tree(fig5,root);

	export_eps(fig5, "draw_binary_tree.eps");
	/***********************************************/


	return 0;
}
