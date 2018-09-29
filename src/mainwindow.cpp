#include "include/mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QMovie>
#include <QFileDialog>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    team()
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
    // creating the dialog window
    newproj = new ProjectDialog();
    newproj->setWindowTitle("Project creation window");
    newproj->setModal(true);

    QObject::connect(newproj, SIGNAL(project_creation_send_data(std::string,int,int,int,int,int)),
                     this, SLOT(project_creation_data_received(std::string,int,int,int,int,int)));

    newproj->show();
}

void MainWindow::project_creation_data_received(std::string project_name,
                                                int development_time,
                                                int management_time,
                                                int deadline_year,
                                                int deadline_month,
                                                int deadline_day)
{
    std::cerr << "PROJECT NAME IS " << project_name << std::endl;
    std::cerr << "DEVELOPMENT TIME IS " << development_time << std::endl;
    std::cerr << "MANAGEMENT TIME IS " << management_time << std::endl;
    std::cerr << "DEADLINE IS " << deadline_year
              << "-" << deadline_month
              << "-" << deadline_day << std::endl;

    // creating a new project
    Project pro = Project(project_name, development_time, management_time, deadline_year, deadline_month, deadline_day);

    // adding it to the project list

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

    // converting QString to c++ string
    std::string name = fileName.toStdString();
    ERPConfig *config;
    try {
        config = new ERPConfig(name);
    } catch (const cpptoml::parse_exception& e) {
        std::cerr << e.what() << std::endl;
    }

    // *** DEBUG ***
    std::cerr << "PDGS:" << std::endl;
    for(std::string pdg: config->get_team()->pdgs)
    {
        std::cerr << pdg << std::endl;
    }
    std::cerr << std::endl;

    std::cerr << "PM" << std::endl;
    for(std::string pm: config->get_team()->project_managers)
    {
        std::cerr << pm << std::endl;
    }
    std::cerr << std::endl;

    std::cerr << "DCO" << std::endl;
    for(std::string dco: config->get_team()->duty_coordinators)
    {
        std::cerr << dco << std::endl;
    }
    std::cerr << std::endl;

    std::cerr << "DEVS" << std::endl;
    for(std::string dev: config->get_team()->developers)
    {
        std::cerr << dev << std::endl;
    }
    std::cerr << std::endl;

    std::cerr << "PROJECTS" << std::endl;
    for(Project *p: config->get_project_list())
    {
        std::cerr << p->get_name() << std::endl;
        std::cerr << p->get_dev_time() << std::endl;
        std::cerr << p->get_managing_time() << std::endl;
        std::cerr << p->get_deadline().get_year()
                  << "/" << p->get_deadline().get_month()
                  << "/" << p->get_deadline().get_day() << std::endl << std::endl;
    }

    // *** Initializing team and project list ***

    // clearing current team & project list
    team.pdgs.clear();
    team.project_managers.clear();
    team.duty_coordinators.clear();
    team.developers.clear();
    project_list.clear();

    // initializing with config data
    for(std::string pdg: config->get_team()->pdgs)
    {
        team.pdgs.push_back(pdg);
    }

    for(std::string pm: config->get_team()->project_managers)
    {
        team.project_managers.push_back(pm);
    }

    for(std::string dco: config->get_team()->duty_coordinators)
    {
        team.duty_coordinators.push_back(dco);
    }

    for(std::string dev: config->get_team()->developers)
    {
        team.developers.push_back(dev);
    }

    for(Project *p: config->get_project_list())
    {
        project_list.push_back(*p);
    }
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
