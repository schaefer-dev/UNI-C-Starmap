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
    
    struct star s;
    int x,y;
    FILE* starsT = fopen(argv[2],"r");
    while (star_read_from_file(&s,starsT)==1){
        star_coord_to_pixel(&s,&img,&x,&y);
        image_draw_pixel(&img,0xffffff, x, y);
    }
    fclose(starsT);
    // Finish

	/* Open every constellation file. */
	for (int i = 3; i < argc; i++) {
		FILE* f = fopen(argv[i], "r");
		/* if the file could not be opened, skip to the next one. */
		if (f == NULL) {
			fprintf(stderr, "cannot open line file \"%s\"\n", argv[i]);
			continue;
		}

		/* TODO: draw the constellation */

        int drap1=0;
        int drap2=0;
        while (2==(fscanf(f,"%i,%i", &drap1, &drap2))) {
            int drap1found=0;
            int drap1x=0;
            int drap1y=0;
            int drap2found=0;
            int drap2x=0;
            int drap2y=0;
           FILE* starL = fopen(argv[2],"r"); 
           //while (6==fscanf(s, "%lf %lf %lf %i %lf %i",&xcord,&ycord,&zcord,&drapnr,&mag,&hrn))
           struct star st;
           while (star_read_from_file(&st,starL)==1){
               if (drap1==(st.draper)){drap1found=1;star_coord_to_pixel(&st,&img,&drap1x,&drap1y);}; 
               if (drap2==(st.draper)){drap2found=1;star_coord_to_pixel(&st,&img,&drap2x,&drap2y);};
           }
           fclose(starL);
           if (drap1found==0)
               printf("Warnung: Drapernummer %i wurde nicht gefunden und konnte daher nicht in das Sternenbild eingetragen werden\n", drap1);
           if (drap2found==0)
               printf("Warnung: Drapernummer %i wurde nicht gefunden und konnte dahern icht in das Sternenbild eingetragen werden\n",drap2);

           if ((drap1found==1)|(drap2found==1)){
               image_draw_line(&img,0x00ff00,drap1x,drap1y,drap2x,drap2y);
           }
        }
        //Finish
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
