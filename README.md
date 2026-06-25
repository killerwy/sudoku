# Sudoku

> A GUI-based Sudoku desktop application developed with Qt5/Qt6 and C++

[English](./README.md) | [中文](./README_zh.md)

![GitHub stars](https://img.shields.io/github/stars/killerwy/sudoku?style=for-the-badge&logo=github) 
![GitHub forks](https://img.shields.io/github/forks/killerwy/sudoku?style=for-the-badge&logo=github) 
![GitHub issues](https://img.shields.io/github/issues/killerwy/sudoku?style=for-the-badge&logo=github) 
![Last commit](https://img.shields.io/github/last-commit/killerwy/sudoku?style=for-the-badge&logo=github) 
![License](https://img.shields.io/badge/license-MIT-green?style=for-the-badge)
![C++](https://img.shields.io/badge/c++-%23F34B7D.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![Qt](https://img.shields.io/badge/Qt-%23217346.svg?style=for-the-badge&logo=Qt&logoColor=white)


## 📑 Table of Contents
- [Description](#-description)
- [Features](#-features)
- [Tech Stack](#-tech-stack)
- [Quick Start](#-quick-start)
- [Usage Guide](#-usage-guide)
- [Project Structure](#-project-structure)
- [License](#-license)

## 📝 Description
This is a complete desktop Sudoku game developed based on C++ and Qt5/Qt6, built with CMake. The project separates the UI layer and Sudoku algorithm solving layer:
1. Independent `SudokuSolver` module implements optimized backtracking Sudoku solving, unique puzzle generation, validity detection and solution counting functions;
2. Qt GUI provides an interactive 9×9 Sudoku panel, supporting manual input, one-click solving, random puzzle generation of three difficulties, and answer checking;
3. Compatible with Qt5 and Qt6 cross-platform compilation, supports Windows, macOS, Linux desktop systems.

## ✨ Features
### Algorithm Core
1. Optimized backtracking solver: Select empty cells with the fewest candidate numbers first to drastically reduce recursion branches and improve solving speed;
2. Unique puzzle generation: Randomly generate easy/medium/hard Sudoku puzzles, automatically verify single solution to ensure standard valid Sudoku;
3. Board validity detection: Check whether the current filled number conforms to Sudoku rules (no duplicates in rows, columns, 3×3 subgrids);
4. Multi-solution counting: Support counting the number of all valid solutions of the current board, with early termination limit to avoid performance loss;
5. State isolation: Independent usage mark arrays for rows, columns and subgrids to avoid repeated traversal when calculating candidate numbers.

### Qt Game UI
1. Visual 9×9 input grid: QLineEdit single-digit input box, only numbers 1-9 are allowed through regular expression verification;
2. Partition color distinction: Middle 3×3 subgrid uses dark gray background to visually distinguish 9 sub-boxes;
3. Functional operation buttons: Solve / Clear board / Generate Easy / Generate Medium / Generate Hard / Check Answer;
4. Read-only fixed number display: The preset numbers of generated puzzles are locked and cannot be edited, user input numbers are marked red;
5. Pop-up prompt feedback: Give warning/information pop-ups for invalid boards, unsolvable puzzles, correct/wrong answers.

## 🔧 Tech Stack
- Programming Languages: C++
- Framework: Qt

## ⚡ Quick Start
### Command
1. Clone Repository

```bash
git clone https://github.com/killerwy/sudoku.git
cd sudoku
```

2. Compile & Build

```bash
# Windows
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
mingw32-make
./sudoku.exe

# Linux/macOS
mkdir build && cd build
cmake ..
make -j4
./sudoku
```

### Qt Creator
1. Download this Repository.
2. Open Qt Creator, import the root directory `CMakeLists.txt`;
3. Select Qt5 or Qt6 Kit for configuration;
4. Click Run to compile and launch the program directly.


## 📖 Usage Guide
1. **Generate Puzzle**
   Click `Easy / Medium / Hard` to generate a standard Sudoku with unique solution; fixed numbers are locked, blank cells can be filled manually.
2. **Manual Input**
   Click any blank grid, input numbers 1-9 directly; non-numeric input will be automatically filtered by validator.
3. **Check Answer**
   After filling the whole board, click `Check Answer`; the program will judge whether your filling matches the unique solution.
4. **One-click Solve**
   After filling partial numbers, click `Solve` to automatically fill all remaining cells with the standard solution.
5. **Clear Board**
   Click `Clear` to erase all numbers and reset the empty Sudoku board.

## 📁 Project Structure
All source files are placed directly in the project root directory:
```
sudoku/
├── CMakeLists.txt        # CMake build configuration file, compatible Qt5/Qt6
├── main.cpp              # Program entry, create SudokuGame main window
├── mainwindow.h          # MainWindow header
├── mainwindow.cpp        # MainWindow implementation
├── mainwindow.ui         # Qt Designer UI file for MainWindow
├── SudokuGame.h          # Qt main game window header, UI layout & slot declaration
├── SudokuGame.cpp        # Qt main game window implementation
├── SudokuSolver.h        # Sudoku core algorithm solver header
├── SudokuSolver.cpp      # Sudoku core algorithm solver implementation
├── README.md             # English project documentation
├── README_zh.md          # Chinese project documentation
├── LICENSE               # MIT open source license
└── .gitignore            # Git ignore file
```

## 📜 License
This project is licensed under the **MIT License** - see the [LICENSE](LICENSE) file for details.

---
*This README was generated with ❤️ by [ReadmeBuddy](https://readmebuddy.com)*
