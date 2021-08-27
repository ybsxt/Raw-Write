#include "runrawwrite.h"
#include "rawwriteinfo.h"
#include <QFile>
#include <QByteArray>
RunRawwrite::RunRawwrite(RawwriteInfo *writeinfo,QObject *parent): QObject(parent){
    info = writeinfo;
    infile=new QFile;
    outfile=new QFile;
    connect(info,&RawwriteInfo::start,this,&RunRawwrite::rawwrite);
}
RunRawwrite::~RunRawwrite(){
    delete infile;
    delete outfile;
}
void RunRawwrite::rawwrite(){
    emit rawwritestarted();
    infile->setFileName(info->getinfile());
    outfile->setFileName(info->getoutfile());
    if(!infile->open(QIODevice::ReadOnly)){
        emit rawwritefailed(infile->errorString());
        return;
    }
    if(!outfile->open(QIODevice::ReadWrite)){
        infile->close();
        emit rawwritefailed(outfile->errorString());
        return;
    }
    if(!infile->seek(info->getifseek())){
        infile->close();
        outfile->close();
        emit rawwritefailed(infile->errorString());
        return;
    }
    if (!outfile->seek(info->getofseek())) {
        infile->close();
        outfile->close();
        emit rawwritefailed(outfile->errorString());
        return;
    }
    emit readstarted();
    QByteArray data=infile->read(info->getsize());
    if(data.isEmpty()){
        infile->close();
        outfile->close();
        emit rawwritefailed(infile->errorString());
        return;
    }
    emit writestarted();
    if(outfile->write(data)==-1){
        infile->close();
        outfile->close();
        emit rawwritefailed(outfile->errorString());
        return;
    }
    infile->close();
    outfile->close();
    emit rawwritesuccess();
    return;
}
