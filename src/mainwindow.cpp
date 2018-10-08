#include "include/mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QMovie>
#include <QFileDialog>
#include <iostream>
#include "include/event.h"
#include "include/eventstack.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    team(),
    current_date()
{
    QMovie *movie=new QMovie(":/img/img/giphy.gif");
    if (!movie->isValid())
        {
         // Something went wrong :(
        printf("here");
        }

    // Play GIF
    ui->setupUi(this);
    ui->icone->setGeometry(10,10,100,100);

    ui->icone->setMovie(movie);
    movie->start();


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
    // creating a new project
    Project pro = Project(project_name, development_time, management_time, deadline_year, deadline_month, deadline_day);

    // adding it to the project list
    project_list.push_back(pro);

    // updating project infos
    update_projects();

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
        std::cerr << p->get_deadline().year()
                  << "/" << p->get_deadline().month()
                  << "/" << p->get_deadline().day() << std::endl << std::endl;
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

    team.team_efficiency = config->get_team()->team_efficiency;
    team.starting_date = config->get_team()->starting_date;
    current_date = team.starting_date;

    for(Project *p: config->get_project_list())
    {
        project_list.push_back(*p);
    }

    // updating screen infos
    update();
}

/*
 * When "New Employee" button is clicked,
 * adding a new employee (developer or manager) to the team
 */
void MainWindow::on_pushButton_new_employee_clicked()
{
    newempl = new EmployeeDialog();
    newempl->setWindowTitle("Employee recruitement center");
    newempl->setModal(true);

    QObject::connect(newempl, SIGNAL(employee_creation_send_data(std::string, int, int, int, int)),
                     this, SLOT(employee_creation_data_received(std::string, int, int, int, int)));

    newempl->show();

}

void MainWindow::employee_creation_data_received(std::string employee_name,
                                                 int employee_job,
                                                 int employee_year,
                                                 int employee_month,
                                                 int employee_day)
{
    /*
    // adding the new employee to the list
    switch (employee_job)
    {
    case 0: team.pdgs.push_back(employee_name); break;
    case 1: team.duty_coordinators.push_back(employee_name); break;
    case 2: team.project_managers.push_back(employee_name); break;
    case 3: team.developers.push_back(employee_name); break;
    default: std::cerr << "ERROR index of employee is invalid !" << std::endl;
    }
    */

    // adding the new employee to the recruitement center
    rc.add_employee(employee_name, employee_job, QDate(employee_year, employee_month, employee_day));

    // updating the display of employees
    update_employees();
}

/*
 * When adding a new employee/project
 * or loading a new config file
 * updates all infos on screen
 */
void MainWindow::update()
{
    // *** updating team infos ***
    update_employees();

    // *** Updating Projects display ***
    update_projects();

    // updating efficiency display
    ui->progressBar_efficiency->setValue(team.team_efficiency);

    // updating starting date display
    std::string date = "";
    date = date + std::to_string(team.starting_date.year()) + "-"
            + std::to_string(team.starting_date.month()) + "-"
            + std::to_string(team.starting_date.day());
    QString qdate = QString::fromStdString(date);
    ui->label_start_date->setText(qdate);

    // *** Updating Result display ***
    // TODO
}

/*
 * Updates the employees infos
 */
void MainWindow::update_employees()
{
    // *** Updating Team display ***

    std::string line = "Employees :\n\n";

    line = line + " * Chief Executive Officier(s) :\n";
    for (std::string ceo_elem: team.pdgs)
    {
        line = line + "\t" + ceo_elem + "\n";
    }

    line = line + " * Duty Coordinator(s) :\n";
    for (std::string dco_elem: team.duty_coordinators)
    {
        line = line + "\t" + dco_elem + "\n";
    }

    line = line + " * Project Manager(s) :\n";
    for (std::string pm_elem: team.project_managers)
    {
        line = line + "\t" + pm_elem + "\n";
    }

    line = line + " * Developer(s) :\n";
    for (std::string dev_elem: team.developers)
    {
        line = line + "\t" + dev_elem + "\n";
    }

    QString qtext = QString::fromStdString(line);
    ui->textBrowser_employees->setText(qtext);
}

