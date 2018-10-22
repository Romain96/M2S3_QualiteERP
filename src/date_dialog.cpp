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
