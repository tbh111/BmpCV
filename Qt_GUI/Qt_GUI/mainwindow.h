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

private:
    Ui::MainWindow *ui;
    Client* c;
    QImage* img_show;
    bool img_exist = false;
    bool eye_dropper_switch = false;
};
#endif // MAINWINDOW_H
