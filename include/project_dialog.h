#ifndef PROJECT_DIALOG_H
#define PROJECT_DIALOG_H

#include <QDialog>

namespace Ui {
class ProjectDialog;
}

class ProjectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProjectDialog(QWidget *parent = 0);
    ~ProjectDialog();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

signals:
    void project_creation_send_data(std::string project_name,
                                    int development_time,
                                    int management_time,
                                    int price,
                                    int deadline_year,
                                    int deadline_month,
                                    int deadline_day);


private:
    Ui::ProjectDialog *ui;
};

#endif // PROJECT_DIALOG_H
