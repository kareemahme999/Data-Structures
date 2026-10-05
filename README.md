# Advanced Data Structures

C++ implementations and notes for the **Advanced Data Structures** course. Each topic lives in its own folder with source code, examples, and documentation. The repository grows as the course progresses.

---

## Course Topics

| # | Topic | Folder | Status |
|---|---|---|---|
| 1 | [Red-Black Trees](#1-red-black-trees) | `01-red-black-trees/` | ✅ Implemented |
| 2 | [B-Trees](#2-b-trees) | `02-b-trees/` | 🕒 Coming soon |
| 3 | [Tries and Suffix Trees](#3-tries-and-suffix-trees) | `03-tries-and-suffix-trees/` | 🕒 Coming soon |
| 4 | [Suffix Arrays](#4-suffix-arrays) | `04-suffix-arrays/` | 🕒 Coming soon |
| 5 | [Interval and Segment Trees](#5-interval-and-segment-trees) | `05-interval-and-segment-trees/` | 🕒 Coming soon |
| 6 | [Range and Kd Trees](#6-range-and-kd-trees) | `06-range-and-kd-trees/` | 🕒 Coming soon |
| 7 | [Disjoint Sets](#7-disjoint-sets) | `07-disjoint-sets/` | 🕒 Coming soon |
| 8 | [Bloom Filters](#8-bloom-filters) | `08-bloom-filters/` | 🕒 Coming soon |

---

## Repository Structure

```
Advanced-Data-Structures/
├── README.md
├── 01-red-black-trees/
│   ├── Red_Black_Tree.h
│   ├── main.cpp
│   └── README.md
├── 02-b-trees/
├── 03-tries-and-suffix-trees/
├── 04-suffix-arrays/
├── 05-interval-and-segment-trees/
├── 06-range-and-kd-trees/
├── 07-disjoint-sets/
└── 08-bloom-filters/
```

## Requirements

- A C++11 (or newer) compiler such as `g++`, `clang++`, or MSVC

Each topic folder is self-contained. Build and run it from inside its own folder.

---

## 1. Red-Black Trees

A header-only implementation of a **Red-Black Tree**, a self-balancing binary search tree. Search, insertion, and deletion all run in **O(log n)** time. The project includes an interactive menu to build and explore the tree.

**Status:** ✅ Implemented

### Features

- Insert values with automatic rebalancing (recoloring and rotations)
- Delete values by key
- Search for a value and report its color, parent, and position
- Print the tree as a sideways diagram with node colors
- Interactive `switch` menu with safe input handling

### How it works

Every node is either red or black, and the tree keeps these rules:

1. The root is black.
2. A red node never has a red child.
3. Every path from a node down to its empty children has the same number of black nodes.

When an insert or delete breaks a rule, the tree repairs itself with recoloring and rotations (`fixInsert`, `fixDelete`, `leftRotate`, `rightRotate`).

### Build and run

```bash
cd 01-red-black-trees
g++ -std=c++11 main.cpp -o rbtree
./rbtree
```

### Interactive menu

```
===== Red-Black Tree Menu =====
1. Insert a value
2. Delete a value
3. Search for a value
4. Print the tree
0. Exit
```

### Usage in code

```cpp
#include "Red_Black_Tree.h"

int main() {
    RedBlackTree tree;

    tree.insert(10);
    tree.insert(5);
    tree.insert(15);

    tree.printTree();
    tree.searchAndPrint(15);   // 15 found. Color: BLACK, parent = 10 (right child)
    tree.remove(5);
}
```

### API

| Method | Returns | Description |
|---|---|---|
| `insert(int val)` | `void` | Inserts `val` and rebalances. Duplicates go right. |
| `remove(int val)` | `void` | Deletes the first node matching `val`. |
| `search(int val) const` | `bool` | `true` if `val` exists. Prints nothing. |
| `searchAndPrint(int val) const` | `void` | Prints whether `val` was found, with its color and parent. |
| `printTree()` | `void` | Prints the tree sideways (root on the left). |

### Complexity

| Operation | Time |
|---|---|
| Insert | O(log n) |
| Delete | O(log n) |
| Search | O(log n) |
| Print | O(n) |

### Known limitations

- **Delete rebalancing gap:** `fixDelete` is only called when the replacement node is not `nullptr`, so deleting a black node with no children can leave the tree unbalanced.
- **No destructor:** nodes are not freed when the tree goes out of scope.
- **Copying** is not disabled.
- Keys are `int` only.

### Planned improvements

- [ ] Fix black-leaf deletion in `fixDelete`
- [ ] Add a destructor and disable copying
- [ ] Add an `isValid()` checker
- [ ] Add tree traversals (in-order, pre-order, post-order, level-order)
- [ ] Convert to a template (`RedBlackTree<T>`)

---

## 2. B-Trees

**Status:** 🕒 Coming soon

*Description, features, build instructions, and API will be added here.*

---

## 3. Tries and Suffix Trees

**Status:** 🕒 Coming soon

*Description, features, build instructions, and API will be added here.*

---

## 4. Suffix Arrays

**Status:** 🕒 Coming soon

*Description, features, build instructions, and API will be added here.*

---

## 5. Interval and Segment Trees

**Status:** 🕒 Coming soon

*Description, features, build instructions, and API will be added here.*

---

## 6. Range and Kd Trees

**Status:** 🕒 Coming soon

*Description, features, build instructions, and API will be added here.*

---

## 7. Disjoint Sets

**Status:** 🕒 Coming soon

*Description, features, build instructions, and API will be added here.*

---

## 8. Bloom Filters

**Status:** 🕒 Coming soon

*Description, features, build instructions, and API will be added here.*

---

## Adding a New Topic

When you finish a topic, copy this template into its section and change the status in the table at the top to ✅ Implemented:

```markdown
## N. Topic Name

Short description of the data structure and why it is useful.

**Status:** ✅ Implemented

### Features
- ...

### Build and run
​```bash
cd 0N-topic-name
g++ -std=c++11 main.cpp -o app
./app
​```

### API
| Method | Returns | Description |
|---|---|---|
| ... | ... | ... |

### Complexity
| Operation | Time |
|---|---|
| ... | ... |

### Known limitations
- ...
```

---

<div align="center">

<h3><i>Written &amp; maintained by</i></h3>

<h2><code>Kareem Ahmed</code></h2>

<sub><i>Learning data structures by building them, one at a time.</i></sub>

</div>
