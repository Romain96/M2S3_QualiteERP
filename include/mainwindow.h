#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include "include/project_dialog.h"
#include "include/employee_dialog.h"
#include "include/project.h"
#include "include/team.h"
#include "lib/cpptoml.h"
#include "include/erp_config.h"
#include "include/event.h"
#include "include/event_stack.h"
#include "include/recruitement_center.h"

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

    // internal methods
    int __working_days_in_week(QDate date);
    int __working_days_between_dates(QDate date1, QDate date2);
    QDate __end_date_from_days(QDate date, int days);
    QDate __earliest_last_working_day(QDate date);
    QDate __earliest_working_day_from_date(QDate date);
};

#endif // MAINWINDOW_H
