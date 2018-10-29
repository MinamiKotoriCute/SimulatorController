#include "mainwindow.h"

#include "mylabel.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setCentralWidget(new MyLabel);
}

MainWindow::~MainWindow()
{

}
