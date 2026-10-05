# Red-Black Tree in C++

A header-only C++ implementation of a **Red-Black Tree**, a self-balancing binary search tree, with an interactive command-line menu to build and explore the tree.

Search, insertion, and deletion all run in **O(log n)** time because the tree keeps itself balanced after every change.

---

## Table of Contents

- [Features](#features)
- [How a Red-Black Tree Works](#how-a-red-black-tree-works)
- [Project Structure](#project-structure)
- [Getting Started](#getting-started)
- [Interactive Menu](#interactive-menu)
- [Using the Class in Your Own Code](#using-the-class-in-your-own-code)
- [API Reference](#api-reference)
- [Example Output](#example-output)
- [Implementation Notes](#implementation-notes)
- [Known Limitations](#known-limitations)
- [Roadmap](#roadmap)
- [Author](#author)

---

## Features

- **Insert** values with automatic rebalancing (recoloring and rotations)
- **Delete** values by key
- **Search** for a value and report its color, parent, and position (left or right child)
- **Visualize** the tree as a sideways diagram with node colors
- **Interactive menu** driven by a `switch` statement
- **Safe input handling**: typing letters instead of numbers does not break the program
- **Header-only**: just include one file

---

## How a Red-Black Tree Works

Every node is either **red** or **black**, and the tree maintains these rules:

1. The root is black.
2. A red node never has a red child (no two reds in a row).
3. Every path from a node down to its empty children contains the same number of black nodes.

When an insert or delete breaks one of these rules, the tree repairs itself using **recoloring** and **rotations**:

| Operation | Repair function | Tools used |
|---|---|---|
| Insert | `fixInsert` | Recoloring, left/right rotation |
| Delete | `fixDelete` | Recoloring, left/right rotation |

These rules guarantee that the longest path is never more than twice as long as the shortest path, so the height stays at **O(log n)**.

---

## Project Structure

```
Red-Black-tree/
├── Red_Black_Tree.h   # Node and RedBlackTree classes (header-only)
├── main.cpp           # Interactive menu program
└── README.md
```

---

## Getting Started

### Requirements

- A C++11 (or newer) compiler, such as `g++`, `clang++`, or MSVC

### Build and run

```bash
g++ -std=c++11 main.cpp -o rbtree
./rbtree
```

On Windows:

```bash
g++ -std=c++11 main.cpp -o rbtree.exe
rbtree.exe
```

Or open the folder in Xcode, Visual Studio, or CLion and run `main.cpp`.

---

## Interactive Menu

When you run the program, you can build your own tree:

```
===== Red-Black Tree Menu =====
1. Insert a value
2. Delete a value
3. Search for a value
4. Print the tree
0. Exit
Choose an option:
```

| Option | Action |
|---|---|
| `1` | Insert an integer into the tree |
| `2` | Delete an integer from the tree (prints a message if not found) |
| `3` | Search for an integer and show its color and parent |
| `4` | Print the current tree structure |
| `0` | Exit the program |

### Sample session

```
Choose an option: 1
Enter value to insert: 10
10 inserted.

Choose an option: 3
Enter value to search: 10
10 found. Color: BLACK, it is the root.

Choose an option: 3
Enter value to search: 99
99 not found.
```

---

## Using the Class in Your Own Code

```cpp
#include <iostream>
#include "Red_Black_Tree.h"

int main() {
    RedBlackTree tree;

    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);
    tree.insert(12);
    tree.insert(18);

    tree.printTree();

    if (tree.search(12))
        std::cout << "12 exists in the tree\n";

    tree.searchAndPrint(12);   // 12 found. Color: RED, parent = 15 (left child)

    tree.remove(5);
    tree.printTree();

    return 0;
}
```

---

## API Reference

All public methods belong to the `RedBlackTree` class.

| Method | Returns | Description |
|---|---|---|
| `insert(int val)` | `void` | Inserts `val` and rebalances the tree. Duplicates go to the right subtree. |
| `remove(int val)` | `void` | Deletes the first node matching `val`. Prints a message if it is not found. |
| `search(int val) const` | `bool` | Returns `true` if `val` exists in the tree. Prints nothing. |
| `searchAndPrint(int val) const` | `void` | Prints whether `val` was found, along with its color and parent. |
| `printTree()` | `void` | Prints the tree sideways (right subtree on top, root at the left). |

> **Note:** `search` only returns a result. To see output on screen, use its return value in an `if` statement, or call `searchAndPrint`.

### Complexity

| Operation | Time |
|---|---|
| Insert | O(log n) |
| Delete | O(log n) |
| Search | O(log n) |
| Print | O(n) |

Space used by the tree is O(n).

---

## Example Output

Building a tree from `10, 5, 15, 3, 7, 12, 18` and calling `printTree()`:

```
          18(RED)

     15(BLACK)

          12(RED)

10(BLACK)

          7(RED)

     5(BLACK)

          3(RED)
```

The diagram is rotated 90 degrees: the **root is on the left**, each level is indented further to the right, **right children appear above** their parent, and **left children appear below**.

After `remove(5)`:

```
          18(RED)

     15(BLACK)

          12(RED)

10(BLACK)

     7(BLACK)

          3(RED)
```

---

## Implementation Notes

- **Node** stores `data`, `color`, and pointers to `left`, `right`, and `parent`. Its constructor is private, and `RedBlackTree` is declared a `friend`, so only the tree can create nodes.
- New nodes are always inserted **red**, then `fixInsert` repairs any violation.
- **Rotations** (`leftRotate`, `rightRotate`) run in O(1) and preserve the in-order ordering of the tree.
- **Deletion** uses the `transplant` helper and replaces a node with two children by its in-order successor (the minimum of the right subtree).
- Empty children (`nullptr`) are treated as black.

---

## Known Limitations

This project is meant for learning and experimentation. Before using it in production, be aware of the following:

- **Delete rebalancing gap:** `deleteNode` only calls `fixDelete` when the replacement node `x` is not `nullptr`. Deleting a **black node that has no children** skips the repair step and can leave the tree violating the black-height rule. The fix is to pass the parent of `x` into `fixDelete` and treat `nullptr` as black.
- **No destructor:** nodes are not freed when the tree goes out of scope, which causes a memory leak at program exit. Add a `~RedBlackTree()` that deletes all nodes recursively.
- **Copying:** copy construction and assignment are not disabled, so copying a tree would share nodes. Mark them `= delete` or implement deep copy.
- **Integers only:** keys are `int`. Making the classes templates would support other types.
- **Duplicates:** equal values are allowed and go to the right, and `remove` deletes only the first match found.
- **Duplicate print helper:** there is only one print style (sideways). A level-by-level view is not implemented.

---

## Roadmap

- [ ] Fix `fixDelete` for black leaf deletion
- [ ] Add a destructor and disable copying
- [ ] Add an `isValid()` function to verify the Red-Black properties
- [ ] Add in-order, pre-order, post-order, and level-order traversals
- [ ] Convert to a template (`RedBlackTree<T>`)
- [ ] Add unit tests

---

## Author

**Kareem Ahmed**
