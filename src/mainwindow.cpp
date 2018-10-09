#include "include/mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QMovie>
#include <QFileDialog>
#include <iostream>
#include "include/event.h"
#include "include/eventstack.h"
#include <deque>
#include <algorithm>

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
    es.build_event_stack(project_list, rc);

    // putting project list in the right order again
    std::reverse(project_list.begin(), project_list.end());

    // retrieving current "closest deadline" project
    std::vector<Project>::iterator current_project_it = project_list.begin();
    QDate end_date = current_date;

    // for each project, computing the end date and comparing it to the deadline of the project
    while (!es.event_stack.empty())
    {
        // computing the end date of the project according to the current workforce
        int dev_days = (*current_project_it).get_dev_time() / (team.developers.size() + team.duty_coordinators.size());
        int man_days = (*current_project_it).get_managing_time() / team.project_managers.size();

        // adding max(dev_time,man_time) to current date (5 days/week -> mon-fri)
        int days = std::max(dev_days, man_days);

        std::cerr << "starting project on " << current_date.toString("yyyy.MM.dd").toStdString() << std::endl;
        end_date = __end_date_from_days(current_date, days);
        std::cerr << "finishing project on " << end_date.toString("yyyy.MM.dd").toStdString() << std::endl;

        /*
         * retrieving the closest event from the event stack that is a project
         * and storing all employee events in a temporary deque
         */
        std::deque<Event> temporary_event_holder;
        Event e = es.event_stack.top();
        while (!es.event_stack.empty() && !e.is_proj)
        {
            e = es.event_stack.top();
            std::cerr << "[FIFO] building with " << e.employee.first << std::endl;
            temporary_event_holder.push_back(e);
            es.event_stack.pop();         
        }

        /*
         * if the temporary event holder is empty there is no recruitement event between
         * the computed date and the deadline of the closest project
         */
        if (temporary_event_holder.empty())
        {
            // if the computed end date is before the deadline, the project is validated
            if (end_date <= e.date)
            {
                std::cerr << "* Project " << (*current_project_it).get_name() << " is validated !" << std::endl;
                std::cerr << "\t(" << end_date.toString("yyyy.MM.dd").toStdString() << " <= " << e.date.toString("yyyy.MM.dd").toStdString() << std::endl;
                es.event_stack.pop();
                current_project_it++;
                current_date = end_date;
            }
            // if the computed end date is after the deadline, the project in invalidated !
            else
            {
                std::cerr << "* Project " << (*current_project_it).get_name() << " is invalidated !" << std::endl;
                std::cerr << "\t(" << end_date.toString("yyyy.MM.dd").toStdString() << " <= " << e.date.toString("yyyy.MM.dd").toStdString() << std::endl;
                es.event_stack.pop();
                current_project_it++;
                current_date = end_date;
                // TODO : compute needed ressources to complete the project
            }
        }
        /*
         * if the temporary event stack is not empty there are one or several recruitements taking
         * place before the deadline of the project but not neccessarily before our computed end date
         * we need to check whether we need to smplit the computation of our end date
         * (one of these events happens before our computed end date) of not (our computed end date is the closest event)
         */
        else
        {
            std::cerr << "temporary event holder not empty" <<std::endl;

            QDate new_end_date = current_date;
            int total_dev = (*current_project_it).get_dev_time() / (team.developers.size() + team.duty_coordinators.size());
            int total_man = (*current_project_it).get_managing_time() / team.project_managers.size();
            int remaining_days = std::max(total_dev,total_man);
            int remaining_weeks = remaining_days/5;
            remaining_days = remaining_days - 5*remaining_weeks;

            // for each date until the end of the project computing the new end date
            while (!temporary_event_holder.empty())
            {
                // retrieving closest event
                Event e = temporary_event_holder.front();
                // computing number of days from current date to first event
                qint64 days_to_event = new_end_date.daysTo(e.date);
                std::cerr << "days to event " << days_to_event << std::endl;
                int weeks_to_event = days_to_event/7;
                days_to_event = days_to_event - 7*weeks_to_event;

                // if remaining project days are smaller than the number of days to the event
                if (7*remaining_weeks + remaining_days < 7*weeks_to_event + days_to_event)
                {
                    std::cerr << "remaining days smaller than event " << 7*remaining_weeks + remaining_days
                              << " < " << 7*weeks_to_event + days_to_event << std::endl;
                    // all subsequent events including this one need to be replaced on the the event stack
                    while (!temporary_event_holder.empty())
                    {
                        Event e = temporary_event_holder.back();
                        es.event_stack.push(e);
                        std::cerr << "replacing event " << e.employee.first << " in event stack" << std::endl;
                        temporary_event_holder.pop_back();
                    }
                    new_end_date = current_date.addDays(7*remaining_weeks + remaining_days);
                    current_date = new_end_date;
                    std::cerr << "* Project " << (*current_project_it).get_name() << " is validated" << std::endl;
                    current_project_it++;
                    std::cerr << "ES size " << es.event_stack.size() << std::endl;
                }
                // if remaining project days are bigger then the number of days to the event
                else
                {
                    std::cerr << "remaining days bigger than event " << 7*remaining_weeks + remaining_days
                              << " >= " << 7*weeks_to_event + days_to_event << std::endl;
                    // computing new remaining days/weeks
                    remaining_days = 5*remaining_weeks + remaining_days;
                    remaining_weeks = remaining_days - (7*weeks_to_event + days_to_event)/5;
                    remaining_days = remaining_days - 5*remaining_weeks;
                    std::cerr << "new remaining time : " << 5*remaining_weeks + remaining_days << std::endl;
                    new_end_date = current_date.addDays(7*weeks_to_event + days_to_event);

                    // TODO add employee to team
                    switch (e.employee.second.first)
                    {
                    case 0: team.pdgs.push_back(e.employee.first); break;
                    case 1: team.duty_coordinators.push_back(e.employee.first); break;
                    case 2: team.project_managers.push_back(e.employee.first); break;
                    case 3: team.developers.push_back(e.employee.first); break;
                    default: std::cerr << "ERROR index of employee is invalid !" << std::endl;
                    }

                    temporary_event_holder.pop_front();

                    // if temporary event holder is empty we have to decide whether the project is validated
                    if (temporary_event_holder.empty())
                    {
                        std::cerr << "TODO" << temporary_event_holder.size() << std::endl;
                        current_project_it++;
                    }
                }
            }
        }
    }
}

