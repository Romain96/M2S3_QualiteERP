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

private slots:
    void on_pushButton_new_project_clicked();

    void on_actionImport_triggered();

    void on_pushButton_new_employee_clicked();

    void project_creation_data_received(std::string project_name,
                                        int development_time,
                                        int management_time,
                                        int deadline_year,
                                        int deadline_month,
                                        int deadline_day);

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
};

#endif // MAINWINDOW_H
