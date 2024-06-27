#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_setRectangleButton_clicked();
    void on_cutCellButton_clicked();
    void on_restoreCellButton_clicked();

private:
    Ui::MainWindow *ui;
    int piecesCount;
    int x1, y1, x2, y2;
    void updatePiecesCount();
    void dfs(int row, int col, std::vector<std::vector<bool>> &visited);
    int countPieces();
};

#endif // MAINWINDOW_H
