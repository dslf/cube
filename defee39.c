#include "defee39.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char cube[6][9];
char b[6][9];
char c[100];
char line[100];
int i, j, k, l, n;

void parse_argc(int argc, char *argv[]) {
	char *t_filename;
	int t_line_number;
	int found_filename = 0;
	int found_linenumber = 0;

	if (argc < 2) {
		show_help(argc, argv);
		exit(0);
	}
	for (i = 0; i < argc; i++) {
		if (strcmp(argv[i], "-f") == 0) {
			if (argv[i + 1] == NULL) {
				printf("%s is empty", argv[i]);
				break;
			}
			found_filename = 1;
			t_filename = argv[i + 1];

			printf("Found file, reading %s\n", argv[i + 1]);
		}
		if (strcmp(argv[i], "-n") == 0) {
			if (argv[i + 1] == NULL) {
				printf("%s is empty", argv[i]);
				break;
			}
			found_linenumber = 1;
			t_line_number = atoi(argv[i + 1]);
		/* 	printf("Line to read %s\n", argv[i + 1]); */
		}

		if (strcmp(argv[i], "-s") == 0) {
			if (argv[i + 1] == NULL) {
				printf("%s is empty\n", argv[i]);
				break;
			}
			if (argv[i + 1] != NULL) { 
			init_cube(); 
			rotate_cube(argv[i+1]);
			draw_cube();
			printf("Scramble %s\n", argv[i+1]);
			}
		}
	}
	if (found_filename && found_linenumber) {
		printf("Found file name and file\n");
		read_line(t_filename, t_line_number);
	}

	if (!found_filename && found_linenumber){
		/* no file name, but have line number, so check for defaul file exist */
		FILE *file = fopen(DEF_SCR_FILENAME, "r");
		if (file) {				
			fclose(file);
			read_line(DEF_SCR_FILENAME, t_line_number);
		} else {
			printf("default scrables (%s) not found, please specify with -f FILENAME\n", DEF_SCR_FILENAME);

		}
	}
}

void show_help(int argc, char *argv[]) {	
	draw_cube();
	printf("\nUsage: %s -f FILE -n LINE_NUMBER -s SCRAMBLE\n"
		"Example: %s \"U L' B R2 U2 F U2\"\n", P_NAME, P_NAME);
	
}

void rotate_cube(const char *str) {
	while (*str != '\0') { /* Go through every char in str, until null-terminator */
		switch (*str) {
			case 'D':
				if (*(str + 1) == 39) { /* D' */
					rotate_side(D);
					rotate_side(D);
					rotate_side(D);
					break;
				}
				if (*(str + 1) == '2') { /* D2 */
					rotate_side(D);
					rotate_side(D);
					break;
				}
				rotate_side(D);
				break;

			case 'F':
				if (*(str + 1) == 39) { /* F' */
					rotate_side(F);
					rotate_side(F);
					rotate_side(F);
					break;
				}
				if (*(str + 1) == '2') { /* F2 */
					rotate_side(F);
					rotate_side(F);
					break;
				}
				rotate_side(F);
				break;

			case 'B':
				if (*(str + 1) == 39) { /* B' */
					rotate_side(B);
					rotate_side(B);
					rotate_side(B);
					break;
				}
				if (*(str + 1) == '2') { /* B2 */
					rotate_side(B);
					rotate_side(B);
					break;
				}
				rotate_side(B);
				break;

			case 'U':
				if (*(str + 1) == 39) { /* U' */
					rotate_side(U);
					rotate_side(U);
					rotate_side(U);
					break;
				}
				if (*(str + 1) == '2') { /* U2 */
					rotate_side(U);
					rotate_side(U);
					break;
				}
				rotate_side(U);
				break;

			case 'L':
				if (*(str + 1) == 39) { /* L' */
					rotate_side(L);
					rotate_side(L);
					rotate_side(L);
					break;
				}
				if (*(str + 1) == '2') { /* L2 */
					rotate_side(L);
					rotate_side(L);
					break;
				}
				rotate_side(L);
				break;

			case 'R':
				if (*(str + 1) == 39) { /* R' */
					rotate_side(R);
					rotate_side(R);
					rotate_side(R);
					break;
				}
				if (*(str + 1) == '2') { /* R2 */
					rotate_side(R);
					rotate_side(R);
					break;
				}
				rotate_side(R);
				break;

			default:
				break; /* Skip any nonsence */
		}
		str++; /* Increase pointer */
	}
}

