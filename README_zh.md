# 数独

> 一款基于 Qt5/Qt6、C++ 开发的图形化数独桌面程序

[English](./README.md) | [中文](./README_zh.md)

![GitHub stars](https://img.shields.io/github/stars/killerwy/sudoku?style=for-the-badge&logo=github) 
![GitHub forks](https://img.shields.io/github/forks/killerwy/sudoku?style=for-the-badge&logo=github) 
![GitHub issues](https://img.shields.io/github/issues/killerwy/sudoku?style=for-the-badge&logo=github) 
![Last commit](https://img.shields.io/github/last-commit/killerwy/sudoku?style=for-the-badge&logo=github) 
![License](https://img.shields.io/badge/license-MIT-green?style=for-the-badge)
![C++](https://img.shields.io/badge/c++-%23F34B7D.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![Qt](https://img.shields.io/badge/Qt-%23217346.svg?style=for-the-badge&logo=Qt&logoColor=white)

## 📑 目录
- [项目简介](#-项目简介)
- [功能特性](#-功能特性)
- [技术栈](#-技术栈)
- [快速上手](#-快速上手)
- [使用说明](#-使用说明)
- [项目结构](#-项目结构)
- [开源协议](#-开源协议)

## 📝 项目简介
本项目是一套基于 C++ + Qt5/Qt6 开发、使用 CMake 构建的完整桌面端数独游戏。项目将界面层与数独算法求解层完全解耦：
1. 独立 `SudokuSolver` 算法模块，实现优化回溯求解、唯一解谜题生成、盘面合法性校验、解数量统计等功能；
2. Qt 图形界面提供交互式 9×9 数独面板，支持手动填数、一键求解、三种难度随机生成、答案校验；
3. 同时兼容 Qt5、Qt6 跨平台编译，可在 Windows、macOS、Linux 桌面系统运行。

## ✨ 功能特性
### 算法核心
1. 优化回溯求解器：优先选择候选数字最少的空格进行递归，大幅减少递归分支，提升求解速度；
2. 唯一解谜题生成：随机生成简单/中等/困难三种难度数独，自动校验保证谜题仅有唯一标准解；
3. 盘面合法性检测：校验当前填入数字是否符合数独规则（每行、每列、每个3×3九宫格内数字不重复）；
4. 多解统计：可统计当前盘面所有合法解的总数，内置提前终止限制，避免性能损耗；
5. 状态隔离设计：行、列、九宫格使用独立占用标记数组，计算候选数字时无需重复遍历盘面。

### Qt 游戏界面
1. 可视化9×9填数网格：采用单行输入框限制仅可输入1-9数字，通过正则表达式过滤非法输入；
2. 分区色差区分：中间3×3九宫格使用深灰色背景，直观区分九个小九宫内区域；
3. 功能操作按钮：求解 / 清空盘面 / 生成简单 / 生成中等 / 生成困难 / 校验答案；
4. 固定数字只读锁定：生成谜题自带的预置数字不可编辑，用户手动填入数字标红区分；
5. 弹窗消息反馈：盘面非法、无解、答案正确/错误等场景均弹出对应提示弹窗。

## 🔧 技术栈
- 编程语言：C++
- 图形框架：Qt

## ⚡ 快速上手
### 命令行编译
1. 克隆仓库
```bash
git clone https://github.com/killerwy/sudoku.git
cd sudoku
```

2. 编译构建
```bash
# Windows 平台
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
mingw32-make
./sudoku.exe

# Linux / macOS 平台
mkdir build && cd build
cmake ..
make -j4
./sudoku
```

### Qt Creator 编译运行
1. 下载本项目源码；
2. 打开 Qt Creator，导入项目根目录下的 `CMakeLists.txt`；
3. 选择 Qt5 或 Qt6 编译套件完成配置；
4. 点击运行按钮，一键编译并启动程序。

## 📖 使用说明
1. **生成谜题**
点击「简单 / 中等 / 困难」按钮，生成拥有唯一解的标准数独；自带固定数字锁定不可修改，空白格子可手动填数。
2. **手动填数**
点击任意空白格子，直接输入1-9数字；非数字输入会被输入校验器自动过滤。
3. **校验答案**
完整填完盘面后，点击「校验答案」，程序会判断你的填数是否与标准唯一解完全匹配。
4. **一键求解**
填入部分数字后，点击「求解」，程序自动补全剩余所有空格，输出标准完整解。
5. **清空盘面**
点击「清空」，清除所有数字，重置为空白数独盘面。

## 📁 项目结构
所有源码文件直接存放于项目根目录，结构如下：
```
sudoku/
├── CMakeLists.txt        # CMake 构建配置文件，兼容 Qt5/Qt6
├── main.cpp              # 程序入口，创建游戏主窗口
├── mainwindow.h          # 基础主窗口头文件
├── mainwindow.cpp        # 基础主窗口实现文件
├── mainwindow.ui         # Qt Designer 界面文件
├── SudokuGame.h          # Qt 游戏主窗口头文件，定义界面布局与槽函数
├── SudokuGame.cpp        # Qt 游戏主窗口逻辑实现
├── SudokuSolver.h        # 数独核心求解算法头文件
├── SudokuSolver.cpp      # 数独核心求解算法实现
├── README.md             # 英文项目文档
├── README_zh.md          # 中文项目文档
├── LICENSE               # MIT 开源协议文件
└── .gitignore            # Git 忽略配置文件
```

## 📜 开源协议
本项目基于 **MIT 开源协议** 开放，详细协议内容请查看 [LICENSE](LICENSE) 文件。

---
*本README由 [ReadmeBuddy](https://readmebuddy.com) 倾情生成 ❤️*
