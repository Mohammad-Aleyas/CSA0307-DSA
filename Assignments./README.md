# Data Structures Assignment 3 – CO3

**Student:** Mohammad Aleyas  
**Register number:** 192521220  
**Department:** Information Technology  
**Academic year:** 2nd Year  
**Faculty:** Manoj H.D.  
**Institution:** SIMATS Engineering

This repository contains seven standalone C programs, sample input files, captured program outputs, terminal-style execution evidence, and tree diagrams. It is designed to accompany the assignment report.

## Contents

- `src/q1_bst.c` – BST insertion, search/comparison counting, traversals, height, deletion, 2,000-key experiment, preorder save.
- `src/q2_avl.c` – AVL insertion, rotations, height/balance validation, 100,000 sorted-key experiment and timing.
- `src/q3_btree.c` – B-tree (minimum degree 2) insertion with splits, traversal and search/node-read counts.
- `src/q4_red_black.c` – Red-black insertion, rotations/recolouring and invariant validation.
- `src/q5_splay.c` – Splay insertion/access sequence and root changes.
- `src/q6_trie.c` – Trie insertion, exact search, prefix count, autocomplete, deletion and cleanup.
- `src/q7_dictionary.c` – Dictionary prototype combining trie lookup/autocomplete with sorted range listing.
- `inputs/` – Sample data used by the programs.
- `outputs/` – Actual stdout captured from the compiled programs.
- `screenshots/` – Readable terminal-style images generated from those captured outputs.
- `diagrams/` – Tree structure diagrams.
- `predictions_and_analysis.md` – Predicted outputs and interpretation.

## Compile and run

Requires GCC or another C11 compiler. From the repository root:

```bash
mkdir -p bin
for f in src/*.c; do
  name=$(basename "$f" .c)
  gcc -std=c11 -O2 -Wall -Wextra "$f" -o "bin/$name"
  "bin/$name"
done
```

Run one program, for example:

```bash
gcc -std=c11 -O2 src/q3_btree.c -o bin/q3_btree
./bin/q3_btree
```

Q1 writes `outputs/bst_preorder.txt` when run from the repository root.

## Evidence and interpretation

The `.txt` files in `outputs/` are direct stdout captures from successful local compilation and execution in the preparation environment. Timing values are machine-dependent; they should be rerun on the student's computer if the report requires local timings. The 100,000-key AVL experiment is measured by `clock()` and is not a benchmark comparison against a fully implemented 100,000-key BST or red-black tree.

The Q7 program is a compact working prototype on a ten-word test fixture, not a full 200,000-word production dictionary. Expand the fixture and measure memory/latency on the target phone before making production claims. The B-tree implementation demonstrates insertion and search for the assignment's eight-key example; deletion is not implemented. The red-black implementation demonstrates insertion and invariant checking; deletion is not implemented. The splay implementation demonstrates insertion and access; deletion/workload benchmarking is not implemented.

## GitHub submission

Create a new public or faculty-approved private repository on GitHub, then run:

```bash
git init
git add .
git commit -m "Complete Data Structures Assignment 3"
git branch -M main
git remote add origin https://github.com/YOUR-USERNAME/data-structures-assignment-3.git
git push -u origin main
```

Replace the example remote with the URL of the repository you create. Do not submit the example URL as if it were real.
