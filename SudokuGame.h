// SudokuGame.h - 数独游戏Qt界面头文件
#ifndef SUDOKUGAME_H
#define SUDOKUGAME_H

#include <QMainWindow>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include "SudokuSolver.h"

class SudokuGame:public QMainWindow
{
    Q_OBJECT

private:
    SudokuSolver solver; // 数独求解器实例
    QLineEdit *cells[9][9]; // 9x9的输入框网格
    QGridLayout *gridLayout; // 网格布局

    // 创建UI组件
    void createUI();

    // 更新UI显示
    void updateUI();

    // 验证输入
    bool validateInput();

private slots:
    // 槽函数
    void solvePuzzle();
    void clearBoard();
    void generateEasy();
    void generateMedium();
    void generateHard();
    void checkSolution();

public:
    SudokuGame(QWidget *parent=nullptr);
};

#endif // SUDOKUGAME_H
