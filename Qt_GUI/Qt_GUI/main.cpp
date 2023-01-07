#include "mainwindow.h"
#include <time.h>
#include <QApplication>
#include <QDebug>
#include <QMutex>
#include <QFile>
#include <QMessageLogContext>
#include <QDatetime>

void logger(QtMsgType type, const QMessageLogContext& context, const QString& msg);

int main(int argc, char *argv[])
{
    qInstallMessageHandler(logger);
    qDebug() << "GUI start";
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

void logger(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    // 加锁
    static QMutex mutex;
    mutex.lock();

    QByteArray localMsg = msg.toLocal8Bit();

    QString strMsg("");
    switch(type)
    {
    case QtDebugMsg:
        strMsg = QString("Debug");
        break;
    case QtWarningMsg:
        strMsg = QString("Warning");
        break;
    case QtCriticalMsg:
        strMsg = QString("Critical");
        break;
    case QtFatalMsg:
        strMsg = QString("Fatal");
        break;
    default:
        break;
    }

    // 设置输出信息格式
    QString strDateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd");
    QString strMessage = QString("[%1][%2] File:%3 Line:%4  %5")
            .arg(strDateTime).arg(strMsg).arg(context.file).arg(context.line).arg(localMsg.constData());
    // 输出信息至文件中（读写、追加形式）
    QFile file("../../log/log.txt");
    file.open(QIODevice::ReadWrite | QIODevice::Append);
    QTextStream stream(&file);
    stream << strMessage << "\r\n";
    file.flush();
    file.close();

    // 解锁
    mutex.unlock();
}
