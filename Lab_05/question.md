# Lab 05: Race Conditions and Synchronization using Semaphores

## Problem Statement

Write C programs to demonstrate race conditions and their prevention using semaphores in the following real-world synchronization scenarios:

### i. Critical Section Problem
Simulate multiple processes accessing a shared resource, such as a bank account or shared counter.

### ii. Readers–Writers Problem
Simulate concurrent access to a shared database by multiple readers and writers.

### iii. Dining Philosophers Problem
Simulate resource sharing among competing processes to avoid deadlock and starvation.

## Requirements

Each program should:

1. **Demonstrate the occurrence of a race condition without synchronization**
2. **Use semaphores to synchronize access to shared resources**
3. **Ensure mutual exclusion, progress, and bounded waiting**
4. **Display the correct and synchronized output**
