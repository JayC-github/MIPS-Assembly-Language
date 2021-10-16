#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
	if (argc != 2) {
		fprintf(stderr,  "Usage: %s <filename>\n", argv[0]);
		return 1;
	}
	
    // fopen returns a file pointer used to access file
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        // couldn't open the file, print an error message
        // to standard error
        fprintf(stderr, "%s: ", argv[0]);
        perror(argv[1]);
        return 1;
    }
    
    int c;
	long count = 0;
	while ((c = fgetc(fp)) != EOF) {
		if (isprint(c) == 0) {
			printf("byte %4ld: %3d 0x%02x \n", count, c, c);
		} else {
		    printf("byte %4ld: %3d 0x%02x '%c'\n", count, c, c, c);
		}
		count++;
	}
    
    // close the file, as the program is about to exit
    // this isn't necessary but is good practice
    fclose(fp);
    return 0;
}

/*


	
*/
