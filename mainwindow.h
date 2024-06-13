#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "graph.h"
#include "node.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_dfsButton_clicked();
    void on_bfsButton_clicked();

private:
    Ui::MainWindow *ui;
    Graph<int> intGraph;
    Node<int> n0, n1, n2, n3, n4;
    void initializeGraph();
};

#endif // MAINWINDOW_H
