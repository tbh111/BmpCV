#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QString>
#include <QVector>
#include <QMutex>
#include <windows.h>
#include <tlhelp32.h>

typedef struct{int height; int width; int depth; int size;}shape;

class Client : public QThread
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);
    volatile bool running_flag = false;
    enum OP_CODE{FLIP_V = 0x01, FLIP_H = 0x02, RESIZE = 0x03, ROTATE = 0x04, CUT = 0x05, RECALL = 0x06, CLOSE = 0x09};
    void clear_packet_count();
protected:
    void run();
signals:
    void client_message(QString str);
    void client_array(QByteArray arr);
    void client_shape(shape s);
    void client_debug_message(QString msg);
public slots:
    void updateInst(QByteArray inst);
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
    int byte_read = 0;
    QMutex data_lock;
    shape img_shape;
};

#endif // CLIENT_H
