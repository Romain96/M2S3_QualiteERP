#include "include/date_dialog.h"
#include "ui_date_dialog.h"

#include <iostream>

DateDialog::DateDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DateDialog)
{
    ui->setupUi(this);
}

DateDialog::~DateDialog()
{
    delete ui;
}

/*
 * checks date validity then sends date to mainwindow
 */
void DateDialog::on_buttonBox_accepted()
{
    int year = ui->lineEdit_year->text().toInt();
    int month = ui->lineEdit_month->text().toInt();
    int day = ui->lineEdit_day->text().toInt();

    // checling values
    if (month < 1)
        month = 1;
    else if (month > 12)
        month = 12;

    if (day < 1)
        day = 0;
    else if (day > 31)
        day = 31;

    if (month == 2 && day > 28)
    {
        if (day > 28)
            day = 28;
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11)
    {
        if (day > 30)
            day = 30;
    }

    if (year < 1)
        year = 1;

    emit starting_date_send_new_date(year, month, day);

    close();
}

/*
 * rejection
 */
void DateDialog::on_buttonBox_rejected()
{
    std::cerr << "DateDialog ERROR : starting date change aborted !" << std::endl;
    close();
}
