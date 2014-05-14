#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "star.h"
#include "image.h"

int main(int argc, char **argv)
{
	if (argc < 3) {
		fprintf(stderr, "syntax: %s size starlist [lines...]\n", argv[0]);
		return 1;
	}

	int size = atoi(argv[1]);
	if (size <= 0) {
		fprintf(stderr, "size of image cannot be <= 0\n");
		return 1;
	}

	struct image img;
	image_init(&img, size, size);

	/* TODO: Read in the stars from the file with name argv[2] and draw them to the image. */
	abort();

	/* Open every constellation file. */
	for (int i = 3; i < argc; i++) {
		FILE* f = fopen(argv[i], "r");
		/* if the file could not be opened, skip to the next one. */
		if (f == NULL) {
			fprintf(stderr, "cannot open line file \"%s\"\n", argv[i]);
			continue;
		}

		/* TODO: draw the constellation */
		abort();

		fclose(f);
	}


	/* write the painted image to the output file. */
	FILE* image_file = fopen("stars.pbm", "w");
	if (image_file == NULL) {
		fprintf(stderr, "cannot open output file.\n");
		return 1;
	}
	image_write_to_file(&img, image_file);
	fclose(image_file);
	return 0;
}
