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


void MyDialog::dataBuffer(QByteArray buf)
{
    static QByteArray buffer;

    buffer.append(buf);
    //tmp.clear();
    //ui->plainTextEdit->setPlainText(buf.toHex().toUpper());

    QByteArray startValue;
    startValue[0] = 0xAA;
    startValue[1] = 0x55;

    int start = -1;
    QByteArray tmp;

    //TODO: Übertrag von letzten Bytes
    if (buffer.size() > 10)
    {
        start = buffer.indexOf(startValue);

        if ((start != (-1))&&((buffer.size()>(start+10))))
        {
            int lengthOfStream = buffer[start+2];  //byteanzahl an 2 stelle

            if(buffer.size()>=(start+lengthOfStream))
            {
                tmp = buffer.mid(start,lengthOfStream+1);

                ui->plainTextEdit->setPlainText(tmp.toHex().toUpper());
                ui->label_6->setText(QString::number(lengthOfStream));
                ui->label_7->setText(QString::number(buffer[start+2]));

                MyDialog::dataStream = tmp;
                ui->plainTextEdit->setPlainText(tmp.toHex().toUpper());

                MyDialog::updateValue();
                //TODO: Plausiblitätscheck

                tmp.clear();
                buffer.clear();
            }
        }
    }
}



void MyDialog::on_pushButton_clicked()
{

}

void MyDialog::on_ResetButton_clicked()
{
    i = 0;
    ui->plainTextEdit->setPlainText("-");
}
