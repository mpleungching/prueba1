#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , n0(0), n1(1), n2(2), n3(3), n4(4)
{
    ui->setupUi(this);
    initializeGraph();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::initializeGraph() {
    intGraph.addEdge(&n0, &n1);
    intGraph.addEdge(&n0, &n4);
    intGraph.addEdge(&n1, &n2);
    intGraph.addEdge(&n1, &n3);
    intGraph.addEdge(&n1, &n4);
    intGraph.addEdge(&n2, &n3);
    intGraph.addEdge(&n3, &n4);
}

void MainWindow::on_dfsButton_clicked() {
    std::cout << "DFS for int graph: ";
    intGraph.DFS(&n0);
    std::cout << std::endl;
}

void MainWindow::on_bfsButton_clicked() {
    std::cout << "BFS for int graph: ";
    intGraph.BFS(&n0);
    std::cout << std::endl;
}
