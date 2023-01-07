#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QString>
#include <QMessageBox>
#include <QImage>
#include <QMouseEvent>
#include <QFileDialog>
#include <QCloseEvent>
#include <QMutex>
#include "client.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    void mousePressEvent(QMouseEvent *e);
    void closeEvent(QCloseEvent *e);
public slots:
    void update_message(QString message);
    void draw_img(QByteArray arr);
    void update_text(shape s);
private slots:
    void on_EyeDropper_button_clicked(bool checked);
    void on_Save_button_clicked();
    void on_horizontalSlider_valueChanged(int value);
    void on_Rotate_button_clicked(bool checked);
    void on_Flip_h_button_clicked();
    void on_Flip_v_button_clicked();
    void on_Larger_button_clicked();
    void on_Smaller_button_clicked();
    void on_Roi_button_clicked(bool checked);
    void on_Recall_button_clicked();

signals:
    void button_inst(QByteArray inst);
private:
    Ui::MainWindow *ui;
    Client* c;
    QImage* img_show;
    uchar* data_temp;

    bool img_exist = false;
    bool eye_dropper_switch = false;
    bool roi_switch = false;
    bool roi_pt1_flag = false;
    bool roi_pt2_flag = false;
    int32_t resize_ratio = 10;
    shape img_shape;
    QMutex img_data_lock;
};
#endif // MAINWINDOW_H
