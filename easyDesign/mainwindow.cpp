#include "mainwindow.h"
#include "easyui.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->resize(800,600);

    easyUI *e = new easyUI(this);
    e->init(200, 200, 0, 0, QString("test.jpg"));

    e->setButtonAction("scaled", true);
}

MainWindow::~MainWindow()
{

}
