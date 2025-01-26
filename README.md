# Data Structures and Algorithms in C

A collection of concise and efficient implementations of various Data Structures and Algorithms (DSA) in pure C. Each implementation prioritizes functionality and brevity, making it ideal for educational purposes, quick reference, and foundational understanding.

## Table of Contents

- [Data Structures](#data-structures)
  - [AVL Trees](#avl-trees)
  - [Splay Trees](#splay-trees)
  - [B-Trees](#b-trees)
  - [Red-Black Trees](#red-black-trees)
  - [Disjoint Sets](#disjoint-sets)
  - [Binary Indexed Trees (Fenwick Trees)](#binary-indexed-trees-fenwick-trees)
  - [Generic Linked Lists](#generic-linked-lists)
  - [XOR Linked Lists](#xor-linked-lists)
  - [Self-Organizing Lists](#self-organizing-lists)
  - [N-ary Trees](#n-ary-trees)
- [Algorithms](#algorithms)
  - [Sparse Set](#sparse-set)
  - [Sparse Table](#sparse-table)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
- [Usage](#usage)
- [Contributing](#contributing)

## Data Structures

### AVL Trees

Self-balancing binary search trees ensuring O(log n) time complexity for insertions, deletions, and lookups.

### Splay Trees

Self-adjusting binary search trees with the additional property that recently accessed elements are quick to access again.

### B-Trees

Balanced tree data structures optimized for systems that read and write large blocks of data, commonly used in databases and filesystems.

### Red-Black Trees

Balanced binary search trees with an additional color attribute for nodes, ensuring balanced height and efficient operations.

### Disjoint Sets

Data structures that keep track of a set of elements partitioned into disjoint (non-overlapping) subsets, supporting union and find operations efficiently.

### Binary Indexed Trees (Fenwick Trees)

Efficient data structures for cumulative frequency tables, supporting point updates and range queries in logarithmic time.

### Generic Linked Lists

Flexible linked list implementations capable of storing data of any type using void pointers.

### XOR Linked Lists

Memory-efficient linked lists that use XOR of node addresses to store pointers, reducing memory usage by nearly half.

### Self-Organizing Lists

Linked lists that reorder themselves based on access patterns to optimize for frequently accessed elements.

### N-ary Trees

Tree structures where each node can have up to N children, suitable for representing hierarchical data like file systems.

## Algorithms

### Sparse Set

An efficient set representation that allows O(1) time complexity for insertion, deletion, and membership checks.

### Sparse Table

A data structure that allows answering range queries (like minimum, maximum) in constant time after O(n log n) preprocessing.

## Getting Started

### Prerequisites

- GCC Compiler
- Make (optional)

### Installation

1. **Clone the Repository**

   ```bash
   git clone https://github.com/Vbansal21/DSA_Lab_Code.git
   cd DSA_Lab_Code
   ```

2. **Compile the Code**

   Each data structure or algorithm has its own C file. To compile, use:

   ```bash
   gcc -o avl avl.c
   gcc -o splay_tree splay_tree.c
   gcc -o bTree bTree.c
   ...
   ```

   Alternatively, use the provided `Makefile` (if available):

   ```bash
   make
   ```

## Usage

After compiling, execute the binaries to see the implementations in action.

```bash
./avl
./splay_tree
./bTree
...
```

Each program includes sample operations demonstrating the functionality of the respective data structure or algorithm.

## Contributing

Contributions are welcome! Please fork the repository and submit a pull request with your enhancements or additional implementations.

1. Fork the Repository
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

---

README generated using ChatGPT.
