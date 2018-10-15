#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include "qcustomplot.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    InitAnHistogram(ui->graph);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_bStart_clicked()
{
    img = ImgMgr("2018-10-07-144058.jpg");
    QPixmap pic(img.Name());
    ui->label->setPixmap(pic);
}

void MainWindow::InitAnHistogram(QCustomPlot *graph)
{
    this->graph = graph;

    bars = new QCPBars(graph->xAxis, graph->yAxis);
    graph->addPlottable(bars);

    bars->setPen(Qt::NoPen);

    QColor color("blue");
    bars->setBrush(color);

    graph->yAxis->setVisible(false);
    graph->yAxis->setRange(1, 20);

    graph->xAxis->setLabel("blach ---> white");
    graph->xAxis->setRange(1, 20);
    graph->xAxis->grid()->setVisible(true);
}

void MainWindow::ShowImg(const char *name)
{
    QPixmap pic(name);
    ui->label->setPixmap(pic);
}

void MainWindow::FillHist(vector<double> y)
{
    QVector<double> X(y.size());
    QVector<double> Y(y.size());
    for(int i = 0; i < X.size(); i++)
    {
        X[i] = i;
        Y[i] = y[i];
    }

    bars->setData(X, Y);
    graph->xAxis->rescale();
    graph->yAxis->rescale();
    graph->replot();
}

void MainWindow::on_btnGrScale_clicked()
{
    img.ToGrayScale();
    img.Save();
    ShowImg(img.Name());
    FillHist(img.GetBrightnessHistogram());
}

void MainWindow::on_btnSaveImg_clicked()
{
    img.Save();
}

void MainWindow::on_slLowBorder_valueChanged(int low)
{
    uint16_t high = ui->slHighBorder->value();
    img.InitBinValues(low, high);
    ui->lineLowBorder->setText(QString::number(low));
    img.ToBin();
}

void MainWindow::on_slLowBorder_sliderMoved(int low)
{
    uint16_t high = ui->slHighBorder->value();
    img.InitBinValues(low, high);
    ui->lineLowBorder->setText(QString::number(low));
    img.ToBin();
}

void MainWindow::on_slHighBorder_sliderMoved(int high)
{
    uint16_t low = ui->slLowBorder->value();
    img.InitBinValues(low, high);
    ui->lineHighBorder->setText(QString::number(high));
    img.ToBin();
}

void MainWindow::on_slHighBorder_valueChanged(int high)
{
    uint16_t low = ui->slLowBorder->value();
    img.InitBinValues(low, high);
    ui->lineHighBorder->setText(QString::number(high));
    img.ToBin();
}
