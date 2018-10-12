#include "include/result_dialog.h"
#include "ui_result_dialog.h"

Result_Dialog::Result_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Result_Dialog)
{
    ui->setupUi(this);
}

Result_Dialog::~Result_Dialog()
{
    delete ui;
}


void Result_Dialog::display_result(std::string res){
    ui->display_result_browser->setText(QString::fromStdString(res));

}

void Result_Dialog::on_ok_clicked()
{
    close();
}
