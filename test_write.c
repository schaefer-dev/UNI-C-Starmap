#include <string.h>
#include <stdio.h>

#include "image.h"

static int check_image(struct image* img)
{
	FILE* f = fopen("test.pbm", "w");
	image_write_to_file(img, f);
	fclose(f);

	f = fopen("test.pbm", "r");
	if (!f) {
		fprintf(stderr, "image file 'test.pbm' missing\n");
		return 1;
	}

	/* look if first line contains P3 */
	char buf[16];
	fgets(buf, sizeof(buf), f);
	if (strcmp(buf, "P3\n") != 0) {
		fprintf(stderr, "expected P3 but found: %s\n", buf);
		goto fail;
	}

	/* check, if the dimensions match */
	int w, h;
	fscanf(f, "%d %d\n", &w, &h);
	if (w != img->w || h != img->h) {
		fprintf(stderr, "wdith and height differ (%d, %d) != (%d, %d)\n", w, h, img->w, img->h);
		goto fail;
	}

	/* read the maximum rgb component value */
	int max_col;
	if (fscanf(f, "%d\n", &max_col) != 1)
		goto fail;

	/* look at all pixels, if they match with written image */
	int pixels = 0;
	for (;;) {
		int r, g, b;
		if (fscanf(f, "%d %d %d", &r, &g, &b) != 3)
			break;

		if (r < 0 || max_col < r) {
			fprintf(stderr, "red in pixel %d is larger than maximum color specified: %d > %d\n", pixels, r, max_col);
			goto fail;
		}
		if (g < 0 || max_col < g) {
			fprintf(stderr, "green in pixel %d is larger than maximum color specified: %d > %d\n", pixels, g, max_col);
			goto fail;
		}
		if (b < 0 || max_col < b) {
			fprintf(stderr, "blue in pixel %d is larger than maximum color specified: %d > %d\n", pixels, b, max_col);
			goto fail;
		}

		int c = r << 16 | g << 8 | b;
		if (c != img->data[pixels]) {
			fprintf(stderr, "pixel %d color does not match original color: %x != %x\n", pixels, c, img->data[pixels]);
			goto fail;
		}
		pixels++;
	}

	/* check if we read precisely the necessary amount of pixels */
	if (pixels != w * h) {
		fprintf(stderr, "file contained wrong number (%d) of pixels. required: %d\n", pixels, w * h);
		goto fail;
	}

	fclose(f);
	return 0;

fail:
	fclose(f);
	return 1;
}

int main(int argc, char **argv)
{
	struct image img;

	image_init(&img, 10, 10);
	image_draw_pixel(&img, 0x123456, 2, 5);
	image_draw_pixel(&img, 0xffeedd, 4, 9);
	image_draw_pixel(&img, 0xaa55aa, 0, 0);

	return check_image(&img);
}
