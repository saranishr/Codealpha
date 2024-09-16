
#include <QApplication>
#include <QWidget>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <vector>

// Sudoku solver class
class SudokuSolver {
public:
    bool solve(std::vector<std::vector<int>>& board);
private:
    bool isValid(const std::vector<std::vector<int>>& board, int row, int col, int num);
    bool findEmptyLocation(const std::vector<std::vector<int>>& board, int &row, int &col);
};

// SudokuSolver implementation
bool SudokuSolver::isValid(const std::vector<std::vector<int>>& board, int row, int col, int num) {
    for (int x = 0; x < 9; x++)
        if (board[row][x] == num || board[x][col] == num)
            return false;

    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i + startRow][j + startCol] == num)
                return false;

    return true;
}

bool SudokuSolver::findEmptyLocation(const std::vector<std::vector<int>>& board, int &row, int &col) {
    for (row = 0; row < 9; row++)
        for (col = 0; col < 9; col++)
            if (board[row][col] == 0)
                return true;
    return false;
}

bool SudokuSolver::solve(std::vector<std::vector<int>>& board) {
    int row, col;
    if (!findEmptyLocation(board, row, col))
        return true;

    for (int num = 1; num <= 9; num++) {
        if (isValid(board, row, col, num)) {
            board[row][col] = num;
            if (solve(board))
                return true;
            board[row][col] = 0; // Undo assignment (backtrack)
        }
    }
    return false;
}

// MainWindow class
class MainWindow : public QWidget {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void solvePuzzle();
    void clearBoard();

private:
    QLineEdit* cells[9][9];
    SudokuSolver solver;
    std::vector<std::vector<int>> readBoard();
    void writeBoard(const std::vector<std::vector<int>>& board);
};

// MainWindow implementation
MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
    QGridLayout *gridLayout = new QGridLayout(this);
    setLayout(gridLayout);

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            cells[i][j] = new QLineEdit(this);
            cells[i][j]->setMaxLength(1);
            cells[i][j]->setAlignment(Qt::AlignCenter);
            cells[i][j]->setValidator(new QIntValidator(1, 9, this));
            gridLayout->addWidget(cells[i][j], i, j);
        }
    }

    QPushButton *solveButton = new QPushButton("Solve", this);
    QPushButton *clearButton = new QPushButton("Clear", this);
    gridLayout->addWidget(solveButton, 9, 0, 1, 5);
    gridLayout->addWidget(clearButton, 9, 5, 1, 4);

    connect(solveButton, &QPushButton::clicked, this, &MainWindow::solvePuzzle);
    connect(clearButton, &QPushButton::clicked, this, &MainWindow::clearBoard);
}

std::vector<std::vector<int>> MainWindow::readBoard() {
    std::vector<std::vector<int>> board(9, std::vector<int>(9, 0));
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            QString text = cells[i][j]->text();
            bool ok;
            int value = text.toInt(&ok);
            if (ok && value >= 1 && value <= 9) {
                board[i][j] = value;
            }
        }
    }
    return board;
}

void MainWindow::writeBoard(const std::vector<std::vector<int>>& board) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cells[i][j]->setText(board[i][j] == 0 ? "" : QString::number(board[i][j]));
        }
    }
}

void MainWindow::solvePuzzle() {
    std::vector<std::vector<int>> board = readBoard();
    if (solver.solve(board)) {
        writeBoard(board);
    } else {
        QMessageBox::information(this, "No Solution", "No solution exists for the given Sudoku puzzle.");
    }
}

void MainWindow::clearBoard() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cells[i][j]->clear();
        }
    }
}

// Main function
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow window;
    window.setWindowTitle("Sudoku Solver");
    window.resize(400, 400);
    window.show();
    return app.exec();
}
