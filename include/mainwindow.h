#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <include/dialog.h>
#include <QWidget>

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

private:

    Dialog *newproj;
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
