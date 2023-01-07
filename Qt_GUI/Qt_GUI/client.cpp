#include "client.h"

Client::Client(QObject *parent):
    QThread(parent)
{

}

void Client::run()
{
    qDebug() << "start process thread";
    int mode = checkMode();
    if(mode == 1)
    {
        pipeInit();
    }
    running_flag = true;
    while(running_flag)
    {
        if(mode == 1)
        {
            readPipe();
        }
        else
        {
            processRequest();
        }
    }
    qDebug() << "end process thread";
}


void Client::pipeInit()
{
    read_pipe = GetStdHandle(STD_INPUT_HANDLE);
    write_pipe = GetStdHandle(STD_OUTPUT_HANDLE);
    if(INVALID_HANDLE_VALUE == read_pipe || INVALID_HANDLE_VALUE == write_pipe)
    {
        qDebug() << "Get pipe handle error";
        CloseHandle(read_pipe);
        CloseHandle(write_pipe);
    }
}

void Client::readPipe()
{
    TCHAR data[4096] = {0};
    DWORD data_read;
    memset(data, 0, sizeof(data));
    if(ReadFile(read_pipe, data, 4096, &data_read, NULL))
    {
        data_lock.lock();
        if(data_read == 0)
            return;
        QByteArray qba;
//        QString str_show = "";
        qba.append(data, data_read);
        img_arr.append(data, data_read);
        byte_read += data_read;
        if(packet_count == 0)
        {
            QByteArray qba1 = qba.left(20);
            QList list = qba1.split(0x00);
            QByteArray qba2 = list[0];
            QList list1 = qba2.split(',');
            img_shape.width = list1[0].toInt();
            img_shape.height = list1[1].toInt();
            img_shape.depth = list1[2].toInt();
            img_shape.size = img_shape.width*img_shape.height*img_shape.depth;
            emit client_shape(img_shape);
        }

        if(byte_read >= img_shape.size + 20)
        {
            img_arr = img_arr.remove(0, 20);
            img_arr = img_arr.left(img_shape.size);
//            for(int i=0; i<img_shape.size; i++)
//            {
//                str_show.append(tr("0x%1,").arg((quint8)img_arr.at(i),2,16,QLatin1Char('0')));
//            }
//            str_show.append("-----------");
            emit client_array(img_arr);
        }
        data_lock.unlock();
        packet_count++;
//        emit client_debug_message(str_show);
    }
}

void Client::clear_packet_count()
{
    packet_count = 0;
    byte_read = 0;
    img_arr.clear();
}

int Client::checkMode()
{
    int ret = 1;

    TCHAR szModule[512] = {0};
    GetModuleFileName(NULL, szModule, 512);
    std::string wstrModule(&szModule[0]);

    DWORD d_expID = 0;
    GetWindowThreadProcessId(GetShellWindow(), &d_expID);

    PROCESSENTRY32 p;
    PROCESSENTRY32 *info = &p;
    info->dwSize = sizeof(PROCESSENTRY32);
    HANDLE handlePro = NULL;

    HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if(hProcessSnap == INVALID_HANDLE_VALUE)
    {
        return 1;
    }

    BOOL bMore = Process32First(hProcessSnap, info);
    BOOL terminate = FALSE;
    while( bMore != FALSE)
    {
        if(wstrModule.find(info->szExeFile) != std::string::npos)
        {
            if(d_expID == info->th32ParentProcessID)
                ret = 0;
            else
                ret = 1;
            break;
        }
        bMore = Process32Next(hProcessSnap, info);
    }
    CloseHandle(hProcessSnap);
    return ret;
}

void Client::processRequest()
{

}

void Client::updateInst(QByteArray inst)
{
    // gui button instruction format:
    // op_code(1 byte) + param_1(4 byte) + zero(4 byte)
    // op_code(1 byte) + param_1(4 byte) + param_2(4 byte)
    DWORD data_write;
    char* data = inst.data();
    WriteFile(write_pipe, (LPCTSTR)data, 9, &data_write, NULL);

//    QString str_show;
//    str_show.append(QString::number(inst[0]));
//    str_show.append(" ");
//    str_show.append(QString::number(inst[1]));
//    str_show.append(" ");
//    str_show.append(QString::number(inst[2]));
//    str_show.append(" ");
//    str_show.append(QString::number(inst[3]));
//    str_show.append(" ");
//    str_show.append(QString::number(inst[4]));
//    str_show.append(" ");
//    str_show.append(QString::number(inst[5]));
//    str_show.append(" ");
//    str_show.append(QString::number(inst[6]));
//    str_show.append(" ");
//    str_show.append(QString::number(inst[7]));
//    str_show.append(" ");
//    str_show.append(QString::number(inst[8]));
//    str_show.append("\n");
//    emit client_debug_message(str_show);
}

void Client::closePipe()
{

}
