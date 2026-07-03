# Mini Process Supervisor

## Overview

This project is a simple **Linux process supervisor** written in C. It demonstrates how a parent process can create, monitor, and restart child processes using fundamental Linux system calls.

The supervisor launches multiple worker processes, waits for them to terminate, determines whether they exited normally or crashed, and automatically restarts them.

The project is inspired by the basic principles used by service managers such as `systemd`, but is intentionally kept simple for learning purposes.

---

## Features

* Launches multiple worker processes.
* Tracks each worker using its Process ID (PID).
* Uses `waitpid()` to detect when any child process exits.
* Determines whether a worker:

  * exited normally
  * terminated because of a signal (crashed)
* Automatically restarts terminated workers.
* Demonstrates process supervision using Linux system calls.

---

## Concepts Demonstrated

This project covers several important Linux programming concepts:

* Process creation using `fork()`
* Program execution using `execl()`
* Parent-child relationships
* Process IDs (PIDs)
* Waiting for child processes using `waitpid()`
* Exit status handling
* Detecting crashes using:

  * `WIFEXITED()`
  * `WEXITSTATUS()`
  * `WIFSIGNALED()`
  * `WTERMSIG()`
* Automatic process restart

---

## Project Structure

```text
process-supervisor/
│
├── supervisor.c
├── worker.c
└── README.md
```

---

## How It Works

1. The supervisor starts.
2. It launches three worker processes using `fork()`.
3. Each child immediately executes the `worker` program using `execl()`.
4. The supervisor stores the PID of every worker.
5. The supervisor blocks on `waitpid(-1, &status, 0)` until any worker exits.
6. Once a worker terminates, the supervisor:

   * identifies which worker exited,
   * checks whether it exited normally or crashed,
   * prints the termination reason,
   * launches a replacement worker.

This supervision loop continues indefinitely.

---

## Process Flow

```text
                Supervisor

                     |
        -------------------------
        |           |           |
      fork()      fork()      fork()
        |           |           |
      execl()     execl()     execl()
        |           |           |
     Worker 1    Worker 2    Worker 3
        |           |           |
        +-----------+-----------+
                    |
              waitpid(-1)
                    |
        Child exits or crashes
                    |
          Restart the worker
```

---

## Building

Compile the worker and supervisor separately.

```bash
gcc worker.c -o worker
gcc supervisor.c -o supervisor
```

---

## Running

```bash
./supervisor
```

---

## Sample Output

```text
=================================
 Mini Process Supervisor
 Supervisor PID = 4210
=================================

Worker 1 started with PID 4211
Worker 2 started with PID 4212
Worker 3 started with PID 4213

Worker 2 (PID=4212) terminated
Reason: Crashed
Signal = 11

Restarting Worker 2...

Worker 2 started with PID 4215
```

---

## Important Linux APIs Used

| Function        | Purpose                                            |
| --------------- | -------------------------------------------------- |
| `fork()`        | Creates a child process                            |
| `execl()`       | Replaces the child process with the worker program |
| `waitpid()`     | Waits for a child process to terminate             |
| `getpid()`      | Returns the current process ID                     |
| `WIFEXITED()`   | Checks if a child exited normally                  |
| `WEXITSTATUS()` | Retrieves the child's exit code                    |
| `WIFSIGNALED()` | Checks if a child terminated due to a signal       |
| `WTERMSIG()`    | Returns the signal that terminated the child       |

---

## Learning Objectives

After completing this project, you should understand:

* How Linux creates new processes.
* The relationship between parent and child processes.
* How `exec()` replaces a process image.
* Why zombie processes occur.
* How `waitpid()` retrieves a child's termination status.
* How a supervisor can detect failures and automatically recover by restarting processes.

---

## License

This project is intended for educational purposes to demonstrate Linux process management and process supervision concepts.
