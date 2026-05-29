// SudokuSolver.cpp - 优化后的数独求解器实现
#include <cstdlib>
#include "SudokuSolver.h"

SudokuSolver::SudokuSolver()
{
    // 初始化棋盘为全0
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            board[i][j]=0;
        }
    }
    initializeUsage();
}

void SudokuSolver::initializeUsage()
{
    // 初始化使用记录
    for(int i=0;i<9;i++)
    {
        for(int num=1;num<=9;num++)
        {
            rowUsed[i][num]=false;
            colUsed[i][num]=false;
            boxUsed[i][num]=false;
        }
    }
}

void SudokuSolver::setNumberUsage(int row,int col,int num,bool used)
{
    rowUsed[row][num]=used;
    colUsed[col][num]=used;
    boxUsed[(row/3)*3+col/3][num]=used;
}

void SudokuSolver::initialize(int initialBoard[9][9])
{
    initializeUsage();

    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            board[i][j]=initialBoard[i][j];
            if (board[i][j]!=0)
            {
                setNumberUsage(i,j,board[i][j],true);
            }
        }
    }
}

void SudokuSolver::getBoard(int currentBoard[9][9])
{
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            currentBoard[i][j]=board[i][j];
        }
    }
}

bool SudokuSolver::findBestEmptyCell(int &row,int &col)
{
    int minCandidates=10; // 初始化为大于最大可能值(9)
    bool found=false;

    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            if(board[i][j]==0)
            {
                int count=getCandidateCount(i,j);
                if(count<minCandidates)
                {
                    minCandidates=count;
                    row=i;
                    col=j;
                    found=true;

                    // 如果找到只有一个候选数的单元格，立即返回
                    if (minCandidates==1)
                    {
                        return true;
                    }
                }
            }
        }
    }

    return found;
}

int SudokuSolver::getCandidateCount(int row,int col)
{
    int count=0;
    bool candidates[10]={false};
    getCandidates(row,col,candidates);

    for(int num=1;num<=9;num++)
    {
        if(candidates[num]) count++;
    }

    return count;
}

void SudokuSolver::getCandidates(int row,int col,bool candidates[10])
{
    // 初始时所有数字都是候选
    for(int num=1;num<=9;num++)
    {
        candidates[num]=true;
    }

    // 检查行、列、小格子中已使用的数字
    for(int num=1;num<=9;num++)
    {
        if (rowUsed[row][num] || colUsed[col][num] || boxUsed[(row/3)*3+col/3][num])
        {
            candidates[num]=false;
        }
    }
}

bool SudokuSolver::solve()
{
    int row,col;

    // 如果没有空单元格，问题已解决
    if(!findBestEmptyCell(row,col)) return true;

    // 获取候选数字
    bool candidates[10]={false};
    getCandidates(row,col,candidates);

    // 尝试所有候选数字
    for(int num=1;num<=9;num++)
    {
        if(candidates[num])
        {
            // 尝试填入数字
            board[row][col]=num;
            setNumberUsage(row,col,num,true);

            // 递归解决剩下的棋盘
            if(solve()) return true;

            // 如果失败，回溯
            board[row][col]=0;
            setNumberUsage(row,col,num,false);
        }
    }

    // 触发回溯
    return false;
}

bool SudokuSolver::isValidBoard()
{
    // 临时保存原始使用记录
    bool tempRowUsed[9][10]={false};
    bool tempColUsed[9][10]={false};
    bool tempBoxUsed[9][10]={false};

    // 检查每个数字是否符合规则
    for(int row=0;row<9;row++)
    {
        for(int col=0;col<9;col++)
        {
            int num=board[row][col];
            if(num!=0)
            {
                int box=(row/3)*3+col/3;

                // 如果数字在行、列或小格子中已经出现过，则无效
                if(tempRowUsed[row][num] || tempColUsed[col][num] || tempBoxUsed[box][num])
                {
                    return false;
                }

                // 标记数字已使用
                tempRowUsed[row][num]=true;
                tempColUsed[col][num]=true;
                tempBoxUsed[box][num]=true;
            }
        }
    }

    return true;
}

bool SudokuSolver::countSolutions(int &solutionCount,int limit)
{
    solutionCount=0;
    countSolutionsRecursive(solutionCount,limit);
    return solutionCount>0;
}

void SudokuSolver::countSolutionsRecursive(int &solutionCount,int limit)
{
    // 如果已经找到足够多的解，提前终止
    if(solutionCount>=limit)
    {
        return;
    }

    int row, col;

    // 如果没有空单元格，找到一个解
    if(!findBestEmptyCell(row,col))
    {
        solutionCount++;
        return;
    }

    // 获取候选数字
    bool candidates[10]={false};
    getCandidates(row,col,candidates);

    // 尝试所有候选数字
    for(int num=1;num<=9 && solutionCount<limit;num++)
    {
        if(candidates[num])
        {
            // 尝试填入数字
            board[row][col]=num;
            setNumberUsage(row,col,num,true);

            // 递归寻找解
            countSolutionsRecursive(solutionCount,limit);

            // 回溯
            board[row][col]=0;
            setNumberUsage(row,col,num,false);
        }
    }
}

void SudokuSolver::generatePuzzle(int difficulty)
{
    // 清空棋盘
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            board[i][j]=0;
        }
    }
    initializeUsage();

    // 生成一个完整解
    solve();

    // 根据难度移除一定数量的数字
    int cellsToRemove;
    switch(difficulty)
    {
        case 1:cellsToRemove=20;break; // 简单
        case 2:cellsToRemove=30;break; // 中等
        case 3:cellsToRemove=50;break; // 困难
        default:cellsToRemove=20;break;
    }

    // 随机移除数字，但要确保解的唯一性
    int removed=0;
    while(removed<cellsToRemove)
    {
        int row=rand()%9;
        int col=rand()%9;

        if(board[row][col]!=0)
        {
            int temp=board[row][col];
            board[row][col]=0;

            // 检查解的唯一性
            SudokuSolver tempSolver;
            tempSolver.initialize(board);

            int solutions=0;
            if(tempSolver.countSolutions(solutions,2) && solutions==1)
            {
                setNumberUsage(row,col,temp,false);
                removed++;
            }
            else
            {
                board[row][col]=temp;
            }
        }
    }
}
