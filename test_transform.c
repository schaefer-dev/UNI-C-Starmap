#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "star.h"

#define FALSE   0
#define TRUE    1
#define BOOL    int

void pass(char* test_name) {
	printf("PASS: '%s'\n", test_name);
}

void fail(char* test_name, char* message) {
	fprintf(stderr, "fail: '%s' with message '%s'\n", test_name, message);
}

int main(int argc, char **argv)
{
	BOOL failed = FALSE;
	struct star validstar;
	int x;
	int y;
	struct image img;

	image_init(&img, 501, 501);
	validstar.x = 1.0;
	validstar.y = 1.0;
	star_coord_to_pixel(&validstar, &img, &x, &y);
	if (x != 500 || y != 0)
		failed = TRUE;

	validstar.x = -0.78;
	validstar.y = 0.34;
	star_coord_to_pixel(&validstar, &img, &x, &y);
	if (x < 54 || x > 56 || y < 164 || y > 166)
		failed = TRUE;

	validstar.x = -1.0;
	validstar.y = -1.0;
	star_coord_to_pixel(&validstar, &img, &x, &y);
	if (x != 0 || y != 500)
		failed = TRUE;

	validstar.x = 0.0;
	validstar.y = 0.0;
	star_coord_to_pixel(&validstar, &img, &x, &y);
	if (x != 250 || y != 250)
		failed = TRUE;

	if (failed) {
		fail("test_transform", "at least one coordinate wrong transformed");
		return 1;
	} else {
		pass("test_transform");
		return 0;
	}
}
