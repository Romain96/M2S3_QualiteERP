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

    this->setWindowTitle("Inside Out's very minimalistic ERP");
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
 * When "New Project" button is clicked,
 * adding a new project to the project list
 */
void MainWindow::on_pushButton_new_project_clicked()
{
    newproj= new Dialog();
    newproj->setWindowTitle("Project creation window");
    newproj->show();

}

/*
 * Importing a toml data file containing a team of dev/manager and
 * a list of projects
 */
void MainWindow::on_actionImport_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "/home",
                                                    tr("data (*.toml)"));

    // TODO parser init TEAM

}

/*
 * When "New Employee" button is clicked,
 * adding a new employee (developer or manager) to the team
 */
void MainWindow::on_pushButton_new_employee_clicked()
{
    newempl= new EmployeeDialog();
    newempl->setWindowTitle("Employee recruitement center");
    newempl->show();

}