/*
 * Internal use only : computes the working days in the week beginning on the days indicated by the date
 */
int MainWindow::__working_days_in_week(QDate date)
{
    int wd = 0;
    switch (date.dayOfWeek())
    {
    case 1:
        wd = 5; // mon-fri
        break;
    case 2:
        wd = 4; // tue-fri
        break;
    case 3:
        wd = 3; // wed-fri
        break;
    case 4:
        wd = 2; // thu-fri
        break;
    case 5:
        wd = 1; // fri-fri
        break;
    case 6:
        wd = 0;
        break;
    case 7:
        wd = 0;
        break;
    }

    return wd;
}

/*
 * Internal use only : computes the working days from the day indicated by the first date (included)
 * to the day indicated by the second date (not included)
 */
int MainWindow::__working_days_between_dates(QDate date1, QDate date2)
{
    std::cerr << "__working_days_between_dates" << std::endl;

    // working days in the first week (week of date1)
    int wd_first = __working_days_in_week(date1);
    // working days in the last week (week of date2) before date2
    int wd_last = 5 - __working_days_in_week(date2);

    // computing number of weeks between the two dates
    int weeks = date2.weekNumber() - date1.weekNumber();

    // number of full working weeks = weeks - 2 (first and last already computed)
    int wd = (weeks - 2) * 5 + wd_first + wd_last;

    std::cerr << "first : " << wd_first
              << "last : " << wd_last
              << "weeks : " << weeks
              << "wd : " << wd << std::endl;

    return wd;
}

/*
 * Internal use only : computes the end date (first day from which the project is finished)
 * from "date" (included) with "days" working days
 */
QDate MainWindow::__end_date_from_days(QDate date, int days)
{
    QDate end_date = date;

    // if starting day is a saturday/sunday giong to first monday (first working day)
    if (date.dayOfWeek() == 6)
    {
        end_date = date.addDays(2);
    }
    else if (date.dayOfWeek() == 7)
    {
        end_date = date.addDays(1);
    }

    // computing the number of weeks (5 working days/week) and days
    int nb_weeks = days/5;
    int nb_days = days - nb_weeks * 5;

    // advancing the correct amount of weeks/days
    end_date = end_date.addDays(7*nb_weeks + nb_days);

    // returning previous last working day
    return __earliest_last_working_day(end_date);
}

/*
 * Intenal use only : computes the earliest last working day before the beginning of
 * the day indicated by "date" (ex : for monday 12th semptember -> friday 9th september)
 */
QDate MainWindow::__earliest_last_working_day(QDate date)
{
    QDate last = date;
    std::cerr << "__earliest date " << last.toString("yyyy.MM.dd").toStdString() << std::endl;

    // if monday then last friday
    if (date.dayOfWeek() == 1)
    {
        last = date.addDays(-3);
    }
    // if sunday then last friday
    else if (date.dayOfWeek() == 7)
    {
        last = date.addDays(-2);
    }
    // else the previous day
    else
    {
        last = date.addDays(-1);
    }

    return last;
}
