#ifndef RESULT_DIALOG_H
#define RESULT_DIALOG_H

#include <QDialog>

namespace Ui {
class Result_Dialog;
}

class Result_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Result_Dialog(QWidget *parent = 0);
    ~Result_Dialog();
    void on_pushButton_clicked();
    void display_result(std::string res);

private slots:
    void on_ok_clicked();

private:
    Ui::Result_Dialog *ui;
};

#endif // RESULT_DIALOG_H
