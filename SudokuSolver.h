// SudokuSolver.h - 优化后的数独求解器头文件
#ifndef SUDOKUSOLVER_H
#define SUDOKUSOLVER_H

class SudokuSolver
{
private:
    int board[9][9]; // 9x9数独棋盘

    // 行、列、小格子的数字使用情况记录
    bool rowUsed[9][10];    // rowUsed[i][num] 表示第i行是否已使用num
    bool colUsed[9][10];    // colUsed[j][num] 表示第j列是否已使用num
    bool boxUsed[9][10];    // boxUsed[k][num] 表示第k个小格子是否已使用num

    // 初始化使用记录
    void initializeUsage();

    // 检查并设置数字使用状态
    void setNumberUsage(int row,int col,int num,bool used);

    // 找到最优的空单元格（最少候选数的单元格）
    bool findBestEmptyCell(int &row,int &col);

    // 获取单元格的候选数字数量
    int getCandidateCount(int row,int col);

    // 获取单元格的候选数字
    void getCandidates(int row,int col,bool candidates[10]);

    // 递归计算解决方案数量
    void countSolutionsRecursive(int &solutionCount,int limit);

public:
    // 构造函数
    SudokuSolver();

    // 从二维数组初始化棋盘
    void initialize(int initialBoard[9][9]);

    // 获取当前棋盘状态
    void getBoard(int currentBoard[9][9]);

    // 解决数独问题（优化后的回溯法）
    bool solve();

    // 检查当前棋盘是否有效
    bool isValidBoard();

    // 生成随机数独题目
    void generatePuzzle(int difficulty);

    // 计算当前棋盘的可能解数量（最多计算到limit个）
    bool countSolutions(int &solutionCount,int limit=2);
};

#endif // SUDOKUSOLVER_H
