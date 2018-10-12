#include "include/mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QMovie>
#include <QFileDialog>
#include <iostream>
#include "include/event.h"
#include "include/event_stack.h"
#include <deque>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <QTime>

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

    QObject::connect(newproj, SIGNAL(project_creation_send_data(std::string,int,int,int,int,int,int)),
                     this, SLOT(project_creation_data_received(std::string,int,int,int,int,int,int)));

    newproj->show();
}

void MainWindow::project_creation_data_received(std::string project_name,
                                                int development_time,
                                                int management_time,
                                                int price,
                                                int deadline_year,
                                                int deadline_month,
                                                int deadline_day)
{
    // creating a new project
    Project pro = Project(project_name, development_time, management_time, price, deadline_year, deadline_month, deadline_day);

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
                                                    ":/data",
                                                    tr("data (*.toml)"));

    if (!fileName.isEmpty())
    {
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
    // adding the new employee to the recruitement center
    rc.add_employee(employee_name, employee_job, QDate(employee_year, employee_month, employee_day));
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

    // if efficiency is more than 100% a special teatment needs to be applied
    // to show the right value (real value is correct but shown value is wrong)
    if (team.team_efficiency > 100)
    {
        ui->progressBar_efficiency->setRange(0,team.team_efficiency);
        ui->progressBar_efficiency->setFormat("%v%");
    }

    // updating efficiency display
    ui->progressBar_efficiency->setValue(team.team_efficiency);

    // updating current date display
    std::string date = "";
    date = date + std::to_string(current_date.year()) + "-"
            + std::to_string(current_date.month()) + "-"
            + std::to_string(current_date.day());
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
                + "\tdeadline : " + pro.get_deadline().toString("yyyy.MM.dd").toStdString() + "\n";
    }

    QString qtext = QString::fromStdString(line);
    ui->textBrowser_projects->setText(qtext);
}

/*
 * *** Running simulation ***
 * - computes start/end dates for each projects
 * - dynamically adds new employees (recruits)
 * - computes minimal needed ressources in case of non completion of a project
 * - writes the result in a file (chronological order)
 */
