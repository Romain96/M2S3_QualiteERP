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

    // project price (currently unused)
    float price = ui->lineEdit_price->text().toFloat();

    emit project_creation_send_data(project_name, dev_time, management_time, deadline_year, deadline_month, deadline_day);
}
