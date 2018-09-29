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

private:
    Ui::EmployeeDialog *ui;
};

#endif // EMPLOYEE_DIALOG_H
