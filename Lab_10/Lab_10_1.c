#include <stdio.h>

void simulateFIFO(int pages[], int n, int frames) {
    int temp[frames], faults = 0, s = 0;
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
            temp[s] = pages[i];
            s = (s + 1) % frames; // Replace oldest page
            faults++;
        }
    }
    printf("FIFO | Frames: %d | Page Faults: %d\n", frames, faults);
}

int main() {
    int pages[] = {6, 7, 8, 9, 6, 7, 1, 6, 7, 8, 9, 1};
    int n = 12;

    printf("--- FIFO: Verifying Belady's Anomaly ---\n");
    simulateFIFO(pages, n, 3); // Expected: 9
    simulateFIFO(pages, n, 4); // Expected: 10 (Anomaly detected)
    simulateFIFO(pages, n, 5); 

    return 0;
}