# 42 Philosophers

## Overview
This project is my implementation of the 42 Philosophers challenge, focused on concurrency, synchronization, and timing correctness.

It includes:
- Mandatory version using threads and mutexes
- Bonus version using processes and semaphores

The central problem: multiple workers compete for limited shared resources (forks). The implementation must prevent data races and avoid deadlock while preserving realistic timing behavior.

## Why This Project Matters
Philosophers is not about printing messages in order. It is about learning how concurrent systems fail when synchronization is weak:
- race conditions on shared state
- deadlocks from circular resource waits
- starvation when one worker is repeatedly blocked
- timing drift that causes incorrect death detection

## What I Implemented
- Strict argument validation and error handling
- Accurate time-based simulation in milliseconds
- Safe shared-state access for death/fullness checks
- Monitoring logic for death and meal completion
- Even/odd fork acquisition strategy to reduce deadlock risk
- Bonus process model with named semaphores

## Core Concepts

### Multithreading (Mandatory)
In the mandatory part, all philosophers run as threads within one process.

Key properties:
- Threads share the same memory space.
- Shared variables are fast to access but unsafe without locks.
- Mutexes protect critical sections (fork usage, state flags, last-meal timestamps).

Main takeaway:
Threading is lightweight and fast, but correctness depends on strict synchronization discipline.

### Multiprocessing (Bonus)
In the bonus part, philosophers run as separate processes.

Key properties:
- Each process has its own memory space.
- State sharing is explicit and typically coordinated via IPC/synchronization primitives.
- Semaphores are used to model shared resource access and guarded output sections.

Main takeaway:
Processes isolate memory better, which can simplify some safety concerns, but coordination and lifecycle management become more complex.

### Mutex vs Semaphore (Practical Difference)
- Mutex: ownership lock, usually for one process/thread domain, ideal for protecting a specific critical section.
- Semaphore: counter-based synchronization primitive, useful for controlling access to a pool of resources and process-level synchronization.

In this project:
- Mutexes fit naturally in the threaded model.
- Semaphores are the natural choice in the process model.

## Build
Mandatory:
- cd philo
- make

Bonus:
- cd philo_bonus
- make

## Run
Mandatory:
- ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

Bonus:
- ./philo_bonus number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

Example:
- ./philo 5 800 200 200 7

Parameter meanings:
- number_of_philosophers: number of workers/forks in the simulation
- time_to_die: max ms without eating before death
- time_to_eat: eating duration in ms
- time_to_sleep: sleeping duration in ms
- number_of_times_each_philosopher_must_eat: optional completion condition

## Project Structure
- philo: thread + mutex implementation
- philo_bonus: process + semaphore implementation

Typical runtime loop:
- think -> take forks/resources -> eat -> release -> sleep -> repeat

Monitor logic runs in parallel to detect death and optional meal completion criteria.

## Key Learnings
- Concurrency design under strict constraints
- Synchronization primitives and shared resource protection
- Timing-sensitive debugging
- Clean cleanup paths for failures and normal exit

## Notes
This project follows 42 rules and coding style constraints.
