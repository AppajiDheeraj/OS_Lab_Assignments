#include <stdio.h>

void simulateOptimal(int pages[], int n, int frames) {
    int temp[frames], faults = 0;
    for (int i = 0; i < frames; i++) temp[i] = -1;

    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < frames; j++) {
            if (temp[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {
            int pos = -1;
            // Fill empty slots
            for (int j = 0; j < frames; j++) {
                if (temp[j] == -1) {
                    pos = j;
                    break;
                }
            }
            // If full, look into future
            if (pos == -1) {
                int farthest = -1;
                for (int j = 0; j < frames; j++) {
                    int k;
                    for (k = i + 1; k < n; k++) {
                        if (temp[j] == pages[k]) break;
                    }
                    if (k > farthest) {
                        farthest = k;
                        pos = j;
                    }
                }
            }
            temp[pos] = pages[i];
            faults++;
        }
    }
    printf("Optimal | Frames: %d | Page Faults: %d\n", frames, faults);
}

int main() {
    int pages[] = {6, 7, 8, 9, 6, 7, 1, 6, 7, 8, 9, 1, 7, 9, 6};
    int n = 15;

    printf("--- Optimal Page Replacement ---\n");
    simulateOptimal(pages, n, 3); // Expected: 8

    return 0;
}