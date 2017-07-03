#include "mydialog.h"
#include "ui_mydialog.h"

MyDialog::MyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MyDialog)
{
    ui->setupUi(this);

    i = 0;
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


    //read 'Sachnummer'
    quint8 s3,s2,s1,s0;
    s3 = dataStream.at(3);
    s2 = dataStream.at(4);
    s1 = dataStream.at(5);
    s0 = dataStream.at(6);
    quint32 sum = s3*16777216 + s2*65536 + s1*256 + s0;
    quint32 Sachnummer = sum;

    //set ui labels
    ui->plainTextEdit->setPlainText(MyDialog::dataStream.toHex('-').toUpper());

    ui->label_bytes->setText(tr("Bytes: %1").arg(QString::number(dataStream.at(2))));
    ui->label_version->setText(tr("Version: %1").arg(QString::number(dataStream.at(7))));
    ui->label_sachnummer->setText(tr("Sachnummer: %1").arg(QString::number(Sachnummer)));
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
    ui->label->setText("0");
    ui->plainTextEdit->setPlainText("-");

}
