#include "include/mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QMovie>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QMovie *movie=new QMovie(":/img/img/giphy.gif");
    if (!movie->isValid())
        {
         // Something went wrong :(
        printf("ici");
        }

    // Play GIF
    QLabel *label=new QLabel(this);

    label->setGeometry(0,20,100,120);
  //  label->size(new size(100,100));
    label->setMovie(movie);
    movie->start();
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    newproj= new Dialog();
    newproj->show();

}
