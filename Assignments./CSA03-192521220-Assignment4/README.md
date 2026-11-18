# Data Structures – Assignment 4 (CO4)
**Designing Fast Storage and Ordering of Data**

- **Student Name:** Mohammad Aleyas
- **Register Number:** 192521220
- **Course:** Data Structures (CSA0307)
- **Compiler & Version:** GCC 13.2.0 (`gcc -std=c11 -Wall -Wextra -fsanitize=address`)

---

## Repository Structure

| Folder | Task | Description |
| :--- | :--- | :--- |
| `Task01/` | Task 1 | Hash Function Design Review: Poor Hash vs. Polynomial Rolling Hash & FNV-1a (`hash_benchmark.c`) |
| `Task02/` | Task 2 | Collision Resolution: Linear Probing Trace (`linear_probe_trace.c`) & Library Chaining (`library_chaining.c`) |
| `Task03/` | Task 3 | Heaps & Priority Queues: Min-Heap Build (`build_min_heap.c`) & Emergency Triage Max-Heap (`ed_triage.c`) |
| `Task04/` | Task 4 | Sorting Forensics: Lomuto Partition Trace (`lomuto_trace.c`) & Median-of-Three Quicksort (`repaired_quicksort.c`) |
| `Task05/` | Task 5 | Sorting & Parallelism: Stable Order Merge Sort (`stable_merge_sort.c`) & OpenMP Parallel Sort (`parallel_merge_sort.c`) |
| `Task06/` | Task 6 | Design Challenge: Food-Delivery Platform Order Processing Engine (`delivery_platform.c`) |

---

## Compilation & Execution Instructions

Compile any C file using the mandatory C11 flags:
```bash
gcc -std=c11 -Wall -Wextra -fsanitize=address <source_file.c> -o <executable>
./<executable>
```
*(Note: For `Task05/parallel_merge_sort.c`, compile with `-fopenmp`: `gcc -std=c11 -Wall -Wextra -fopenmp parallel_merge_sort.c -o parallel_merge_sort`.)*

---

## Summary of Task Results

- **Task 1:** Replaced 2-character state hash (`max chain ~100,000`) with a 31-base polynomial rolling hash and prime bucket table (`131,071`), reducing max chain length to 6 and average chain length to 0.76 for 100,000 vehicle registrations.
- **Task 2:** Completed separate chaining library lookup (`0200130`, `CSE1044 -> Rahul (3 probes)`, `CSE9999 -> not found (0 probes)`) verified cleanly under `-fsanitize=address`.
- **Task 3:** Implemented Emergency Department Max-Heap triage queue (`P102(9) P106(8) P104(7) P103(5) P101(3) P105(1)`) and verified `O(n)` bottom-up min-heap construction (`1 4 2 9 8 7 6`).
- **Task 4:** Repaired worst-case $O(n^2)$ quicksort stack overflow using median-of-three pivot selection and tail-call elimination on the larger partition.
- **Task 5:** Verified stable order merge sort (`15` comparisons) preserving original relative order of equal amounts (`#2:120` before `#5:120`) and measured multi-threaded OpenMP speedup on 10,000,000 orders.
- **Task 6:** Implemented hybrid Hash Table + Max-Heap + Merge Sort order engine handling 50,000 and 100,000 simulated orders in sub-second total execution time.
