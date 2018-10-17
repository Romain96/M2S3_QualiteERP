#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <iostream>
#include <fstream>
#include "include/project_dialog.h"
#include "include/employee_dialog.h"
#include "include/project.h"
#include "include/team.h"
#include "lib/cpptoml.h"
#include "include/erp_config.h"
#include "include/event.h"
#include "include/event_stack.h"
#include "include/recruitement_center.h"
#include "include/result_dialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    // updating screen infos (team, projects, result)
    void update();

    // updating employee infos only
    void update_employees();

    // updating project infos only
    void update_projects();

private slots:
    void on_pushButton_new_project_clicked();

    void on_actionImport_triggered();

    void on_pushButton_new_employee_clicked();

    // used to receive the signal containing data from new project
    void project_creation_data_received(std::string project_name,
                                        int development_time,
                                        int management_time,
                                        int price,
                                        int deadline_year,
                                        int deadline_month,
                                        int deadline_day);

    // used to receive the signal containing data from new employee
    void employee_creation_data_received(std::string employee_name,
                                         int employee_job,
                                         int employee_year,
                                         int employee_month,
                                         int employee_day);

    void on_pushButton_simulate_clicked();

private:

    // new project creation window
    ProjectDialog *newproj;
    // new employee recuirtement window
    EmployeeDialog *newempl;

    //result window
    Result_Dialog *result_diag;


    // main UI
    Ui::MainWindow *ui;


    // Inside Out's team
    Team team;
    // Inside Out's project list
    std::vector<Project> project_list;
    // current date
    QDate current_date;
    // Recruitement center
    RecruitementCenter rc;
    // Event stack
    EventStack es;

    // log writing methods
    void __log_write_general_infos(std::ofstream& output);

    void __log_write_simulation_start(std::ofstream& output, QDate date);

    void __log_write_simulation_end(std::ofstream& output, QDate date);

    void __log_write_project_start(std::ofstream& output,
                                   std::vector<Project>::iterator& project_it,
                                   int man_days_remaining,
                                   int dev_days_remaining,
                                   QDate start_date,
                                   QDate end_date);

    void __log_write_project_validation(std::ofstream& output,
                                        std::vector<Project>::iterator project_it,
                                        QDate end_date);

    void __log_write_project_ressources_computation(std::ofstream& output,
                                                    int ideal_man,
                                                    int ideal_man_more,
                                                    int ideal_dev,
                                                    int ideal_dev_more,
                                                    std::vector<Project>::iterator project_it);

    void __log_write_project_invalidation(std::ofstream& output,
                                          std::vector<Project>::iterator project_it);

    void __log_write_project_impossible_completion(std::ostream& output,
                                                   std::vector<Project>::iterator project_it,
                                                   QDate date);

    void __log_write_project_rejection(std::ofstream& output,
                                       std::vector<Project>::iterator project_it,
                                       QDate date);

    void __log_write_new_employee_addition(std::ofstream& output,
                                           QDate date,
                                           std::vector<Project>::iterator project_it,
                                           int man_days_remaining,
                                           int man_days,
                                           int man_team_size,
                                           int dev_days_remaining,
                                           int dev_days,
                                           int dev_team_size,
                                           QDate end_date);

    void __log_write_general_needed_ressources(std::ostream& output,
                                               int general_needed_man,
                                               int general_needed_dev);

    // internal methods
    int __working_days_in_week(QDate date);
    int __working_days_between_dates(QDate date1, QDate date2);
    QDate __end_date_from_days(QDate date, int days);
    QDate __earliest_last_working_day(QDate date);
    QDate __earliest_working_day_from_date(QDate date);    
};

#endif // MAINWINDOW_H
