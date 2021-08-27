#include "rawwriteinfo.h"
#include "runrawwrite.h"
#include <QString>
#include <QFile>
#include <QThread>

RawwriteInfo::RawwriteInfo(QObject *parent): QObject(parent)
{
    infile="";
    outfile="";
    infileseek=0;
    outfileseek=0;
    size=0;
    run=new RunRawwrite(this);
    runthread=new QThread;
    run->moveToThread(runthread);
    connect(run,&RunRawwrite::rawwritestarted,this,&RawwriteInfo::rawwritestarted);
    connect(run,&RunRawwrite::rawwritesuccess,this,&RawwriteInfo::onsuccess);
    connect(run,&RunRawwrite::rawwritefailed,this,&RawwriteInfo::onfailed);
    connect(run,&RunRawwrite::readstarted,this,&RawwriteInfo::readstarted);
    connect(run,&RunRawwrite::writestarted,this,&RawwriteInfo::writestarted);
}
RawwriteInfo::RawwriteInfo(QString infilepath,QString outfilepath,QObject* parent): QObject(parent)
{
    infile=infilepath;
    outfile=outfilepath;
    infileseek=0;
    outfileseek=0;
    size=0;
    run=new RunRawwrite(this);
    runthread=new QThread;
    run->moveToThread(runthread);
    connect(run,&RunRawwrite::rawwritestarted,this,&RawwriteInfo::rawwritestarted);
    connect(run,&RunRawwrite::rawwritesuccess,this,&RawwriteInfo::rawwritesuccess);
    connect(run,&RunRawwrite::rawwritefailed,this,&RawwriteInfo::rawwritefailed);
    connect(run,&RunRawwrite::readstarted,this,&RawwriteInfo::readstarted);
    connect(run,&RunRawwrite::writestarted,this,&RawwriteInfo::writestarted);
}
RawwriteInfo::RawwriteInfo(QString infilepath,QString outfilepath,qint64 filesize,qint64 ifseek,qint64 ofseek,QObject* parent): QObject(parent){
    infile=infilepath;
    outfile=outfilepath;
    infileseek=ifseek;
    outfileseek=ofseek;
    size=filesize;
    run=new RunRawwrite(this);
    runthread=new QThread;
    run->moveToThread(runthread);
    connect(run,&RunRawwrite::rawwritestarted,this,&RawwriteInfo::rawwritestarted);
    connect(run,&RunRawwrite::rawwritesuccess,this,&RawwriteInfo::rawwritesuccess);
    connect(run,&RunRawwrite::rawwritefailed,this,&RawwriteInfo::rawwritefailed);
    connect(run,&RunRawwrite::readstarted,this,&RawwriteInfo::readstarted);
    connect(run,&RunRawwrite::writestarted,this,&RawwriteInfo::writestarted);
}
RawwriteInfo::~RawwriteInfo(){
    delete run;
    delete runthread;
}
void RawwriteInfo::startrawwrite(){
    runthread->start();
    emit start();
}
void RawwriteInfo::setinfile(QString infilepath){
    infile=infilepath;
}
void RawwriteInfo::setoutfile(QString outfilepath){
    outfile=outfilepath;
}
QString RawwriteInfo::getinfile(){
    return infile;
}
QString RawwriteInfo::getoutfile(){
    return outfile;
}
void RawwriteInfo::setifseek(qint64 ifseek){
    infileseek=ifseek;
}
void RawwriteInfo::setofseek(qint64 ofseek){
    outfileseek=ofseek;
}
void RawwriteInfo::setsize(qint64 writesize){
    size=writesize;
}
qint64 RawwriteInfo::getifseek(){
    return infileseek;
}
qint64 RawwriteInfo::getofseek(){
    return outfileseek;
}
qint64 RawwriteInfo::getsize(){
    return size;
}
void RawwriteInfo::onsuccess(){
    runthread->exit(0);
    emit rawwritesuccess();
}
void RawwriteInfo::onfailed(const QString &error){
    runthread->exit(1);
    emit rawwritefailed(error);
}
