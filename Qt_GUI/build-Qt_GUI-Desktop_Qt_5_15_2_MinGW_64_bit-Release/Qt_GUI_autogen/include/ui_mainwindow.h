/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *message_label;
    QLabel *count;
    QLabel *label_image;
    QSplitter *splitter;
    QLabel *label;
    QLineEdit *line_width;
    QLabel *label_2;
    QLineEdit *line_height;
    QLabel *label_3;
    QLineEdit *line_depth;
    QLabel *label_4;
    QLineEdit *line_size;
    QPushButton *EyeDropper_button;
    QPushButton *Flip_h_button;
    QPushButton *Flip_v_button;
    QPushButton *Save_button;
    QTextEdit *debugEdit;
    QLineEdit *R_edit;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_5;
    QLabel *label_9;
    QLabel *label_10;
    QLineEdit *G_edit;
    QLineEdit *B_edit;
    QLineEdit *X_edit;
    QLineEdit *Y_edit;
    QPushButton *Larger_button;
    QPushButton *Smaller_button;
    QPushButton *Rotate_button;
    QPushButton *Roi_button;
    QSlider *horizontalSlider;
    QLabel *Slide_label;
    QPushButton *Recall_button;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(900, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        message_label = new QLabel(centralwidget);
        message_label->setObjectName(QString::fromUtf8("message_label"));
        message_label->setGeometry(QRect(760, 10, 121, 31));
        message_label->setFrameShape(QFrame::Panel);
        message_label->setFrameShadow(QFrame::Raised);
        count = new QLabel(centralwidget);
        count->setObjectName(QString::fromUtf8("count"));
        count->setGeometry(QRect(110, 190, 53, 16));
        label_image = new QLabel(centralwidget);
        label_image->setObjectName(QString::fromUtf8("label_image"));
        label_image->setGeometry(QRect(10, 120, 630, 400));
        label_image->setFrameShape(QFrame::Box);
        label_image->setFrameShadow(QFrame::Sunken);
        splitter = new QSplitter(centralwidget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setGeometry(QRect(30, 80, 744, 21));
        splitter->setOrientation(Qt::Horizontal);
        label = new QLabel(splitter);
        label->setObjectName(QString::fromUtf8("label"));
        splitter->addWidget(label);
        line_width = new QLineEdit(splitter);
        line_width->setObjectName(QString::fromUtf8("line_width"));
        splitter->addWidget(line_width);
        label_2 = new QLabel(splitter);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        splitter->addWidget(label_2);
        line_height = new QLineEdit(splitter);
        line_height->setObjectName(QString::fromUtf8("line_height"));
        splitter->addWidget(line_height);
        label_3 = new QLabel(splitter);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        splitter->addWidget(label_3);
        line_depth = new QLineEdit(splitter);
        line_depth->setObjectName(QString::fromUtf8("line_depth"));
        splitter->addWidget(line_depth);
        label_4 = new QLabel(splitter);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        splitter->addWidget(label_4);
        line_size = new QLineEdit(splitter);
        line_size->setObjectName(QString::fromUtf8("line_size"));
        splitter->addWidget(line_size);
        EyeDropper_button = new QPushButton(centralwidget);
        EyeDropper_button->setObjectName(QString::fromUtf8("EyeDropper_button"));
        EyeDropper_button->setGeometry(QRect(210, 10, 40, 40));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/new/prefix1/resources/Eyedropper.svg"), QSize(), QIcon::Normal, QIcon::Off);
        icon.addFile(QString::fromUtf8(":/new/prefix1/resources/Eyedropper.svg"), QSize(), QIcon::Normal, QIcon::On);
        EyeDropper_button->setIcon(icon);
        EyeDropper_button->setCheckable(true);
        Flip_h_button = new QPushButton(centralwidget);
        Flip_h_button->setObjectName(QString::fromUtf8("Flip_h_button"));
        Flip_h_button->setGeometry(QRect(110, 10, 40, 40));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/new/prefix1/resources/h_mirror.svg"), QSize(), QIcon::Normal, QIcon::Off);
        Flip_h_button->setIcon(icon1);
        Flip_h_button->setIconSize(QSize(20, 20));
        Flip_v_button = new QPushButton(centralwidget);
        Flip_v_button->setObjectName(QString::fromUtf8("Flip_v_button"));
        Flip_v_button->setGeometry(QRect(160, 10, 40, 40));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/new/prefix1/resources/v_mirror.svg"), QSize(), QIcon::Normal, QIcon::Off);
        Flip_v_button->setIcon(icon2);
        Flip_v_button->setIconSize(QSize(20, 20));
        Save_button = new QPushButton(centralwidget);
        Save_button->setObjectName(QString::fromUtf8("Save_button"));
        Save_button->setGeometry(QRect(10, 10, 40, 40));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/new/prefix1/resources/save.svg"), QSize(), QIcon::Normal, QIcon::Off);
        Save_button->setIcon(icon3);
        Save_button->setIconSize(QSize(20, 20));
        debugEdit = new QTextEdit(centralwidget);
        debugEdit->setObjectName(QString::fromUtf8("debugEdit"));
        debugEdit->setGeometry(QRect(660, 120, 231, 401));
        R_edit = new QLineEdit(centralwidget);
        R_edit->setObjectName(QString::fromUtf8("R_edit"));
        R_edit->setGeometry(QRect(30, 530, 71, 21));
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(125, 530, 9, 21));
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(235, 530, 8, 21));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(15, 530, 8, 21));
        label_9 = new QLabel(centralwidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(345, 530, 8, 21));
        label_10 = new QLabel(centralwidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(455, 530, 8, 21));
        G_edit = new QLineEdit(centralwidget);
        G_edit->setObjectName(QString::fromUtf8("G_edit"));
        G_edit->setGeometry(QRect(140, 530, 71, 21));
        B_edit = new QLineEdit(centralwidget);
        B_edit->setObjectName(QString::fromUtf8("B_edit"));
        B_edit->setGeometry(QRect(250, 530, 71, 21));
        X_edit = new QLineEdit(centralwidget);
        X_edit->setObjectName(QString::fromUtf8("X_edit"));
        X_edit->setGeometry(QRect(360, 530, 71, 21));
        Y_edit = new QLineEdit(centralwidget);
        Y_edit->setObjectName(QString::fromUtf8("Y_edit"));
        Y_edit->setGeometry(QRect(470, 530, 71, 21));
        Larger_button = new QPushButton(centralwidget);
        Larger_button->setObjectName(QString::fromUtf8("Larger_button"));
        Larger_button->setGeometry(QRect(260, 10, 40, 40));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/new/prefix1/resources/larger.svg"), QSize(), QIcon::Normal, QIcon::Off);
        icon4.addFile(QString::fromUtf8(":/new/prefix1/resources/Eyedropper.svg"), QSize(), QIcon::Normal, QIcon::On);
        Larger_button->setIcon(icon4);
        Larger_button->setCheckable(false);
        Smaller_button = new QPushButton(centralwidget);
        Smaller_button->setObjectName(QString::fromUtf8("Smaller_button"));
        Smaller_button->setGeometry(QRect(310, 10, 40, 40));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/new/prefix1/resources/smaller.svg"), QSize(), QIcon::Normal, QIcon::Off);
        icon5.addFile(QString::fromUtf8(":/new/prefix1/resources/Eyedropper.svg"), QSize(), QIcon::Normal, QIcon::On);
        Smaller_button->setIcon(icon5);
        Smaller_button->setCheckable(false);
        Rotate_button = new QPushButton(centralwidget);
        Rotate_button->setObjectName(QString::fromUtf8("Rotate_button"));
        Rotate_button->setGeometry(QRect(360, 10, 40, 40));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/new/prefix1/resources/rotate.svg"), QSize(), QIcon::Normal, QIcon::Off);
        Rotate_button->setIcon(icon6);
        Rotate_button->setIconSize(QSize(22, 22));
        Rotate_button->setCheckable(true);
        Roi_button = new QPushButton(centralwidget);
        Roi_button->setObjectName(QString::fromUtf8("Roi_button"));
        Roi_button->setGeometry(QRect(410, 10, 40, 40));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/new/prefix1/resources/roi.svg"), QSize(), QIcon::Normal, QIcon::Off);
        Roi_button->setIcon(icon7);
        Roi_button->setIconSize(QSize(18, 18));
        Roi_button->setCheckable(true);
        horizontalSlider = new QSlider(centralwidget);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setEnabled(true);
        horizontalSlider->setGeometry(QRect(480, 20, 160, 22));
        horizontalSlider->setMinimum(0);
        horizontalSlider->setMaximum(360);
        horizontalSlider->setValue(180);
        horizontalSlider->setOrientation(Qt::Horizontal);
        Slide_label = new QLabel(centralwidget);
        Slide_label->setObjectName(QString::fromUtf8("Slide_label"));
        Slide_label->setGeometry(QRect(600, 20, 53, 16));
        Recall_button = new QPushButton(centralwidget);
        Recall_button->setObjectName(QString::fromUtf8("Recall_button"));
        Recall_button->setGeometry(QRect(60, 10, 40, 40));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/new/prefix1/resources/recall.svg"), QSize(), QIcon::Normal, QIcon::Off);
        Recall_button->setIcon(icon8);
        Recall_button->setIconSize(QSize(20, 20));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 900, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
