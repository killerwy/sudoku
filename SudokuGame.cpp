// SudokuGame.cpp - 数独游戏Qt界面实现
#include "SudokuGame.h"
#include <QRegularExpressionValidator>

SudokuGame::SudokuGame(QWidget *parent):QMainWindow(parent)
{
    setWindowTitle("数独游戏");
    resize(600,600);

    // 创建中央部件和主布局
    QWidget *centralWidget=new QWidget(this);
    QVBoxLayout *mainLayout=new QVBoxLayout(centralWidget);

    // 创建数独网格
    gridLayout=new QGridLayout();
    createUI();
    mainLayout->addLayout(gridLayout);

    // 创建按钮行
    QHBoxLayout *buttonLayout=new QHBoxLayout();

    QPushButton *solveButton=new QPushButton("求解",this);
    QPushButton *clearButton=new QPushButton("清空",this);
    QPushButton *easyButton=new QPushButton("简单题目",this);
    QPushButton *mediumButton=new QPushButton("中等题目",this);
    QPushButton *hardButton=new QPushButton("困难题目",this);
    QPushButton *checkButton=new QPushButton("检查答案",this);

    buttonLayout->addWidget(solveButton);
    buttonLayout->addWidget(clearButton);
    buttonLayout->addWidget(easyButton);
    buttonLayout->addWidget(mediumButton);
    buttonLayout->addWidget(hardButton);
    buttonLayout->addWidget(checkButton);

    mainLayout->addLayout(buttonLayout);

    // 连接信号和槽
    connect(solveButton,&QPushButton::clicked,this,&SudokuGame::solvePuzzle);
    connect(clearButton,&QPushButton::clicked,this,&SudokuGame::clearBoard);
    connect(easyButton,&QPushButton::clicked,this,&SudokuGame::generateEasy);
    connect(mediumButton,&QPushButton::clicked,this,&SudokuGame::generateMedium);
    connect(hardButton,&QPushButton::clicked,this,&SudokuGame::generateHard);
    connect(checkButton,&QPushButton::clicked,this,&SudokuGame::checkSolution);

    setCentralWidget(centralWidget);
}

void SudokuGame::createUI()
{
    // 创建9x9的输入框网格
    for(int row=0;row<9;row++)
    {
        for(int col=0;col<9;col++)
        {
            cells[row][col]=new QLineEdit(this);
            cells[row][col]->setAlignment(Qt::AlignCenter);
            cells[row][col]->setMaxLength(1);
            cells[row][col]->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

            // 设置验证器，只允许输入1-9
            QRegularExpressionValidator*validator=new QRegularExpressionValidator(QRegularExpression("[1-9]"),this);
            cells[row][col]->setValidator(validator);

            //设置四个小矩阵的背景
            cells[row][col]->setStyleSheet("font-size: 20px;");
            if(!((col>=3 and col<=5) and (row>=3 and row<=5)))
                if((col>=3 and col<=5) or (row>=3 and row<=5))
                {
                    QString currentStyle=cells[row][col]->styleSheet();
                    cells[row][col]->setStyleSheet(currentStyle+"font-size:20px;background-color:#555555;color:white;");
                }

            gridLayout->addWidget(cells[row][col],row,col);
        }
    }
}

void SudokuGame::updateUI()
{
    int currentBoard[9][9];
    solver.getBoard(currentBoard);

    for(int row=0;row<9;row++)
    {
        for(int col=0;col<9;col++)
        {
            QString currentStyle=cells[row][col]->styleSheet();
            cells[row][col]->setStyleSheet(currentStyle+"color:black;");

            if(!((col>=3 and col<=5) and (row>=3 and row<=5)))
                if((col>=3 and col<=5) or (row>=3 and row<=5))
                {
                    QString currentStyle=cells[row][col]->styleSheet();
                    cells[row][col]->setStyleSheet(currentStyle+"background-color:#555555;color:white;");
                }

            cells[row][col]->setReadOnly(true);//设置只读模式
            if(currentBoard[row][col]!=0)
            {
                cells[row][col]->setText(QString::number(currentBoard[row][col]));
            }
            else
            {
                cells[row][col]->clear();
                cells[row][col]->setReadOnly(false);//恢复编辑模式
                QString currentStyle=cells[row][col]->styleSheet();
                cells[row][col]->setStyleSheet(currentStyle+"color:red;");
            }
        }
    }
}

bool SudokuGame::validateInput()
{
    int inputBoard[9][9];

    for(int row=0;row<9;row++)
    {
        for(int col=0;col<9;col++)
        {
            QString text=cells[row][col]->text();
            if(text.isEmpty())
            {
                inputBoard[row][col]=0;
            }
            else
            {
                inputBoard[row][col]=text.toInt();
            }
        }
    }

    solver.initialize(inputBoard);
    return solver.isValidBoard();
}

void SudokuGame::solvePuzzle()
{
    if(!validateInput())
    {
        QMessageBox::warning(this,"错误","当前输入的数独无效，请检查！");
        return;
    }

    if(solver.solve())
    {
        updateUI();
        QMessageBox::information(this,"成功","数独已解决！");
    }
    else
    {
        QMessageBox::warning(this,"错误","此数独无解！");
    }
}

void SudokuGame::clearBoard()
{
    for(int row=0;row<9;row++)
    {
        for(int col=0;col<9;col++)
        {
            cells[row][col]->clear();
            cells[row][col]->setReadOnly(false);//恢复编辑模式
        }
    }

    int emptyBoard[9][9]={0};
    solver.initialize(emptyBoard);
}

void SudokuGame::generateEasy()
{
    solver.generatePuzzle(1);
    updateUI();
}

void SudokuGame::generateMedium()
{
    solver.generatePuzzle(2);
    updateUI();
}

void SudokuGame::generateHard()
{
    solver.generatePuzzle(3);
    updateUI();
}

void SudokuGame::checkSolution()
{
    if(!validateInput())
    {
        QMessageBox::warning(this,"错误","当前输入的数独无效，请检查！");
        return;
    }

    int inputBoard[9][9];
    solver.getBoard(inputBoard);

    SudokuSolver tempSolver;
    tempSolver.initialize(inputBoard);

    if(tempSolver.solve())
    {
        QMessageBox::information(this,"正确","恭喜！您的解答是正确的。");
    }
    else
    {
        QMessageBox::warning(this,"错误","您的解答有误，请检查！");
    }
}
