//Архипов Роман, группа 6, задача о листе бумаги
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <vector>
#include <algorithm>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , piecesCount(1)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_setRectangleButton_clicked()
{
    x1 = ui->x1Input->text().toInt();
    y1 = ui->y1Input->text().toInt();
    x2 = ui->x2Input->text().toInt();
    y2 = ui->y2Input->text().toInt();

    if (x1 > x2) std::swap(x1, x2);
    if (y1 > y2) std::swap(y1, y2);

    int rows = y2 - y1 + 1;
    int cols = x2 - x1 + 1;

    ui->tableWidget->setRowCount(rows);
    ui->tableWidget->setColumnCount(cols);

    QStringList rowHeaders;
    for (int i = y1; i <= y2; ++i)
        rowHeaders << QString::number(i);
    ui->tableWidget->setVerticalHeaderLabels(rowHeaders);

    QStringList columnHeaders;
    for (int i = x1; i <= x2; ++i)
        columnHeaders << QString::number(i);
    ui->tableWidget->setHorizontalHeaderLabels(columnHeaders);

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            ui->tableWidget->setItem(i, j, new QTableWidgetItem());
            ui->tableWidget->item(i, j)->setBackground(Qt::green);
        }
    }

    // Установить размер ячеек
    int tableWidth = ui->tableWidget->width();
    int tableHeight = ui->tableWidget->height();
    int cellWidth = tableWidth / (cols + 1);
    int cellHeight = tableHeight / (rows + 1);

    for (int i = 0; i < cols; ++i) {
        ui->tableWidget->setColumnWidth(i, cellWidth);
    }
    for (int i = 0; i < rows; ++i) {
        ui->tableWidget->setRowHeight(i, cellHeight);
    }

    piecesCount = 1;
    updatePiecesCount();
}

void MainWindow::on_cutCellButton_clicked()
{
    int x = ui->xInput->text().toInt();
    int y = ui->yInput->text().toInt();

    int row = y - y1;
    int col = x - x1;

    if (row >= 0 && row < ui->tableWidget->rowCount() && col >= 0 && col < ui->tableWidget->columnCount())
    {
        ui->tableWidget->item(row, col)->setBackground(Qt::red);

        piecesCount = countPieces();
        updatePiecesCount();
    }
    else
    {
        QMessageBox::warning(this, "Invalid Input", "Что-то тут не то");
    }
}

void MainWindow::on_restoreCellButton_clicked()
{
    int x = ui->x0Input->text().toInt();
    int y = ui->y0Input->text().toInt();

    int row = y - y1;
    int col = x - x1;

    if (row >= 0 && row < ui->tableWidget->rowCount() && col >= 0 && col < ui->tableWidget->columnCount())
    {
        ui->tableWidget->item(row, col)->setBackground(Qt::green);

        piecesCount = countPieces();
        updatePiecesCount();
    }
    else
    {
        QMessageBox::warning(this, "Invalid Input", "Что-то тут не то");
    }
}

void MainWindow::updatePiecesCount()
{
    ui->piecesCountLabel->setText(QString("Кусков: %1").arg(piecesCount));
}

void MainWindow::dfs(int row, int col, std::vector<std::vector<bool>> &visited)
{
    static const std::vector<int> dr = {-1, 1, 0, 0};
    static const std::vector<int> dc = {0, 0, -1, 1};

    visited[row][col] = true;

    for (int i = 0; i < 4; ++i)
    {
        int nr = row + dr[i];
        int nc = col + dc[i];

        if (nr >= 0 && nr < ui->tableWidget->rowCount() && nc >= 0 && nc < ui->tableWidget->columnCount())
        {
            if (!visited[nr][nc] && ui->tableWidget->item(nr, nc)->background() != Qt::red)
            {
                dfs(nr, nc, visited);
            }
        }
    }
}

int MainWindow::countPieces()
{
    std::vector<std::vector<bool>> visited(ui->tableWidget->rowCount(), std::vector<bool>(ui->tableWidget->columnCount(), false));
    int count = 0;

    for (int i = 0; i < ui->tableWidget->rowCount(); ++i)
    {
        for (int j = 0; j < ui->tableWidget->columnCount(); ++j)
        {
            if (!visited[i][j] && ui->tableWidget->item(i, j)->background() != Qt::red)
            {
                dfs(i, j, visited);
                ++count;
            }
        }
    }

    return count;
}