void read_line(const char *filename_to_open, int n) {
	FILE *file;
	char line[100];
	int line_number = 0; /* Line counter */

	file = fopen(filename_to_open, "r");
	if (file == NULL) {
		perror("Error open file");
	}

	while (fgets(line, sizeof(line), file)) {
		line_number++;
		if (line_number == n) { 
			init_cube();
			rotate_cube(line);
			printf("#%d: %s\n", line_number, line); 
			draw_cube();
			printf("\n");
			break; 
		}
	}
	fclose(file);
}

void reset_color() { printf("\033[0m"); }

void set_color(int n) {
	if (n == 0) {
		printf("\e[47m");
	} /* White  */
	if (n == 1) {
		printf("\e[43m");
	} /* Orange */
	if (n == 2) {
		printf("\e[42m");
	} /* Green */
	if (n == 3) {
		printf("\e[41m");
	} /* Red */
	if (n == 4) {
		printf("\e[44m");
	} /* Blue */
	if (n == 5) {
		printf("\x1b[48;5;226m");
	} /* Yellow */
}

void rotate_side(int direction) {
	memcpy(b, cube, sizeof(cube));
	switch (direction) {
		case L:
			cube[1][0] = b[1][6];
			cube[1][1] = b[1][3];
			cube[1][2] = b[1][0];
			cube[1][3] = b[1][7];
			cube[1][4] = b[1][4];
			cube[1][5] = b[1][1];
			cube[1][6] = b[1][8];
			cube[1][7] = b[1][5];
			cube[1][8] = b[1][2];

			cube[0][0] = b[4][8];
			cube[0][3] = b[4][5];
			cube[0][6] = b[4][2];
			cube[4][8] = b[5][0];
			cube[4][5] = b[5][3];
			cube[4][2] = b[5][6];
			cube[5][0] = b[2][0];
			cube[5][3] = b[2][3];
			cube[5][6] = b[2][6];
			cube[2][0] = b[0][0];
			cube[2][3] = b[0][3];
			cube[2][6] = b[0][6];
			break;

		case R:
			cube[0][2] = b[2][2];
			cube[0][5] = b[2][5];
			cube[0][8] = b[2][8];
			cube[2][2] = b[5][2];
			cube[2][5] = b[5][5];
			cube[2][8] = b[5][8];
			cube[5][2] = b[4][6];
			cube[5][5] = b[4][3];
			cube[5][8] = b[4][0];
			cube[4][6] = b[0][2];
			cube[4][3] = b[0][5];
			cube[4][0] = b[0][8];

			cube[3][0] = b[3][6];
			cube[3][1] = b[3][3];
			cube[3][2] = b[3][0];
			cube[3][3] = b[3][7];
			cube[3][4] = b[3][4];
			cube[3][5] = b[3][1];
			cube[3][6] = b[3][8];
			cube[3][7] = b[3][5];
			cube[3][8] = b[3][2];
			break;

		case F:
			cube[2][0] = b[2][6];
			cube[2][1] = b[2][3];
			cube[2][2] = b[2][0];
			cube[2][3] = b[2][7];
			cube[2][4] = b[2][4];
			cube[2][5] = b[2][1];
			cube[2][6] = b[2][8];
			cube[2][7] = b[2][5];
			cube[2][8] = b[2][2];

			cube[0][6] = b[1][8];
			cube[0][7] = b[1][5];
			cube[0][8] = b[1][2];
			cube[1][8] = b[5][2];
			cube[1][5] = b[5][1];
			cube[1][2] = b[5][0];
			cube[5][2] = b[3][0];
			cube[5][1] = b[3][3];
			cube[5][0] = b[3][6];
			cube[3][0] = b[0][6];
			cube[3][3] = b[0][7];
			cube[3][6] = b[0][8];
			break;

		case B:
			cube[4][0] = b[4][6];
			cube[4][1] = b[4][3];
			cube[4][2] = b[4][0];
			cube[4][3] = b[4][7];
			cube[4][4] = b[4][4];
			cube[4][5] = b[4][1];
			cube[4][6] = b[4][8];
			cube[4][7] = b[4][5];
			cube[4][8] = b[4][2];

			cube[0][0] = b[3][2];
			cube[0][1] = b[3][5];
			cube[0][2] = b[3][8];
			cube[3][2] = b[5][8];
			cube[3][5] = b[5][7];
			cube[3][8] = b[5][6];
			cube[5][8] = b[1][6];
			cube[5][7] = b[1][3];
			cube[5][6] = b[1][0];
			cube[1][6] = b[0][0];
			cube[1][3] = b[0][1];
			cube[1][0] = b[0][2];
			break;

		case U:
			cube[0][0] = b[0][6];
			cube[0][1] = b[0][3];
			cube[0][2] = b[0][0];
			cube[0][3] = b[0][7];
			cube[0][4] = b[0][4];
			cube[0][5] = b[0][1];
			cube[0][6] = b[0][8];
			cube[0][7] = b[0][5];
			cube[0][8] = b[0][2];

			cube[2][0] = b[3][0];
			cube[2][1] = b[3][1];
			cube[2][2] = b[3][2];
			cube[3][0] = b[4][0];
			cube[3][1] = b[4][1];
			cube[3][2] = b[4][2];
			cube[4][0] = b[1][0];
			cube[4][1] = b[1][1];
			cube[4][2] = b[1][2];
			cube[1][0] = b[2][0];
			cube[1][1] = b[2][1];
			cube[1][2] = b[2][2];
			break;

		case D:
			cube[5][0] = b[5][6];
			cube[5][1] = b[5][3];
			cube[5][2] = b[5][0];
			cube[5][3] = b[5][7];
			cube[5][4] = b[5][4];
			cube[5][5] = b[5][1];
			cube[5][6] = b[5][8];
			cube[5][7] = b[5][5];
			cube[5][8] = b[5][2];

			cube[2][6] = b[1][6];
			cube[2][7] = b[1][7];
			cube[2][8] = b[1][8];
			cube[1][6] = b[4][6];
			cube[1][7] = b[4][7];
			cube[1][8] = b[4][8];
			cube[4][6] = b[3][6];
			cube[4][7] = b[3][7];
			cube[4][8] = b[3][8];
			cube[3][6] = b[2][6];
			cube[3][7] = b[2][7];
			cube[3][8] = b[2][8];
			break;
	}
}
void draw_cube() {
	int i, j, k = 0;

	for (j = 0; j < 9; j++) {
		if (k == 0) {
			reset_color();
			printf("       ");
		}
		if (k == 3) {
			k = 0;
			printf("\n");
			reset_color();
			printf("       ");
		}
		set_color(cube[0][j]);
		printf("  ");
		reset_color();
		k++;
	}
	printf("\n\n");
	k = 0;

	for (i = 1; i < 5; ++i)
		for (j = 0; j < 3; j++) {
			if (k == 3) {
				k = 0;
				reset_color();
				printf(" ");
			}
			set_color(cube[i][j]);
			printf("  ");
			reset_color();
			++k;
		}
	printf("\n");
	k = 0;

	for (i = 1; i < 5; ++i)
		for (j = 3; j < 6; j++) {
			if (k == 3) {
				k = 0;
				reset_color();
				printf(" ");
			}
			set_color(cube[i][j]);
			printf("  ");
			reset_color();
			++k;
		}
	printf("\n");
	k = 0;

	for (i = 1; i < 5; ++i)
		for (j = 6; j < 9; j++) {
			if (k == 3) {
				k = 0;
				reset_color();
				printf(" ");
			}
			set_color(cube[i][j]);
			printf("  ");
			reset_color();
			++k;
		}
	printf("\n");

	for (j = 0; j < 9; j++) {
		if (k == 0) {
			reset_color();
			printf("       ");
		}
		if (k == 3) {
			k = 0;
			printf("\n");
			reset_color();
			printf("       ");
		}
		set_color(cube[5][j]);
		printf("  ");
		reset_color();
		k++;
	}
	printf("\n");
}

void init_cube() {
	int i;
	int j;
	for (i = 0; i < 6; i++) {
		for (j = 0; j < 9; j++) {
			cube[i][j] = i;	
			}
	}
}