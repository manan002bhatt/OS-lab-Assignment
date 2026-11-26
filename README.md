# Operating Systems Lab Programs

This repository contains the 11 C programs required for the Operating Systems lab.

## Programs

1. Linux System Calls: `fork()`, `exec()` and `wait()`
2. Thread Creation and Management using POSIX Threads
3. CPU Scheduling: FCFS, SJF, Priority and Round Robin
4. Producer-Consumer Problem using Semaphores
5. Readers-Writers Problem using Semaphores
6. Dining Philosophers Problem using Semaphores
7. Deadlock Avoidance using Banker's Algorithm
8. Contiguous Memory Allocation: First Fit, Best Fit and Worst Fit
9. Page Replacement: FIFO, LRU and Optimal
10. Disk Scheduling: FCFS, SSTF, SCAN and C-SCAN
11. File Allocation: Contiguous, Linked and Indexed

## Language and Requirements

- Language: C
- Operating System: Linux
- Compiler: GCC
- For pthread and semaphore programs, use the `-pthread` option.

Install GCC on Debian/Ubuntu:

```bash
sudo apt update
sudo apt install build-essential
```

## Compile and Run

Compile a program using:

```bash
gcc filename.c -o program
./program
```

For programs using pthreads and semaphores:

```bash
gcc filename.c -o program -pthread
./program
```

Example:

```bash
gcc 02_pthreads_creation_management.c -o threads -pthread
./threads
```

## Notes

- Each program is a separate C file and has its own `main()` function.
- CPU scheduling uses non-preemptive SJF and Priority. In Priority Scheduling, a smaller priority number means higher priority.
- The Readers-Writers program uses the reader-preference solution.
- The Dining Philosophers program allows at most four philosophers to compete for forks at a time to avoid deadlock.
- Memory allocation and file allocation programs are simple simulations for learning the algorithms.

## Upload to GitHub

Create a new repository on GitHub. Open a terminal inside this folder and run:

```bash
git init
git add .
git commit -m "Add OS lab programs"
git branch -M main
git remote add origin https://github.com/USERNAME/REPOSITORY.git
git push -u origin main
```

Replace `USERNAME` and `REPOSITORY` with your GitHub username and repository name.
