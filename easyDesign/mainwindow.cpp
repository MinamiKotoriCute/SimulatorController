#include "mainwindow.h"
#include "easyui.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->resize(800,600);

    easyUI *e = new easyUI(this);
    e->init(200, 200, 0, 0, QString("test.jpg"));

    e->setButtonAction("conversion", true, "test2.jpg");

    connect(e,&easyUI::clicked,[=]{
        if(temp)
        {
            e->moveAction(1, 10, 200, 200, "normal");
            temp = false;
        }
        else
        {
            e->moveAction(0);
            temp = true;
        }
    });
}


MainWindow::~MainWindow()
{

}