#if QT_CONFIG(whatsthis)
        MainWindow->setWhatsThis(QString());
#endif // QT_CONFIG(whatsthis)
        message_label->setText(QCoreApplication::translate("MainWindow", "Status: IDLE", nullptr));
        count->setText(QString());
        label_image->setText(QString());
        label->setText(QCoreApplication::translate("MainWindow", "width", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "height", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "depth", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "size", nullptr));
#if QT_CONFIG(tooltip)
        EyeDropper_button->setToolTip(QCoreApplication::translate("MainWindow", "\345\217\226\350\211\262\345\231\250", nullptr));
#endif // QT_CONFIG(tooltip)
        EyeDropper_button->setText(QString());
#if QT_CONFIG(tooltip)
        Flip_h_button->setToolTip(QCoreApplication::translate("MainWindow", "\346\260\264\345\271\263\351\225\234\345\203\217", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        Flip_h_button->setWhatsThis(QString());
#endif // QT_CONFIG(whatsthis)
        Flip_h_button->setText(QString());
#if QT_CONFIG(tooltip)
        Flip_v_button->setToolTip(QCoreApplication::translate("MainWindow", "\345\236\202\347\233\264\351\225\234\345\203\217", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        Flip_v_button->setWhatsThis(QString());
#endif // QT_CONFIG(whatsthis)
        Flip_v_button->setText(QString());
#if QT_CONFIG(tooltip)
        Save_button->setToolTip(QCoreApplication::translate("MainWindow", "\344\277\235\345\255\230", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        Save_button->setWhatsThis(QString());
#endif // QT_CONFIG(whatsthis)
        Save_button->setText(QString());
        label_6->setText(QCoreApplication::translate("MainWindow", "G", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "B", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "R", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "X", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "Y", nullptr));
#if QT_CONFIG(tooltip)
        Larger_button->setToolTip(QCoreApplication::translate("MainWindow", "\346\224\276\345\244\247", nullptr));
#endif // QT_CONFIG(tooltip)
        Larger_button->setText(QString());
#if QT_CONFIG(tooltip)
        Smaller_button->setToolTip(QCoreApplication::translate("MainWindow", "\347\274\251\345\260\217", nullptr));
#endif // QT_CONFIG(tooltip)
        Smaller_button->setText(QString());
#if QT_CONFIG(tooltip)
        Rotate_button->setToolTip(QCoreApplication::translate("MainWindow", "\346\227\213\350\275\254", nullptr));
#endif // QT_CONFIG(tooltip)
        Rotate_button->setText(QString());
#if QT_CONFIG(tooltip)
        Roi_button->setToolTip(QCoreApplication::translate("MainWindow", "\350\243\201\345\211\252", nullptr));
#endif // QT_CONFIG(tooltip)
        Roi_button->setText(QString());
        Slide_label->setText(QString());
#if QT_CONFIG(tooltip)
        Recall_button->setToolTip(QCoreApplication::translate("MainWindow", "\346\201\242\345\244\215\345\216\237\345\233\276", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        Recall_button->setWhatsThis(QString());
#endif // QT_CONFIG(whatsthis)
        Recall_button->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
