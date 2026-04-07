#include <stdio.h>

void simulateLRU(int pages[], int n, int frames) {
    int temp[frames], timeStamp[frames], faults = 0;
    
    for (int i = 0; i < frames; i++) {
        temp[i] = -1;
        timeStamp[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < frames; j++) {
            if (temp[j] == pages[i]) {
                found = 1;
                timeStamp[j] = i; // Update last used time
                break;
            }
        }
        
        if (!found) {
            int pos = -1;
            // First: Look for an empty slot
            for (int j = 0; j < frames; j++) {
                if (temp[j] == -1) {
                    pos = j;
                    break;
                }
            }
            // Second: If full, find page with smallest timestamp (LRU)
            if (pos == -1) {
                int min = timeStamp[0];
                pos = 0;
                for (int j = 1; j < frames; j++) {
                    if (timeStamp[j] < min) {
                        min = timeStamp[j];
                        pos = j;
                    }
                }
            }
            temp[pos] = pages[i];
            timeStamp[pos] = i;
            faults++;
        }
    }
    printf("LRU | Frames: %d | Page Faults: %d\n", frames, faults);
}

int main() {
    int pages[] = {6, 7, 8, 9, 6, 7, 1, 6, 7, 8, 9, 1, 7, 9, 6};
    int n = 15;

    printf("--- LRU Page Replacement ---\n");
    simulateLRU(pages, n, 3); // Expected: 12

    return 0;
}