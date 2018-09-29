#include "include/employee_dialog.h"
#include "ui_employee_dialog.h"

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
