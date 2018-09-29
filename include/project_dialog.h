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

private:
    Ui::ProjectDialog *ui;
};

#endif // PROJECT_DIALOG_H
