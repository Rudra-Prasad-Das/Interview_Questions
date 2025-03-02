#include <stdio.h>
#include <stdlib.h>

void render_abs(int radius) {
    for (int y = -(radius - 1); y <= (radius - 1); y++) {
        for (int x = (radius - 1); x >= -(radius - 1); x--) {
            if (abs(x) +abs(y) <=radius-1) {
                printf(" x ");
            } else {
                printf(" _ ");
            }
        }
        printf("\n");
    }
}

int main() {
    int radius = 3; // Example test case
    printf("Rendering pattern with radius = %d:\n", radius);
    render_abs(radius);
    return 0;
}
