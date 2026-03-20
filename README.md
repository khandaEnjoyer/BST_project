Tree Data Structures Benchmark
Description

This project compares the performance of three tree-based data structures:

Binary Search Tree (BST)

AVL Tree

Splay Tree

The goal is to analyze how different structures behave under various query distributions and workloads.

⚙️ Features

✅ Implementation of:

BST (non-balanced)

AVL Tree (self-balancing)

Splay Tree (self-adjusting)

✅ Performance benchmarking:

Tree construction time

Query time

Average number of node visits

✅ Large-scale testing:

Up to 1,000,000 elements

Up to 100,000,000 queries

✅ Configurable input distribution:

Custom sampler with parameter α

Simulates non-uniform access patterns

🧠 Key Concepts

Self-balancing trees

Tree rotations (AVL, Splay)

Amortized complexity

Cache/locality effects in data structures

Performance benchmarking

▶️ How to Run
g++ main.cpp -O2 -o benchmark
./benchmark

📊 Output

The program prints:

Tree construction time

Tree height

Average number of node visits

Query execution time
