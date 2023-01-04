#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QString>
#include <QVector>
#include <windows.h>
#include <tlhelp32.h>

typedef struct{int height; int width; int depth; int size;}shape;

class Client : public QThread
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);
    QVector<QString> request_queue;
    volatile bool running_flag = false;
protected:
    void run();
signals:
    void client_message(QString str);
    void client_array(QByteArray arr);
    void client_shape(shape s);
    void client_debug_message(QString msg);
public slots:
    void updateQueue();
private:
    HANDLE write_pipe;
    HANDLE read_pipe;
    void pipeInit();
    void readPipe();
    int checkMode();
    void processRequest();
    void closePipe();
    QByteArray img_arr;
    int packet_count = 0;

    shape img_shape;
};

#endif // CLIENT_H
