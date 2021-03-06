#ifndef MYDIALOG_H
#define MYDIALOG_H

#include <QDialog>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QLineSeries>
#include "chartview.h"
#include "chart.h"

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
    void dataBuffer(QByteArray buffer);
    void createGraph();
    ~MyDialog();

private slots:
    void on_ResetButton_clicked();

    void on_Update_clicked();

    void on_GraphButton_clicked();

private:
    Ui::MyDialog *ui;
    int i;
    QByteArray dataStream;
    QByteArray inputBuffer;
    QMainWindow *mGraphWindow;
    QLineSeries *GraphData;
    Chart *chart;
    ChartView *chartView;

};

//inline implementations

inline void MyDialog::setValue(int val)
{
    i = val;
}

inline int MyDialog::getValue()
{
    return i;
}


#endif // MYDIALOG_H
