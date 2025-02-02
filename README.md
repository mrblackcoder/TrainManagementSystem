# Train Loading Management System

**Authors:**

- **Mehmet Taha Boynikoğlu**

**Department:** Software Engineering  
**Instructor:** Ertuğrul İslamoğlu  
**Report Date:** 08/01/2025

---

## Table of Contents

1. [Introduction](#introduction)
2. [Purpose and Scope](#purpose-and-scope)
3. [Features](#features)
4. [System Overview](#system-overview)
5. [Project Objectives](#project-objectives)
6. [Implementation Details](#implementation-details)
7. [Testing and Validation](#testing-and-validation)
8. [Future Extensions](#future-extensions)
9. [References](#references)

---

## Introduction

The **Train Loading Management System** is a programming project designed to simulate a real-world cargo train station. It focuses on efficient handling of boxes and wagons using **doubly linked list structures**, adhering to rules like stacking constraints, weight limits, and dynamic wagon management. This project provides a hands-on opportunity to apply concepts in **data structures**, **dynamic memory management**, **file operations**, and **object-oriented programming** using the C programming language.

---

## Purpose and Scope

This project aims to:

- Implement a train management system with realistic constraints.
- Enhance skills in **C programming** by utilizing data structures like doubly linked lists.
- Focus on modular design, efficient memory management, and error handling.

### Key Features:

- Dynamic handling of wagons and materials.
- Rules for stacking and weight capacity enforcement.
- File operations for saving and loading train states.
- Menu-driven user interface for seamless interaction.

---

## Features

- **Data Structures:** Efficient management of wagons and materials using **doubly linked lists**.
- **Memory Management:** Use of `malloc` and `free` to ensure safe and efficient memory allocation.
- **Stacking Rules:**
  - Small boxes can only be placed on small.
  - Medium boxes can support both small and medium.
  - Large boxes can support all types.
- **Capacity Constraints:** Each wagon can hold a maximum of **1000 kg**.
- **File I/O:** Save and reload train states for data persistence.
- **User Interaction:** Intuitive menu options for loading, unloading, and displaying train status.

---

## System Overview

### Materials (Boxes)

- **Large Box (Steel):** 200 kg
- **Medium Box (Aluminium):** 150 kg
- **Small Box (Wood):** 100 kg

### Wagons

- Maximum capacity: **1000 kg**
- Dynamically managed using **doubly linked lists**.
- Empty wagons are removed, and IDs are renumbered dynamically.

### Train

The train is represented by a `Train` struct, containing:

- `train_id`: A unique identifier for the train.
- `first_wagon`: A pointer to the first wagon.
- `wagon_count`: Total number of wagons in the train.

---

## Project Objectives

### Core Objectives:

1. **Implement Advanced Data Structures:**
   - Use doubly linked lists for managing wagons and materials.
   - Develop efficient insertion, removal, and traversal operations.
2. **Master Dynamic Memory Management:**
   - Prevent memory leaks with robust pointer handling.
3. **File Operations:**
   - Save and load train states in structured file formats.
4. **Modular Design:**
   - Divide the system into `.c` and `.h` files for maintainability.
5. **Resource Management Algorithms:**
   - Dynamically add/remove wagons and enforce stacking rules.

---

## Implementation Details

### File Organization

The project is organized into:

- `.c` files for implementation logic.
- `.h` files for header definitions.

### Constraints

- **Stacking Rules:**
  - SMALL -> Supports only SMALL.
  - MEDIUM -> Supports SMALL and MEDIUM.
  - LARGE -> Supports all types.
- **Capacity Rule:** Ensure `current_weight + box_weight <= max_weight` (1000 kg).

---

## Testing and Validation

1. **Unit Tests:**
   - Validate stacking rules (e.g., LARGE cannot be placed on MEDIUM).
   - Confirm capacity constraints (e.g., 1000 kg limit).
2. **Integration Tests:**
   - Ensure proper loading and unloading across wagons.
3. **File I/O Tests:**
   - Verify train state persistence through save and reload operations.
4. **User Acceptance Tests:**
   - Ensure an intuitive and seamless user interface.

---

## Future Extensions

- **Graphical Visualization:** Create a graphical interface to display wagons and boxes visually.
- **Concurrent Operations:** Implement thread-safe loading/unloading.
- **Enhanced Material Tracking:** Add support for dimensional constraints or advanced scheduling algorithms.

---

## References

1. Kernighan, B.W., & Ritchie, D.M. (1988). _The C Programming Language_ (2nd ed.).

---

This README provides an overview of the **Train Loading Management System**, focusing on its features, implementation details, and future prospects. The project serves as a comprehensive simulation, bridging theoretical learning with practical application in **C programming**.
