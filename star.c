#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "star.h"

int star_read_from_file(struct star* s, FILE* f)
{
    // TODO implement	
	abort();
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
	// TODO implement
	abort();
}
