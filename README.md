# **Scheduler Simulator with Gantt Chart Visualization**

This project implements a scheduler simulator using **C++** for process scheduling and **Python** for Gantt chart visualization. It supports 2 scheduling algorithms such as **First-Come-First-Served (FCFS)** and **Round Robin (RR)**.

---

## **Features**
- **Scheduling Algorithms**:
  - First-Come-First-Served (FCFS)
  - Round Robin (RR) with configurable time quantum
- **Gantt Chart**:
  - Generates a `gantt_chart.csv` file with process scheduling data.
  - Visualizes the Gantt chart using Python's `matplotlib`.

---

## **Setup Instructions**

### Prerequisites
1. **C++ Compiler**: Install `g++`.
   - **Ubuntu/Debian**:
     ```bash
     sudo apt update && sudo apt install g++
     ```
   - **macOS**:
     ```bash
     xcode-select --install
     ```
   - **Windows**: Install [MinGW](https://www.mingw-w64.org/).

2. **Python Environment**:
   - Install Python (version 3.7 or higher).
   - Install `matplotlib`:
     ```bash
     pip install matplotlib
     ```

---

## **How to Run**

### 1. Compile and Run the C++ Program
1. Navigate to the project folder:
   ```bash
   cd scheduler_simulator
   ```
2. Compile the C++ program:
   ```bash
   g++ -std=c++11 -o scheduler_simulator main.cpp
   ```
3. Run the program:
   ```bash
   ./scheduler_simulator
   ```
4. Input the number of processes, their attributes (arrival time, burst time, and priority), and select the scheduling algorithm.
5. The program will generate a `gantt_chart.csv` file with scheduling data.

---

### 2. Visualize the Gantt Chart
1. Run the Python script to visualize the Gantt chart:
   ```bash
   python3 visualize_gantt.py
   ```
2. The Gantt chart will be displayed in a pop-up window.

---