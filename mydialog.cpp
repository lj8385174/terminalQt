#include "mydialog.h"
#include "ui_mydialog.h"

MyDialog::MyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MyDialog)
{
    ui->setupUi(this);
}

MyDialog::~MyDialog()
{
    delete ui;
}

void MyDialog::updateValue()
{
    i++;
    QString tmp = QString::number(i);
    ui->label->setText(tmp);
}

void MyDialog::on_Reset_clicked()
{
    //ui->label->setText("Hallo");
    //int tmp = MyDialog::get

    //QString tmp = QString::number(i);
    //ui->label->setText(tmp);

    i = 0;
}




void MyDialog::on_pushButton_clicked()
{

}
