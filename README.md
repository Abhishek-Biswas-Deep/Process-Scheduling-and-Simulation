<img src="https://github.com/user-attachments/assets/2ad86f70-12b4-4500-997d-9f8c1874a9b5" alt="Dal logo" width="80"/>
<h1>Associated with Dalhousie University</h1>

### CSCI3120

### Process Scheduling and Simulation
This project is a Process Scheduling Simulator that evolves through multiple stages, implementing various scheduling algorithms, multithreading techniques, and inter-process communication. The simulation models a system running multiple processes on a single processor, extending to multi-node communication using threads.

#### Overview
The objective of this project is to simulate a simplified operating system that manages processes using different scheduling algorithms like Round Robin, Shortest Job First (SJF), and Priority-based scheduling. The simulation evolves to support multithreading, where each node runs a scheduler and manages processes independently. In later stages, inter-process communication through message passing is introduced, allowing processes on different nodes to communicate.

#### Features
- Process Scheduling: Supports various scheduling algorithms such as Round Robin, Shortest Job First, and Priority-based scheduling with preemption.
- Quantum Control: Configurable quantum size for Round Robin scheduling.
- Multithreading: Simulates multiple nodes running concurrently, each with its own scheduler.
- Message Passing: Processes on different nodes communicate through synchronous message passing.
- Priority Queues: Manages ready and blocked processes using priority-based queues.
- State Tracking: Tracks and outputs the state transitions (new, ready, running, blocked, finished) of each process.
- Statistics: Outputs statistics for each process, including the total time spent running, blocked, and waiting.

#### Scheduling Algorithms
- Round Robin (RR): Time-slicing based on quantum length. Processes are scheduled in a cyclic order with preemption after the quantum expires.
- Shortest Job First (SJF): Processes with the shortest remaining execution time are scheduled first.
- Priority-Based Scheduling: Processes with higher priority (lower numeric value) are scheduled first. Preemption occurs when a higher-priority process becomes ready.

#### Input Format
The input consists of:

The number of processes (NumProcs) and the quantum length (Quantum).
- For each process:
1. Process Name: Name of the process.
2. Size: The number of operations (primitives) in the process description.
3. Priority: The priority value of the process (used for Priority Scheduling).
4. Sequence of Primitives: DOOP, BLOCK, LOOP, END, HALT, SEND, RECV.

#### Sample input and output
```
Input
4 5 2
Proc1 3 1 1
SEND 201
RECV 202
HALT
Proc2 3 1 1
RECV 202
SEND 201
HALT
Proc3 3 1 2
RECV 101
RECV 102
HALT
Proc4 3 1 2
SEND 102
SEND 101
HALT

Output
[02] 00000: process 1 new
[02] 00000: process 1 ready
[02] 00000: process 2 new
[02] 00000: process 2 ready
[01] 00000: process 1 new
[01] 00000: process 1 ready
[01] 00000: process 2 new
[01] 00000: process 2 ready
[01] 00000: process 1 running
[02] 00000: process 1 running
[02] 00001: process 1 blocked (recv)
[02] 00001: process 2 running
[01] 00001: process 1 blocked (send)
[01] 00001: process 2 running
[01] 00002: process 1 ready
[01] 00002: process 2 blocked (recv)
[01] 00002: process 1 running
[02] 00002: process 1 ready
[02] 00002: process 2 blocked (send)
[02] 00002: process 1 running
[02] 00003: process 2 ready
[02] 00003: process 1 blocked (recv)
[02] 00003: process 2 running
[01] 00003: process 2 ready
[01] 00003: process 1 blocked (recv)
[01] 00003: process 2 running
[01] 00004: process 2 blocked (send)
[02] 00004: process 2 blocked (send)
[02] 00005: process 1 finished
[02] 00005: process 2 finished
[01] 00005: process 1 finished
[01] 00005: process 2 finished
| 00005 | Proc 01.01 | Run 2, Block 0, Wait 0, Sends 1, Recvs 1
| 00005 | Proc 01.02 | Run 2, Block 0, Wait 1, Sends 1, Recvs 1
| 00005 | Proc 02.01 | Run 2, Block 0, Wait 0, Sends 0, Recvs 2
| 00005 | Proc 02.02 | Run 2, Block 0, Wait 1, Sends 2, Recvs 0
```
#### Note - This is an example only, and the order of the above will change between runs!

#### Multithreading and Parallel Execution
The simulator supports parallel execution by running multiple threads, each representing a separate node. Each node has its own scheduler and manages processes independently. The system ensures that processes are handled concurrently by using mutex locks and shared data structures.

#### Key points:
- Each node operates independently with its own process queue.
- Threads are synchronized using barriers to maintain consistent execution timing across nodes.
-Processes can be distributed across nodes to simulate real-world distributed systems.

#### Message Passing Between Processes
The simulator introduces inter-process communication using synchronous message passing. Processes can send and receive messages, which may occur between processes on different nodes.
- SEND: A process sends a message to another process and blocks until the message is received.
- RECV: A process receives a message from another process and blocks until the message is sent.
- Message passing is synchronous, meaning both the sender and receiver block until the operation is completed.

##### Feel free to contribute and enhance.
