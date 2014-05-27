#include <stdlib.h>
#include <string.h>

#include "image.h"

void image_init(struct image* img, int w, int h)
{
	img->w = w;
	img->h = h;
	img->data = malloc(w * h * sizeof(*img->data));
	memset(img->data, 0, w * h * sizeof(*img->data));
}

void image_draw_pixel(struct image* img, int color, int x, int y)
{
    int wide = (img->w);
    int hight = (img->h);
    if (x<=wide) {        
        if (y<=hight){
            int num = wide*y+x;
            (img->data[num])=color;
        }
    }
}

/*
 * Draw a line using Bresenham's algorithm.
 * @see http://en.wikipedia.org/wiki/Bresenham's_line_algorithm
 */
void image_draw_line(struct image* img, int color, int x0, int y0, int x1, int y1)
{
	int dx    = x1 > x0 ? x1 - x0 : x0 - x1;
	int dy    = y1 > y0 ? y1 - y0 : y0 - y1;
	int sx    = x1 > x0 ? 1 : -1;
	int sy    = y1 > y0 ? 1 : -1;
	int not_steep = dy > dx;

	if (not_steep) {
		int tmp;
#define SWAP(a,b) tmp = a; a = b; b = tmp;
		SWAP(x0, y0);
		SWAP(dx, dy);
		SWAP(sx, sy);
#undef SWAP
	}

	int e = 2 * dy - dx;
	for (int i = 0; i < dx; i++) {
		if (not_steep)
			image_draw_pixel(img, color, y0, x0);
		else
			image_draw_pixel(img, color, x0, y0);

		if (e >= 0) {
			int d = 1 + e / (2 * dx);
			y0 += sy < 0 ? -d : d;
			e  -= d * 2 * dx;
		}

		x0 += sx;
		e  += 2 * dy;
	}
}

void image_write_to_file(struct image* img, FILE* f)
{
    int wide = (img->w);
    int hight= (img->h);
    int cw=0;
    int hw=0;
    
    fprintf(f,"P3\n%i %i\n255\n", wide, hight);
    while (hw<hight){
        while (cw<wide){
            int rot=((img->data[hw*wide+cw])>>16);   
            unsigned int help= (img->data[hw*wide+cw]<<16);
            int grün = help >> 24;
            help = (img->data[hw*wide+cw]<<24);
            int blau = help >> 24;
            fprintf (f,"%i %i %i ", rot,grün,blau);
            cw++;
        }
        fprintf (f, "\n");
        hw++;
        cw = 0;
    }
}