/*
 *  Updates the project infos
 */
void MainWindow::update_projects()
{
    // *** updating project infos ***

    std::string line = "Projects :\n\n";

    for (Project pro: project_list)
    {
        line = line + " * " + pro.get_name() + "\n"
                + "\tdev time : " + std::to_string(pro.get_dev_time()) + " day(s)\n"
                + "\tmanagement time : " + std::to_string(pro.get_managing_time()) + " day(s)\n"
                + "\tdeadline : " + std::to_string(pro.get_deadline().year()) + "-"
                + std::to_string(pro.get_deadline().month()) + "-"
                + std::to_string(pro.get_deadline().day()) + "\n";
    }

    QString qtext = QString::fromStdString(line);
    ui->textBrowser_projects->setText(qtext);
}

/*
 * Running simulation
 */
void MainWindow::on_pushButton_simulate_clicked()
{
    // building event stack
    es.build_event_stack(project_list);

    // for each project, computing the end date and comparing it to the deadline of the project
    while (!es.event_stack.empty())
    {
        // retrieving current "closest deadline" event
        Event e = es.event_stack.top();

        // computing the end date of the project according to the current workforce
        int dev_days = e.proj.get_dev_time() / (team.developers.size() + team.duty_coordinators.size());
        int man_days = e.proj.get_managing_time() / team.project_managers.size();

        // adding max(dev_time,man_time) to current date (5 days/week -> mon-fri)
        int days = std::max(dev_days, man_days);

        std::cerr << "starting on " << current_date.toString("yyyy.MM.dd").toStdString() << std::endl;
        // going to first monday (1=monday, 7=sunday)
        switch (current_date.dayOfWeek())
        {
        // monday
        case 1:
            // already on right starting day
            break;
        // tuesday
        case 2:
            // advancing 6 days (4 working days)
            current_date = current_date.addDays(6);
            days -= 4;
            break;
        // wednesday
        case 3:
            // advancing 5 days (3 working days)
            current_date = current_date.addDays(5);
            days -= 3;
            break;
        // thursday
        case 4:
            // advancing 4 days (2 working days)
            current_date = current_date.addDays(4);
            days -= 2;
            break;
        // friday
        case 5:
            // advancing 3 days (1 working day)
            current_date = current_date.addDays(3);
            days -= 1;
            break;
        // saturday
        case 6:
            // advancing 2 days (no working day)
            current_date = current_date.addDays(2);
            break;
        // sunday
        case 7:
            // advancing 1 day (no working day)
            current_date = current_date.addDays(1);
            break;
        default: std::cerr << "ERROR dayOfWeek outside of range 1-7 !" << std::endl;
        }

        // advancing the number of weeks
        int weeks = days/5;
        days = days - weeks*5;
        current_date = current_date.addDays(7*weeks + days);
        std::cerr << "finishing on " << current_date.toString("yyyy.MM.dd").toStdString() << std::endl;

        // comparing end date with deadline
        if (current_date < e.proj.get_deadline())
        {
            std::cerr << "Project " << e.proj.get_name() << " validated ( "
                      << current_date.toString("yyyy.MM.dd").toStdString() << " < "
                      << e.proj.get_deadline().toString("yyyy.MM.dd").toStdString() << ")" << std::endl;
        }
        else
        {
            std::cerr << "Project " << e.proj.get_name() << " invalidated ( "
                      << current_date.toString("yyyy.MM.dd").toStdString() << " >= "
                      << e.proj.get_deadline().toString("yyyy.MM.dd").toStdString() << ")" << std::endl;
        }

        es.event_stack.pop();
    }
}
