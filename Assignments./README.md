# CSA0307 – Assignment 4
**Student:** Mohammad Aleyas  
**Register number:** 192521220  
**Course:** Data Structures (DSA)  
**Course code:** CSA0307

## Repository structure
- `Task01/` hash function comparison (poor, polynomial, FNV-1a)
- `Task02/` separate chaining implementation and linear probing demonstration
- `Task03/` max-heap priority queue with stable arrival-order tie-breaking
- `Task04/` quicksort forensic demonstration and stable merge-sort reference
- `Task05/` stable merge sort, six-sort benchmark and OpenMP merge sort
- `Task06/` integrated food-delivery order-processing simulation
- `evidence/` captured compiler and execution output
- `REPORT.pdf` professional written report

## Compiler and commands
Compiler: GCC (record your local `gcc --version` in the submission).
Common command: `gcc -std=c11 -Wall -Wextra -O2 source.c -o program`
Run: `./program`
OpenMP: `gcc -std=c11 -Wall -Wextra -O2 -fopenmp Task05/parallel_merge.c -o parallel_merge`

## Notes
All ordinary C files are compiled using `-std=c11 -Wall -Wextra -O2`. OpenMP is compiled separately with `-fopenmp`. Performance timings depend on CPU, compiler, OS and system load; rerun locally and replace sample evidence with your own machine's results. The 10-million-item OpenMP experiment is provided as a runnable benchmark; the included smoke test uses a smaller input.
The assignment requires progressive commits (at least one per task). Make six separate commits rather than uploading everything in one commit. Add your actual GitHub repository URL to the report and README after creating `CSA03-192521220-Assignment4`.
