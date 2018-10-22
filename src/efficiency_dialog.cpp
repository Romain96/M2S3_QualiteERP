#include "include/efficiency_dialog.h"
#include "ui_efficiency_dialog.h"

#include <iostream>

EfficiencyDialog::EfficiencyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EfficiencyDialog)
{
    ui->setupUi(this);
}

EfficiencyDialog::~EfficiencyDialog()
{
    delete ui;
}

/*
 * emits the new efficiency to mainwindow
 */
void EfficiencyDialog::on_buttonBox_accepted()
{
    int efficiency = ui->lineEdit_efficiency->text().toInt();

    if (efficiency < 0)
        efficiency = 1; // let's say 1% minimum (or program will freeze and crash)

    emit team_efficiency_send_new_efficiency(efficiency);

    close();
}

/*
 * rejection
 */
void EfficiencyDialog::on_buttonBox_rejected()
{
    std::cerr << "EfficiencyDialog ERROR : efficiency change aborted !" << std::endl;
    close();
}
