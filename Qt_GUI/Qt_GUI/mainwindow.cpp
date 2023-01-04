#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    c = new Client;
    qRegisterMetaType<shape>("shape");
    connect(c, SIGNAL(client_debug_message(QString)), this, SLOT(update_message(QString)));
    connect(c, SIGNAL(client_array(QByteArray)), this, SLOT(draw_img(QByteArray)));
    connect(c, SIGNAL(client_shape(shape)), this, SLOT(update_text(shape)));
    c->start();
}

MainWindow::~MainWindow()
{
    if(img_exist)
    {
        delete img_show;
    }
    c->running_flag = false;
    Sleep(100);
    delete c;
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    QPoint pt = e->pos();
    int x_pos = pt.x();
    int y_pos = pt.y();
    if(ui->EyeDropper_button->isChecked() && img_exist)
    {
        QPixmap pixmap = ui->label_image->pixmap(Qt::ReturnByValue);
        double scale_ratio_w = pixmap.width() / double(img_show->width());
        double scale_ratio_h = pixmap.height() / double(img_show->height());

        QPoint pt_img(int((x_pos - ui->label_image->x())/scale_ratio_w), int((y_pos - ui->label_image->y())/scale_ratio_h));
//        ui->debugEdit->append(QString::number(pixmap.width()) + " " + QString::number(pixmap.height()));
//        ui->debugEdit->append(QString::number(scale_ratio_w) + " " + QString::number(scale_ratio_h));
//        ui->debugEdit->append(QString::number(pt_img.x()) + " " + QString::number(pt_img.y()));
//        ui->debugEdit->append("\n");
        if(pt_img.x() >= 0 && pt_img.y() >= 0 &&
           pt_img.x() < img_show->width() && pt_img.y() < img_show->height())
        {
            QColor color = img_show->pixel(pt_img);
            ui->R_edit->setText(QString::number(color.red()));
            ui->G_edit->setText(QString::number(color.green()));
            ui->B_edit->setText(QString::number(color.blue()));
            ui->X_edit->setText(QString::number(pt_img.x()));
            ui->Y_edit->setText(QString::number(pt_img.y()));
            ui->debugEdit->append("R: " + QString::number(color.red()) +
                                  " G: " + QString::number(color.green()) +
                                  " B: " + QString::number(color.blue()) +
                                  " X: " + QString::number(pt_img.x()) +
                                  " Y: " + QString::number(pt_img.y()));
        }

    }
}

void MainWindow::closeEvent(QCloseEvent *e)
{

}

void MainWindow::update_message(QString message)
{
     ui->debugEdit->append(message);
}

void MainWindow::draw_img(QByteArray arr)
{
    ui->message_label->setText("done");
    long size = ui->line_size->text().toInt();
//    QString str;
    if(img_show->format() == QImage::Format_RGB888)
    {
        for(int i=0; i<size; i=i+3)
        {

    //        str.append(tr("0x%1,").arg((quint8)arr.at(i),2,16,QLatin1Char('0')));
    //        str.append(tr("0x%1,").arg((quint8)arr.at(i+1),2,16,QLatin1Char('0')));
    //        str.append(tr("0x%1,").arg((quint8)arr.at(i+2),2,16,QLatin1Char('0')));
    //        str.append("\n");

            img_show->bits()[i] = arr[i+2]; // BGR to RGB
            img_show->bits()[i+1] = arr[i+1];
            img_show->bits()[i+2] = arr[i];
        }
    }
    else
    {
        for(int i=0; i<size; i++)
        {

    //        str.append(tr("0x%1,").arg((quint8)arr.at(i),2,16,QLatin1Char('0')));
    //        str.append(tr("0x%1,").arg((quint8)arr.at(i+1),2,16,QLatin1Char('0')));
    //        str.append(tr("0x%1,").arg((quint8)arr.at(i+2),2,16,QLatin1Char('0')));
    //        str.append("\n");

            img_show->bits()[i] = arr[i];

        }
    }

    QPixmap pixmap = QPixmap::fromImage((*img_show).scaled(ui->label_image->size(), Qt::KeepAspectRatio));
    ui->label_image->setPixmap(pixmap);
//    ui->debugEdit->setText(str);
}

void MainWindow::update_text(shape s)
{
    ui->line_width->setText(QString::number(s.width));
    ui->line_height->setText(QString::number(s.height));
    ui->line_depth->setText(QString::number(s.depth));
    ui->line_size->setText(QString::number(s.size));
    if(s.depth == 3)
        img_show = new QImage(s.width, s.height, QImage::Format_RGB888);
    else
        img_show = new QImage(s.width, s.height, QImage::Format_Grayscale8);
    img_exist = true;
}

void MainWindow::on_EyeDropper_button_clicked(bool checked)
{
    qDebug() << checked;
}

void MainWindow::on_Save_button_clicked()
{
    QString save_path = QFileDialog::getSaveFileName(this, tr("请选择保存路径"), ".", tr("BMP files(*.bmp)"));
    if(img_exist && !save_path.isNull())
    {
        img_show->save(save_path);
    }
}

