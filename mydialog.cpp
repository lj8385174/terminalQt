#include "mydialog.h"
#include "ui_mydialog.h"

#include "chartview.h"

#include "chart.h"
#include "chartview.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCore/QtMath>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>

#include <QTimer>

QT_CHARTS_USE_NAMESPACE

MyDialog::MyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MyDialog)
{
    ui->setupUi(this);

    i = 0;
    alsData = new QtCharts::QLineSeries();
    chart = new Chart();
    mGraphWindow = new QMainWindow(this);
    createGraph();

    //Timer to update the graph
    //QTimer *timer = new QTimer();
    //connect(timer, SIGNAL(timeout()), this, SLOT(on_Update_clicked()));
    //timer->start(1000);
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
    //quint8 s3,s2,s1,s0;
    //s3 = dataStream.at(3);
    //s2 = dataStream.at(4);
    //s1 = dataStream.at(5);
    //s0 = dataStream.at(6);
    //quint32 sum = s3*16777216 + s2*65536 + s1*256 + s0;
    //quint32 Sachnummer = sum;

    //set ui labels
    ui->plainTextEdit->setPlainText(MyDialog::dataStream.toHex('-').toUpper());

    ui->label_bytes->setText(tr("Bytes: %1").arg(QString::number(dataStream.at(2))));
    //ui->label_version->setText(tr("Version: %1").arg(QString::number(dataStream.at(7))));
    //ui->label_sachnummer->setText(tr("Sachnummer: %1").arg(QString::number(Sachnummer)));

    QByteArray temp = dataStream;
    QString gugus = dataStream.toHex().toUpper();

    quint8 B3 = dataStream.at(3);
    quint8 B4 = dataStream.at(4);
    quint8 B5 = dataStream.at(5);


    quint8 CommandByte  = B3;
    quint8 DataByteHigh = B4;
    quint8 DataByteLow  = B5;

    ui->label_byte1->setText("CommandByte : " + QString::number(CommandByte));
    ui->label_byte2->setText("DataByteHigh: " + QString::number(DataByteHigh));
    ui->label_byte3->setText("DataByteLow : " + QString::number(DataByteLow));

    static QString EventList = "";

    if (CommandByte == 0x00)
    {
        quint16 LightMeasurement = (quint16)DataByteHigh;
        LightMeasurement = (LightMeasurement << 8);
        LightMeasurement = (LightMeasurement | (quint16)DataByteLow);
        LightMeasurement = (LightMeasurement & 0xFFFE)>>1;
        quint8 Nachkommastellen = (quint8)(LightMeasurement & 0x00F);
        LightMeasurement = (LightMeasurement & 0x7FF0)>>4;
        ui->LightMeasurement->setText(QString::number(LightMeasurement)+" lx");

        float Value = LightMeasurement;
        if (Nachkommastellen & 0x01) Value = Value + 0.0625;
        if (Nachkommastellen & 0x02) Value = Value + 0.1250;
        if (Nachkommastellen & 0x04) Value = Value + 0.2500;
        if (Nachkommastellen & 0x08) Value = Value + 0.5000;
        alsData->append((qreal)i,(qreal)Value);

        ui->LightMeasurement->setText(QString::number(Value,'f',4)+" lx");

        quint8 Motion =  (DataByteLow & 0x01);
        if (Motion == 0x01)
        {
            ui->Motion->setText("Motion");
        }
        else
        {
            ui->Motion->setText("-");
        }
    }
    else if (CommandByte == 0x01)
    {
        QString Event;
        if (DataByteLow == 0x00) Event = "Short Push";
        if (DataByteLow == 0x01) Event = "Double Click";
        if (DataByteLow == 0x02) Event = "Longpush";
        if (DataByteLow == 0x03) Event = "Ultra Longpush";
        ui->Motion->setText(Event);

        if (EventList.size() > 100) EventList = "";

        EventList.append(Event + "\n");
        ui->EventList->setPlainText(EventList);

    }
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
                tmp = buffer.mid(start,lengthOfStream);

                MyDialog::dataStream = tmp;
                ui->plainTextEdit->setPlainText(tmp.toHex().toUpper());

                MyDialog::updateValue();
                //TODO: Plausiblitätscheck

                //add data to q line series data
                //quint8 highByte, lowByte;
                //highByte = dataStream.at(12);
                //lowByte = dataStream.at(13);
                //quint32 sum = highByte*256 + lowByte;
                //alsData->append((qreal)i,(qreal)sum);


                tmp.clear();
                buffer.clear();
            }
        }
    }
}



void MyDialog::on_pushButton_clicked()
{
    //createRandomData();
    createGraph();
    mGraphWindow->show();
}

void MyDialog::createGraph()
{
    //create some data to show...

    //sine demonstration
    //QLineSeries *series = new QLineSeries();
    //for (int i = 0; i < 500; i++) {
    //    QPointF p((qreal) i, qSin(M_PI / 50 * i) * 30 + (qrand()/2147483647));
    //    p.ry() += qrand() % 20;
    //    *series << p;
    //}

    chart->removeSeries(alsData);

    chart->addSeries(alsData); //was series
    chart->setTitle("Zoom in/out example");
    //chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->legend()->hide();
    chart->createDefaultAxes();

    ChartView *chartView = new ChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    mGraphWindow->setCentralWidget(chartView);
    mGraphWindow->resize(400, 300);
    mGraphWindow->grabGesture(Qt::PanGesture);
    mGraphWindow->grabGesture(Qt::PinchGesture);
}

void MyDialog::on_ResetButton_clicked()
{
    i = 0;
    ui->label->setText("0");
    ui->plainTextEdit->setPlainText("-");

}

void MyDialog::on_Update_clicked()
{
    //mGraphWindow->repaint();
    createGraph();
    mGraphWindow->update();
    //mGraphWindow->show();
}
