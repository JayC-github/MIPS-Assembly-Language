#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    // fopen returns a file pointer used to access file
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        // couldn't open the file, print an error message
        // to standard error
        fprintf(stderr, "%s: ", argv[0]);
        perror(argv[1]);
        return 1;
    }

    char string[3];
	int c;
	int count = 0;
	int newL = 0;
	int j = 1;
	while ((c = fgetc(fp)) != EOF) {
		if (isprint(c) != 0 && count < 3) {
			string[count] = c;
			count++;
		} else if (isprint(c) != 0) {
		    if (j == 1) {
		        int k = 0;
		        while (k < 3) {
		            printf("%c", string[k]);
		            k++;
		        }
		        j = 0;  
		    }
		    printf("%c", c);
		    newL = 1;
		
		} else {
		    if (newL == 1) {
		        printf("\n");
		        newL = 0;
		    } 
		    
		    count = 0;
		    j = 1;
		 
		}
		count++;
	}
	
	
	if (newL == 1) {
	    printf("\n");
	}
    // close the file, as the program is about to exit
    // this isn't necessary but is good practice
    fclose(fp);
    return 0;
}
