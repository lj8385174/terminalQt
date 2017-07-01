#ifndef MYDIALOG_H
#define MYDIALOG_H

#include <QDialog>

namespace Ui {
class MyDialog;
}

class MyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MyDialog(QWidget *parent = 0);
    void setValue(int val);
    int getValue();
    void updateValue();
    ~MyDialog();

private slots:
    void on_pushButton_clicked();

    void on_Reset_clicked();

private:
    Ui::MyDialog *ui;
    int i;
};

//inline implementation

inline void MyDialog::setValue(int val)
{
    i = val;
}

inline int MyDialog::getValue()
{
    return i;
}


#endif // MYDIALOG_H