void MainWindow::on_pushButton_simulate_clicked()
{
    std::cerr << "RUNNING SIMULATION..." << std::endl;

    // building event stack
    es.build_event_stack(project_list, rc);

    // output stream
    std::ofstream output_file;
    std::string output_file_name = "./results";
    output_file.open(output_file_name);

    // writing general informations
    output_file << "This file has been generated on "
                << QDate::currentDate().toString("yyyy.MM.dd").toStdString() << " at "
                << QTime::currentTime().toString("hh:mm:ss").toStdString() << " "
                << "\nby 'Inside Out's very minimalistic ERP'\n\n"
                << "-------------------------------------------------------------------------------\n"
                << "********** Inside Out's Team on "
                << team.starting_date.toString("yyyy.MM.dd").toStdString()
                << " **********\n\n";

    // Inside Out's employee list
    output_file << "// Chief Excutive Officers carries no management or development duties...\n"
                << "* [CEO] Chief Executive Officer(s) :\n";
    for (std::string ceo: team.pdgs)
        output_file << "\t- " << ceo << "\n";

    output_file << "\n// Duty Coordinators are technical experts and carries development duties...\n"
                << "* [DCO] Duty Coordinator(s) :\n";
    for (std::string dco: team.duty_coordinators)
        output_file << "\t- " << dco << "\n";

    output_file << "\n// Project Managers are purely managers and only carries management duties...\n"
                << "* [PM] Project Manager(s) :\n";
    for (std::string pm: team.project_managers)
        output_file << "\t- " << pm << "\n";

    output_file << "\n// Developers are the backbone of the team and carries development duties...\n"
                << "* [DEV] Developer(s) :\n";
    for (std::string dev: team.developers)
        output_file << "\t- " << dev << "\n";

    output_file << "\n// The efficiency is the measure of the quantity of work an employee\n"
                << "// is able to accomplish in a single day of work\n"
                << "// The lower the efficiency the longer it will take to complete a project\n"
                << "// The higher the efficiency the shorter it will take to complete a project\n"
                << "// The efficiency is global (the same for all employees) and fixed\n"
                << "* [Efficiency] Team Efficiency : " << team.team_efficiency << "\n"
                << "-------------------------------------------------------------------------------\n" << std::endl;

    // Inside Out's project list
    output_file << "-------------------------------------------------------------------------------\n"
                << "********** Inside Out's Project list on "
                << team.starting_date.toString("yyyy.MM.dd").toStdString()
                << " **********\n\n";

    for (Project pro: project_list)
    {
        output_file << "* " << pro.get_name() << "\n"
                    << "\t- " << pro.get_managing_time() << " day(s) of management\n"
                    << "\t- " << pro.get_dev_time() << " day(s) of development\n"
                    << "\t- " << pro.get_deadline().toString("yyyy.MM.dd").toStdString() << " fixed deadline\n\n";
    }

    output_file << "-------------------------------------------------------------------------------\n" << std::endl;

    // writing start of simulation
    output_file << "-------------------------------------------------------------------------------\n"
                << "* " << current_date.toString("yyyy.MM.dd").toStdString() << " : Starting simulation\n"
                << "-------------------------------------------------------------------------------\n\n";

    // if unsufficient ressources, general needed ressources are stored here
    int general_needed_dev = 0;
    int general_needed_man = 0;

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

        // computing maximum time (days) required to finish the project
        int dev_days_remaining = static_cast<int>(std::ceil(static_cast<double>(dev_days) * (100.0 + (100.0 - static_cast<double>(team.team_efficiency)))/100.0));
        int man_days_remaining = static_cast<int>(std::ceil(static_cast<double>(man_days) * (100.0 + (100.0 - static_cast<double>(team.team_efficiency)))/100.0));
        int total_days_remaining = std::max(dev_days_remaining, man_days_remaining);

        // advancing to first working day from current date
        current_date = __earliest_working_day_from_date(current_date);

        std::cerr << "starting project on " << current_date.toString("yyyy.MM.dd").toStdString() << std::endl;
        end_date = __end_date_from_days(current_date, total_days_remaining);
        output_file << "-------------------------------------------------------------------------------\n"
                    << "* " << current_date.toString("yyyy.MM.dd").toStdString()
                    << " : starting project " << (*current_project_it).get_name() << "\n"
                    << "\t- " << man_days_remaining << " day(s) of management are needed "
                    << "(" << (*current_project_it).get_managing_time() << " days splitted on " << team.project_managers.size() << " PMs)\n"
                    << "\t- " << dev_days_remaining << " day(s) of development are needed "
                    << "(" << (*current_project_it).get_dev_time() << " days splitted on " << team.duty_coordinators.size() + team.developers.size() << " DCOs/DEVs)\n"
                    << "\t- Expected end date with current workforce : " << end_date.toString("yyyy.MM.dd").toStdString()
                    << "\n-------------------------------------------------------------------------------\n\n";
        std::cerr << "finishing project on " << end_date.toString("yyyy.MM.dd").toStdString() << std::endl;

        /*
         * retrieving the closest event from the event stack that is a project
         * and storing all employee events in a temporary deque
         */
        std::deque<Event> temporary_event_holder;
        Event e = es.event_stack.top();
        while (!es.event_stack.empty())
        {
            e = es.event_stack.top();
            if (e.is_proj)
                    break;

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
                current_date = end_date;

                // writing log
                output_file << "-------------------------------------------------------------------------------\n"
                            << "* " << current_date.toString("yyyy.MM.dd").toStdString() << " : Project "
                            << (*current_project_it).get_name() << " is finished before deadline\n"
                            << "-------------------------------------------------------------------------------\n\n";

                current_project_it++;
            }
            // if the computed end date is after the deadline, the project in invalidated !
            else
            {
                std::cerr << "* Project " << (*current_project_it).get_name() << " is invalidated !" << std::endl;
                std::cerr << "\t(" << end_date.toString("yyyy.MM.dd").toStdString() << " > " << e.date.toString("yyyy.MM.dd").toStdString() << std::endl;

                // computing ressources necessary to complete project before deadline
                int max_working_days = __working_days_between_dates(current_date, (*current_project_it).get_deadline());
                int ideal_dev = 0;
                int ideal_man = 0;

                if (max_working_days > 0)
                {
                    ideal_dev = (*current_project_it).get_dev_time() / max_working_days;
                    ideal_man = static_cast<int>(std::ceil(static_cast<double>((*current_project_it).get_managing_time()) / static_cast<double>(max_working_days)));

                    std::cerr << "Needed ressources : " << ideal_dev << " devs & " << ideal_man << " PM" << std::endl;
                    general_needed_dev = std::max(general_needed_dev, ideal_dev - static_cast<int>(team.developers.size() + team.duty_coordinators.size()));
                    general_needed_man = std::max(general_needed_man, ideal_man - static_cast<int>(team.project_managers.size()));

                    // writing incomplete ressources log
                    output_file << "-------------------------------------------------------------------------------\n"
                                << "* INSUFFICIENT RESSOURCES to complete project " << (*current_project_it).get_name() << "\n"
                                << "\t- Number of development personel needed : " << ideal_dev << " ("
                                << ideal_dev - static_cast<int>(team.developers.size() + team.duty_coordinators.size()) << " more)\n"
                                << "\t- Number of management personel needed : " << ideal_man << " ("
                                << ideal_man - static_cast<int>(team.project_managers.size()) << " more)\n"
                                << "-------------------------------------------------------------------------------\n\n";

                    // writing project invalidation log
                    output_file << "-------------------------------------------------------------------------------\n"
                                << " * " << (*current_project_it).get_deadline().toString("yyyy.MM.dd").toStdString() << " : Project "
                                << (*current_project_it).get_name() << " invalidated \nbut supposed as finished on deadline day with additionnal computed ressources\n"
                                << "-------------------------------------------------------------------------------\n\n";

                    // supposing project finished on deadline day
                    current_date = (*current_project_it).get_deadline();
                    current_project_it++;
                }
                else
                {
                    // writing impossible project completion log (deadline date < starting date)
                    output_file << "-------------------------------------------------------------------------------\n"
                                << "* IMPOSSIBLE COMPLETION of project " << (*current_project_it).get_name() << "\n"
                                << "deadline date " << (*current_project_it).get_deadline().toString("yyyy.MM.dd").toStdString()
                                << " is earlier than starting date " << current_date.toString("yyyy.MM.dd").toStdString() << "\n"
                                << "-------------------------------------------------------------------------------\n\n";

                    // writing project rejection log
                    output_file << "-------------------------------------------------------------------------------\n"
                                << " * " << current_date.toString("yyyy.MM.dd").toStdString() << " : Project "
                                << (*current_project_it).get_name() << " rejected\n"
                                << "-------------------------------------------------------------------------------\n\n";

                    // skipping project (date is not advancing)
                    current_project_it++;
                }
                // removing project from event stack
                es.event_stack.pop();  
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
            dev_days_remaining = (*current_project_it).get_dev_time() / (team.developers.size() + team.duty_coordinators.size());
            man_days_remaining = (*current_project_it).get_managing_time() / team.project_managers.size();
            int remaining_days = std::max(dev_days_remaining,man_days_remaining);

            std::cerr << "dev remaining : " << dev_days_remaining << ", man remaining : " << man_days_remaining << std::endl;

            // for each date until the end of the project computing the new end date
            while (!temporary_event_holder.empty())
            {
                // retrieving closest event
                Event e = temporary_event_holder.front();

                // computing maximum number of days (working days) left before event
                int max_days = __working_days_between_dates(current_date, e.date);
                std::cerr << "working days to event " << max_days << std::endl;

                // if remaining project days are smaller than the number of days to the event
                if (remaining_days < max_days)
                {
                    std::cerr << "remaining days smaller than event " << remaining_days << " < " << max_days << std::endl;
                    // removing project from event stack
                    es.event_stack.pop();

                    // all subsequent events including this one need to be replaced on the the event stack
                    while (!temporary_event_holder.empty())
                    {
                        Event e = temporary_event_holder.back();
                        es.event_stack.push(e);
                        std::cerr << "replacing [employee] event " << e.employee.first << " in event stack" << std::endl;
                        temporary_event_holder.pop_back();
                    }
                    new_end_date = current_date.addDays(remaining_days);
                    current_date = new_end_date;
                    std::cerr << "* Project " << (*current_project_it).get_name() << " is validated" << std::endl;
                    current_project_it++;
                }
                // if remaining project days are bigger then the number of days to the event
                else
                {
                    std::cerr << "remaining days bigger than event " << remaining_days << " >= " << max_days << std::endl;
                    // computing new remaining days/weeks
                    dev_days_remaining = std::max(0, dev_days_remaining - max_days);
                    man_days_remaining = std::max(0, man_days_remaining - max_days);
                    total_days_remaining = std::max(dev_days_remaining, man_days_remaining);

                    std::cerr << "new remaining days : " << remaining_days << std::endl;
                    //new_end_date = current_date.addDays(max_days);

                    // adding employee to the team + writing log
                    output_file << "-------------------------------------------------------------------------------\n"
                                << "* " << e.date.toString("yyyy.MM.dd").toStdString() << " : The new ";

                    // before adding new employee, computing real number of days (not divided)
                    dev_days = dev_days_remaining * static_cast<int>(team.developers.size() + team.duty_coordinators.size());
                    man_days = man_days_remaining * static_cast<int>(team.project_managers.size());

                    switch (e.employee.second.first)
                    {
                    case 0:
                        team.pdgs.push_back(e.employee.first);
                        output_file << "CEO " << e.employee.first << " recruited last month \nis now a full member of the team\n";
                        break;
                    case 1:
                        team.duty_coordinators.push_back(e.employee.first);
                        output_file << "DCO " << e.employee.first << " recruited last month \nis now a full member of the team\n";
                        break;
                    case 2:
                        team.project_managers.push_back(e.employee.first);
                        output_file << "PM " << e.employee.first << " recruited last month \nis now a full member of the team\n";
                        break;
                    case 3:
                        team.developers.push_back(e.employee.first);
                        output_file << "DEV " << e.employee.first << " recruited last month \nis now a full member of the team\n";
                        break;
                    default: std::cerr << "ERROR index of employee is invalid !" << std::endl;
                    }
                    output_file << "-------------------------------------------------------------------------------\n\n";

                    // then dividing work again
                    dev_days_remaining = static_cast<int>(std::ceil(dev_days / static_cast<double>(team.developers.size() + team.duty_coordinators.size())));
                    man_days_remaining = static_cast<int>(std::ceil(man_days / static_cast<double>(team.project_managers.size())));
                    total_days_remaining = std::max(dev_days_remaining, man_days_remaining);
                    new_end_date = __end_date_from_days(e.date, total_days_remaining);

                    // writing infos about current project (updated)
                    output_file << "-------------------------------------------------------------------------------\n"
                                << "* " << e.date.toString("yyyy.MM.dd").toStdString()
                                << " : project " << (*current_project_it).get_name() << " advancement report :\n"
                                << "\t- " << man_days_remaining << " day(s) of management are needed "
                                << "(" << man_days << " days splitted on " << team.project_managers.size() << " PMs)\n"
                                << "\t- " << dev_days_remaining << " day(s) of development are needed "
                                << "(" << dev_days << " days splitted on " << team.duty_coordinators.size() + team.developers.size() << " DCOs/DEVs)\n"
                                << "\t- Expected end date with current workforce : " << new_end_date.toString("yyyy.MM.dd").toStdString()
                                << "\n-------------------------------------------------------------------------------\n\n";

                    // updating the display of employees
                    update_employees();

                    temporary_event_holder.pop_front();

                    // if temporary event holder is empty we have to decide whether the project is validated
                    if (temporary_event_holder.empty())
                    {
                        //new_end_date = __end_date_from_days(new_end_date, total_days_remaining);
                        if(new_end_date < (*current_project_it).get_deadline())
                        {
                            std::cerr << "* Project " << (*current_project_it).get_name() << " is validated !" << std::endl;

                            // writing project validation log
                            output_file << "-------------------------------------------------------------------------------\n"
                                        << "* " << new_end_date.toString("yyyy.MM.dd").toStdString() << " : Project "
                                        << (*current_project_it).get_name() << " is finished before deadline\n"
                                        << "-------------------------------------------------------------------------------\n\n";
                        }
                        else
                        {
                            // same as project invalidation when temporary_event_holder is empty when constructed

                            std::cerr << "* Project " << (*current_project_it).get_name() << " is invalidated !" << std::endl;
                            std::cerr << "\t(" << end_date.toString("yyyy.MM.dd").toStdString() << " > " << e.date.toString("yyyy.MM.dd").toStdString() << std::endl;

                            // computing ressources necessary to complete project before deadline
                            int max_working_days = __working_days_between_dates(e.date, (*current_project_it).get_deadline());
                            int ideal_dev = 0;
                            int ideal_man = 0;

                            if (max_working_days > 0)
                            {
                                ideal_dev = (*current_project_it).get_dev_time() / max_working_days;
                                ideal_man = static_cast<int>(std::ceil(static_cast<double>((*current_project_it).get_managing_time()) / static_cast<double>(max_working_days)));

                                std::cerr << "Needed ressources : " << ideal_dev << " devs & " << ideal_man << " PM" << std::endl;
                                general_needed_dev = std::max(general_needed_dev, ideal_dev - static_cast<int>(team.developers.size() + team.duty_coordinators.size()));
                                general_needed_man = std::max(general_needed_man, ideal_man - static_cast<int>(team.project_managers.size()));

                                // writing incomplete ressources log
                                output_file << "-------------------------------------------------------------------------------\n"
                                            << "* INSUFFICIENT RESSOURCES to complete project " << (*current_project_it).get_name() << "\n"
                                            << "\t- Number of development personel needed : " << ideal_dev << " ("
                                            << ideal_dev - static_cast<int>(team.developers.size() + team.duty_coordinators.size()) << " more)\n"
                                            << "\t- Number of management personel needed : " << ideal_man << " ("
                                            << ideal_man - static_cast<int>(team.project_managers.size()) << " more)\n"
                                            << "-------------------------------------------------------------------------------\n\n";

                                // writing project invalidation log
                                output_file << "-------------------------------------------------------------------------------\n"
                                            << " * " << (*current_project_it).get_deadline().toString("yyyy.MM.dd").toStdString() << " : Project "
                                            << (*current_project_it).get_name() << " invalidated \nbut supposed as finished on deadline day with additionnal computed ressources\n"
                                            << "-------------------------------------------------------------------------------\n\n";

                                // supposing project finished on deadline day
                                new_end_date = (*current_project_it).get_deadline();
                            }
                            else
                            {
                                // writing impossible project completion log (deadline date < starting date)
                                output_file << "-------------------------------------------------------------------------------\n"
                                            << "* IMPOSSIBLE COMPLETION of project " << (*current_project_it).get_name() << "\n"
                                            << "deadline date " << (*current_project_it).get_deadline().toString("yyyy.MM.dd").toStdString()
                                            << " is earlier than starting date " << current_date.toString("yyyy.MM.dd").toStdString() << "\n"
                                            << "-------------------------------------------------------------------------------\n\n";

                                // writing project rejection log
                                output_file << "-------------------------------------------------------------------------------\n"
                                            << " * " << current_date.toString("yyyy.MM.dd").toStdString() << " : Project "
                                            << (*current_project_it).get_name() << " rejected\n"
                                            << "-------------------------------------------------------------------------------\n\n";
                            }
                        }
                        // removing project from event stack
                        es.event_stack.pop();
                        current_date = new_end_date;
                        current_project_it++;
                    }
                }
            }
        }
        // advancing to next day (project if finished at the end of the current day)
        current_date = current_date.addDays(1);
    } 
    // needed ressources (default : 0)
    std::cerr << "Minimum needed ressources to complete all projects :"
              << "\n\t" << general_needed_dev << " dev(s)/duty coordinator(s)"
              << "\n\t" << general_needed_man << " PMs" << std::endl;

    // writing needed ressources (if more than 0)
    if (std::max(general_needed_dev, general_needed_man) > 0)
    {
        output_file << "-------------------------------------------------------------------------------\n"
                    << " This message only appears when at least one project couldn't be terminated\n"
                    << " before its deadline with the current workforce.\n"
                    << " Keep in mind that the additionnal needed employees are considered fully part\n"
                    << " of the team on its starting day; the usual 3 months recruting period and\n"
                    << " 1 month integration to reach the desired efficiency are not taken into account.\n\n"
                    << " Minimal needed ressources in order to complete all planned projects :\n"
                    << "\t- " << general_needed_man << " additionnal managing staff (PMs)\n"
                    << "\t- " << general_needed_dev << " additionnal development staff (DEVs/DCOs)\n"
                    << "-------------------------------------------------------------------------------\n\n";
    }

    // end of simulation log
    output_file << "-------------------------------------------------------------------------------\n"
                << "* " << current_date.toString("yyyy.MM.dd").toStdString() << " : simulation finished !\n"
                << "-------------------------------------------------------------------------------\n";

    // closing output stream
    output_file.close();

    std::cerr << "SIMULATION COMPLETED !" << std::endl;
    update();


    this->result_diag = new Result_Dialog();
    std::string res = "additionnal development staff (DEVs/DCOs): " + std::to_string(general_needed_dev) + "\n" + "additionnal managing staff (PMs) : " + std::to_string(general_needed_man) + ".";
    this->result_diag->display_result(res);
    this->result_diag->show();

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
    // working days in the first week (week of date1)
    int wd_first = __working_days_in_week(date1);
    // working days in the last week (week of date2) before date2
    int wd_last = 5 - __working_days_in_week(date2);

    qint64 days = date1.daysTo(date2);
    if (days < 1)
    {
        // date1 >= date2
        return 0;
    }
    else if (days < 7)
    {
        // date1 and date2 are in the same week
        return std::min(wd_first, wd_last);
    }
    else
    {
        int inter_weeks = static_cast<int>(std::ceil(static_cast<double>(days - wd_first - wd_last + 2) / 7));
        return 5 * inter_weeks + wd_first + wd_last;
    }
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

/*
 *  Internal use only : computes the earliest working starting from "date"
 *  if "date" is monday-friday the returning date else returning following monday
 */
QDate MainWindow::__earliest_working_day_from_date(QDate date)
{
    // saturday
    if (date.dayOfWeek() == 6)
        return date.addDays(2);
    // sunday
    else if (date.dayOfWeek() == 7)
        return date.addDays(1);
    // monday to friday
    else
        return date;
}
