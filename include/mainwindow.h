#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <include/dialog.h>
#include <QWidget>
#include "include/employeedialog.h"

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
    void on_pushButton_clicked();

    void on_actionImport_triggered();

    void on_pushButton_2_clicked();

private:

    Dialog *newproj;
    EmployeeDialog *newempl;
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
