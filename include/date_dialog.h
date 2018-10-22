#ifndef DATE_DIALOG_H
#define DATE_DIALOG_H

#include <QDialog>

namespace Ui {
class DateDialog;
}

class DateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DateDialog(QWidget *parent = nullptr);
    ~DateDialog();

signals:
    void starting_date_send_new_date(int year, int month, int day);

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::DateDialog *ui;
};

#endif // DATE_DIALOG_H
