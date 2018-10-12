#include "include/project_dialog.h"
#include "ui_project_dialog.h"
#include <iostream>
#include "include/project.h"

ProjectDialog::ProjectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProjectDialog)
{
    ui->setupUi(this);
}

ProjectDialog::~ProjectDialog()
{
    delete ui;
}

/*
 * When a new project is created,
 * this slot reveives the signal.
 * The project should be created here and added to the project list
 */
void ProjectDialog::on_buttonBox_accepted()
{
    // project name
    std::string project_name = ui->lineEdit_name->text().toStdString();

    // project development time
    int dev_time = ui->lineEdit_dev_time->text().toInt();

    // project management time
    int management_time = ui->lineEdit_management_time->text().toInt();

    // project deadline (3 dates yyyy-mm-dd)
    int deadline_day = ui->lineEdit_day->text().toInt();
    int deadline_month = ui->lineEdit_month->text().toInt();
    int deadline_year = ui->lineEdit_year->text().toInt();

    // checking values...
    // dev time > 0 (1 by default)
    if (dev_time < 1)
        dev_time = 1;
    // management time > 0 (1 by default)
    if (management_time < 1)
        management_time = 1;
    // deadline year <= 2019 (2019 by default)
    if (deadline_year < 2019)
        deadline_year = 2019;
    // deadline 1 <= month <= 12 (12 by default)
    if (deadline_month < 1 || deadline_month > 12)
        deadline_month = 1;
    // deadline 1 <= day <= 31 (1 by default)
    if (deadline_day < 1 || deadline_day > 31)
        deadline_day = 1;

    // checking validity of day/month
    if (deadline_month == 2)    // february = 28 (see simplifying hypothesis)
    {
        if (deadline_day > 28)
            deadline_day = 28; // capped at 28
    }
    else if (deadline_month == 2 || deadline_month == 4 || deadline_month == 6
             || deadline_month == 9 || deadline_month == 11)
    {
        if (deadline_day > 30)
            deadline_day = 30; // capped at 30
    }

    // project price (currently unused)
    int price = ui->lineEdit_price->text().toInt();

    if(price < 0)
        price = 0;

    // sending verified data
    emit project_creation_send_data(project_name, dev_time, management_time, price, deadline_year, deadline_month, deadline_day);
}

/*
 * "cancel" when creating a new project
 * has no effect for now
 */
void ProjectDialog::on_buttonBox_rejected()
{
    // debug
    std::cerr << "ProjectDialog : Employee creation aborted !" << std::endl;
}
