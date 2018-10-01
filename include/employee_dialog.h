#ifndef EMPLOYEE_DIALOG_H
#define EMPLOYEE_DIALOG_H

#include <QDialog>

namespace Ui {
class EmployeeDialog;
}

class EmployeeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EmployeeDialog(QWidget *parent = 0);
    ~EmployeeDialog();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

signals:
    void employee_creation_send_data(std::string employee_name,
                                     int employee_job,
                                     int employee_year,
                                     int employee_month,
                                     int employee_day);

private:
    Ui::EmployeeDialog *ui;
};

#endif // EMPLOYEE_DIALOG_H
