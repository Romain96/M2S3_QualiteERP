#ifndef EFFICIENCY_DIALOG_H
#define EFFICIENCY_DIALOG_H

#include <QDialog>

namespace Ui {
class EfficiencyDialog;
}

class EfficiencyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EfficiencyDialog(QWidget *parent = nullptr);
    ~EfficiencyDialog();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

signals:
    void team_efficiency_send_new_efficiency(int efficiency);

private:
    Ui::EfficiencyDialog *ui;
};

#endif // EFFICIENCY_DIALOG_H
