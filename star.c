#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "star.h"

int star_read_from_file(struct star* s, FILE* f)
{
    double xcord, ycord, zcord, mag;
    int drapnr, hrn;
    int reads=fscanf(f, "%lf %lf %lf %i %lf %i",&xcord,&ycord,&zcord,&drapnr,&mag,&hrn);
	if (6==reads){
        // ggf. abfangen wenn coordinaten >1
        s->x = xcord;
        s->y = ycord;
        s->magnitude = mag;
        s->draper=drapnr;
        return 1;
    }
    else 
        return 0;
    }
    
void star_coord_to_pixel(struct star const* s, struct image* const img, int* x, int* y)
{
	double a = s->x;
    double b = s->y;
    int height = img->h;
    int width = img->w;
    double mheight=(((double)height)-1)/2.0;
    double mwidth=(((double)width)-1)/2.0;
    *x =(int)((1.0+a)*mwidth);
    *y = (int)((1.0-b)*mheight);
}

void star_plot(struct star const* s, struct image* img)
{
    int y=0;
    int x=0;
    star_coord_to_pixel(s,img,&x,&y);
    int wide=(img->w);                  
    int hight=(img->h);
    if (y<=hight)
        if (x<=wide)
            {int num=wide*y+x;
            (img->data[num])=0xffffff;}
}
