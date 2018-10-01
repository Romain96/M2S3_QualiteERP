#include "include/employee_dialog.h"
#include "ui_employee_dialog.h"
#include <iostream>

EmployeeDialog::EmployeeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EmployeeDialog)
{
    ui->setupUi(this);
}

EmployeeDialog::~EmployeeDialog()
{
    delete ui;
}

/*
 * When a new employee is created via the employee creation window,
 * this function is called to treat the input and validate the data
 * then the employee is added to the team by emitting a signal to the mainwindow
 */
void EmployeeDialog::on_buttonBox_accepted()
{
    // name of the employee
    std::string employee_name = ui->label_name->text().toStdString();

    // job (0 = CEO, 1 = DC, 2 = PM, 3 = DEV)
    int employee_job = ui->comboBox_type->currentIndex();

    // date of recruitement (date from which the recruitement offer is emitted)
    int employee_year = ui->lineEdit_year->text().toInt();
    int employee_month = ui->lineEdit_month->text().toInt();
    int employee_day = ui->lineEdit_day->text().toInt();

    // checking values...
    // 2018 < year (2019 by default)
    if (employee_year < 2018)
        employee_year = 2019;

    // 1 <= month <= 12
    if (employee_month < 1)
        employee_month = 1;
    else if (employee_month > 12)
        employee_month = 12;

    // 1 <= day <= 31
    if (employee_day < 1)
        employee_day = 1;
    else if (employee_day > 31)
        employee_day = 31;

    // checking day/month validity
    if (employee_month == 2)
    {
        if (employee_day > 28)
            employee_day = 28; // february => caped at 28 days
    }
    else if (employee_month == 4 || employee_month == 6 || employee_month == 9 || employee_month == 11)
    {
        if (employee_day > 30)
            employee_day = 30; // caped at 30
    }

    // sending values to mainwindow for the new employee to be added
    emit employee_creation_send_data(employee_name, employee_job, employee_year, employee_month, employee_day);
}

/*
 * When a new employee is created but the "cancel" button is pressed...no action
 */
void EmployeeDialog::on_buttonBox_rejected()
{
    // for debug purposes
    std::cerr << "Employee creation rejected !" << std::endl;
}
