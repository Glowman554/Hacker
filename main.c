#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>


// #define RAND_MAX 32767
unsigned long next = 24629;

int rand() {
    next = next * 1103515245 + 12345;
    return (uint32_t) (next / 65536) % RAND_MAX + 1; 
}

uint8_t buffer[1000][1000] = {0};
uint8_t resets[1000] = {0};
uint64_t num_frames_rendered = 0;

int rows = 20;
int cols = 100;

void frame() {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (i == 0) {
				buffer[i][j] = (buffer[i][j] + 1) % (resets[j] + 2);
				
				if(buffer[i][j] == 0) {
					resets[j] = (rand() % rows);
				}

			} else {
				if(buffer[i - 1][j] != 0) {
					if(buffer[i - 1][j] - 1 > 0) {
						buffer[i][j] = buffer[i - 1][j] - 1;
					} else {
						buffer[i][j] = 0;
					}
				} else {
					buffer[i][j] = 0;
				}
			}
		}
	}

	system("clear");
	printf("\033[32m");
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (buffer[i][j]) {
				putchar('X');
			} else {
				putchar(' ');
			}
		}
		putchar('\n');
	}
	printf("\033[0m");
}

int main() {
	printf("Rows, Columns > ");
	scanf("%d,%d", &rows, &cols);
	
	while (1) {
		frame();
		usleep(1000 * 100);
	}

	return 0;
}