## Problem Overview
A multithreaded simulation of the classic **[Dining Philosophers Problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem)**, illustrating concurrency issues such as deadlock, resource contention, and starvation.
The Dining Philosophers Problem involves five philosophers who alternate between thinking and eating. Each philosopher requires two forks to eat, but there are only five forks available. This creates a synchronization challenge to ensure:

- Deadlock does not occur.
- Philosophers do not starve.
- Resource utilization remains efficient.

## Solution Implementation

This simulation uses **mutex locks** to control access to shared resources (forks). The approach includes:

1. **Thinking and Eating States:** Philosophers alternate between thinking for a random duration and attempting to eat.
2. **Fork Acquisition:**
   - Each philosopher tries to acquire the fork on their left and right.
   - Mutex locks ensure that forks are only held by one philosopher at a time.
   - If a philosopher acquires one fork but cannot acquire the other within a specified retry limit, they release the held fork and retry after a short delay.
3. **Deadlock Mitigation:**
   - Philosophers do not block indefinitely waiting for forks.
   - A retry mechanism and random delays reduce contention and prevent cyclic waiting.

## How to Run

Follow these steps to clone, compile, and run the program:
1. **Clone the Repository:**
   ```bash
   git clone https://github.com/Silence-o0/PhilosophersDinner.git
   ```
2. **Navigate to the Project Directory:**
   ```bash
   cd PhilosophersDinner
   ```
3. **Compile the Program:**
   ```bash
   g++ -std=c++20 -pthread main.cpp -o philosophers_dinner
   ```
4. **Run the Program:**
   ```bash
   ./philosophers_dinner
   ```
