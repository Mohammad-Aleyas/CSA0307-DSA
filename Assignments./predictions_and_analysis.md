# Predictions, outputs and analysis

## Q1 – Binary Search Tree
- Array-tree traversal program prediction: `ABD...` is not the correct way to read the sparse array; for `ABCDE.F`, the actual recursive traversals are `ABDECF`, `DBEAFC`, and `DEBFCA`; the final array scan is `ABCDE F` without the empty marker.
- The supplied deletion program's expected preorder after deleting 20, 30, and 50 is `60 40 70 65 80`.
- In the 2,000-key run, the sorted insertion tree has height 1,999 (worst case); the shuffled insertion tree is much shorter. Exact random height and average comparisons depend on the fixed shuffle and implementation and are recorded in `outputs/q1_bst.txt`.

## Q2 – AVL
- For insertion sequence 10, 20, 30, 40, 50, 25, expected final preorder is `30 20 10 25 40 50`, height 3.
- Sorted 100,000-key insertion remains logarithmic-height; runtime values are machine-dependent and are reported as observed CPU times, not universal constants.

## Q3 – B-tree
- Inserting 10, 20, 5, 6, 12, 30, 7, 17 into minimum-degree-2 B-tree yields sorted traversal `5 6 7 10 12 17 20 30`.
- Search for 6 succeeds; search for 99 fails. Node-read counts are printed by the executable.

## Q4 – Red-black tree
- After each insertion the root remains black, no red node has a red child, and every root-to-leaf path has equal black height. The program checks these invariants after every insertion.

## Q5 – Splay tree
- Each successful access moves the requested key to the root. Alternating accesses to 3 and 9 therefore alternate the root between 3 and 9.

## Q6 – Trie
- Expected prefix counts: `a:5 an:4 anu:2 b:1 z:0`.
- Autocomplete for `an` is `anand anitha anu anusuya`. Deleting `anu` reduces the prefix count for `anu` from 2 to 1.

## Q7 – Dictionary design
- The sample program uses a trie for exact lookup/autocomplete and collects words into a sorted list for range listing. Expected range `[banana..cat]`: `banana band bandit cat`; autocomplete `ba`: `banana band bandit`.
