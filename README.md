Maze-Generator
==============

Suppose we want to build an n * m rectangular maze, which has only one solution. That is, there should be essentially only one path from the start point to the exit, which doesn't walk two times through the same place. To build the maze, we start with all possible walls between the grid's squares, and remove one wall at a time.

We can model this situation with a graph, in which each square in the rectangular grid is a node, and initially there are no edges. At each step we add an edge between a random pair of grid-neighbor nodes, which where not connected by any path. This guarantees that, at each step, our graph is a forest. We stop when the starting node and the end node are connected. Thanks to the invariant, the connected component in which this two nodes lie is a tree, so there is exactly one simple path between them.

To test if two vertices are connected by some path and, if so, connect them, I used a disjoint-set forests representation with two standard optimization heuristics (path compression and union-by-rank).

The program's input is simply the grid's dimensions.
