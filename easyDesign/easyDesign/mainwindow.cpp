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
            e->changeAction(1,100,"test2.jpg");
            temp = false;
        }
        else
        {
            e->changeAction(0);
            temp = true;
        }
    });
}


MainWindow::~MainWindow()
{

}
