#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"
#include "imgmgr.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_bStart_clicked();

    void on_btnGrScale_clicked();

    void on_btnSaveImg_clicked();

    void on_slLowBorder_valueChanged(int value);

    void on_slLowBorder_sliderMoved(int position);

    void on_slHighBorder_sliderMoved(int position);

    void on_slHighBorder_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    QCPBars *bars;
    QCustomPlot *graph;
    ImgMgr img;


    void InitAnHistogram(QCustomPlot *graph);
    void ShowImg(const char* name);
    void FillHist(vector<double> hist);
};

#endif // MAINWINDOW_H
