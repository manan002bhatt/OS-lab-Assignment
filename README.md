# Operating Systems Lab Programs

Eleven standalone C programs for the Operating Systems laboratory.

## Program list

| No. | Source file | Topic |
|---:|---|---|
| 1 | `01_system_calls_fork_exec_wait.c` | Linux system calls, fork(), exec() and wait() |
| 2 | `02_pthreads_creation_management.c` | POSIX thread creation and management |
| 3 | `03_cpu_scheduling_algorithms.c` | FCFS, SJF, Priority and Round Robin CPU scheduling |
| 4 | `04_producer_consumer_semaphores.c` | Producer-Consumer using semaphores |
| 5 | `05_readers_writers_semaphores.c` | Readers-Writers using semaphores |
| 6 | `06_dining_philosophers_semaphores.c` | Dining Philosophers using semaphores |
| 7 | `07_bankers_algorithm.c` | Banker's deadlock-avoidance algorithm |
| 8 | `08_contiguous_memory_allocation.c` | First Fit, Best Fit and Worst Fit memory allocation |
| 9 | `09_page_replacement_algorithms.c` | FIFO, LRU and Optimal page replacement |
| 10 | `10_disk_scheduling_algorithms.c` | FCFS, SSTF, SCAN and C-SCAN disk scheduling |
| 11 | `11_file_allocation_methods.c` | Contiguous, Linked and Indexed file allocation |

## Requirements

- Linux system (Debian/Ubuntu recommended)
- GCC compiler and POSIX threads/semaphores

Install tools on Debian/Ubuntu:

```bash
sudo apt update
sudo apt install build-essential
```

## Compile and run one program

For programs using pthreads/semaphores (2, 4, 5 and 6), include `-pthread`:

```bash
gcc -Wall -Wextra -pthread -o program 02_pthreads_creation_management.c
./program
```

For the other programs:

```bash
gcc -Wall -Wextra -o program 01_system_calls_fork_exec_wait.c
./program
```

Replace the source filename with the program you want to compile.

## Compile all programs

Run this from the repository directory. It creates an executable beside each source file:

```bash
for file in *.c; do
    exe="${file%.c}"
    case "$file" in
        02_*|04_*|05_*|06_*) gcc -Wall -Wextra -pthread "$file" -o "$exe" || exit 1 ;;
        *) gcc -Wall -Wextra "$file" -o "$exe" || exit 1 ;;
    esac
done
```

## Implementation notes

- CPU scheduling uses non-preemptive SJF and Priority; lower numeric priority means higher priority. Round Robin asks for a time quantum.
- Readers-Writers is the reader-preference semaphore solution; writer starvation is possible if readers continuously arrive.
- Dining Philosophers uses a room semaphore initialized to N-1 to prevent circular-wait deadlock.
- SCAN initially moves toward cylinder 0. C-SCAN initially moves toward the highest cylinder; the wraparound movement is counted.
- Memory and file allocation programs are educational simulations, not actual allocation of physical RAM or disk sectors.
- Program 1 creates `syscall_demo.txt` in the current directory.

## Suggested GitHub upload

Create an empty repository on GitHub, then run these commands here (replace the URL):

```bash
git init
git add .
git commit -m "Add Operating Systems lab programs"
git branch -M main
git remote add origin https://github.com/USERNAME/REPOSITORY.git
git push -u origin main
```

Upload the `.c` files and `README.md`. Do not upload compiled executables unless your teacher requests them.
