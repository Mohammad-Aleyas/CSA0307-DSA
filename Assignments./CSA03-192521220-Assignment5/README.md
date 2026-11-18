# Data Structures – Assignment 5 (CO5)
**Modelling and Analysing Real-World Networks with Graphs**

- **Student Name:** Mohammad Aleyas
- **Register Number:** 192521220
- **Course:** Data Structures (CSA0307)
- **Compiler & Version:** GCC 13.2.0 (`gcc -std=c11 -Wall -Wextra -fsanitize=address`)

---

## Repository Structure

| Folder | Task | Description |
| :--- | :--- | :--- |
| `TaskA2/` | Part A – Task A2 | Depth-First Search (`dfs.c`) & Breadth-First Search (`bfs.c`) on 6-vertex graph |
| `TaskA3/` | Part A – Task A3 | Kahn's Topological Sort (`kahn_topo.c`) & Cycle Detection (`kahn_cycle.c`) |
| `TaskA5/` | Part A – Task A5 | Prim's Minimum Spanning Tree (`prim_mst.c`) for 5-village fibre network |
| `TaskB1/` | Part B – Task B1 | CSR Metro Network BFS (`metro_bfs.c`) & Matrix vs. List Benchmark (`rep_bench.c`) |
| `TaskB2/` | Part B – Task B2 | Dijkstra Shortest Path (`dijkstra.c`) & Difficult Input Suite (`dijkstra_edge_cases.c`) |
| `TaskB3/` | Part B – Task B3 | Shortest-Path Comparison: Array Dijkstra, Heap Dijkstra, Floyd-Warshall, and A* (`sp_compare.c`) |
| `TaskB4/` | Part B – Task B4 | 5-City Scalability & 20-Hub Fibre Cabling Extension (`hub_extension.c`) |

---

## Compilation & Execution Instructions

Compile any C file using the mandatory flags:
```bash
gcc -std=c11 -Wall -Wextra -fsanitize=address <source_file.c> -o <executable>
./<executable>
```
*(Note: For `TaskB3/sp_compare.c`, append `-lm` if linking math functions.)*

---

## Summary of Task Results

- **Task A2:** Verified pre-execution prediction `0 1 3 5 4 2` for `dfs(0)` and `0 1 2 3 4 5` for `bfs(0)`.
- **Task A3:** Verified valid hub setup schedule `Lease Power Racks Staff Network Launch` and confirmed cycle detection (`cycle detected`) when adding `Launch -> Lease`.
- **Task A5:** Computed minimum fibre cabling cost of **16 Rs lakh** (`0-1(2), 1-2(3), 0-3(6), 1-4(5)`).
- **Task B1:** Verified shortest metro route from Airport to Koyambedu is **3 stops** (`Airport -> Guindy -> Vadapalani -> Koyambedu`). Confirmed Adjacency List uses ~1.5 MB at 50,000 junctions compared to ~10 GB for an Adjacency Matrix.
- **Task B2:** Verified shortest travel times `0 7 9 20 20 11` and route `0 -> 2 -> 5 -> 4`. Demonstrated unreachable node reporting, negative edge failure vs. Floyd-Warshall, `INT_MAX` overflow prevention, and cycle detection.
- **Task B3:** Verified identical distances across Array Dijkstra, Binary-Heap Dijkstra, and Floyd-Warshall on 8 vertices. Benchmarked up to 10,000 vertices and confirmed A* reduces explored nodes on obstacle grids.
- **Task B4:** Computed 20-hub fibre MST and demonstrated automatic rerouting upon link failure.
