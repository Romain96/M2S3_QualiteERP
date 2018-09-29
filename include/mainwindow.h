#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <include/project_dialog.h>
#include <QWidget>
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



private slots:
    void on_pushButton_new_project_clicked();

    void on_actionImport_triggered();

    void on_pushButton_new_employee_clicked();

private:

    // new project creation window
    Dialog *newproj;
    // new employee recuirtement window
    EmployeeDialog *newempl;
    // main UI
    Ui::MainWindow *ui;


    // Inside Out's team
    Team team;
};

#endif // MAINWINDOW_H
