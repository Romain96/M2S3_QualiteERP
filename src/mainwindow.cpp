#include "include/mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QMovie>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QMovie *movie=new QMovie(":/img/img/giphy.gif");
    if (!movie->isValid())
        {
         // Something went wrong :(
        printf("here");
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

void MainWindow::on_actionImport_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "/home",
                                                    tr("data (*.toml)"));

}
