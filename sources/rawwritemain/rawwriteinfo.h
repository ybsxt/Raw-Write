#ifndef RAWWRITEINFO_H
#define RAWWRITEINFO_H

#include "rawwritemain_global.h"
#include <QObject>

class QString;
class QThread;
class RunRawwrite;


class RAWWRITEMAIN_EXPORT RawwriteInfo: public QObject
{
    Q_OBJECT
public:
    explicit RawwriteInfo(QObject* parent=nullptr);
    RawwriteInfo(QString infilepath,QString outfilepath,QObject* parent=nullptr);
    RawwriteInfo(QString infilepath,QString outfilepath,qint64 size,qint64 ifseek,qint64 ofseek,QObject* parent=nullptr);
    ~RawwriteInfo();
    void startrawwrite();
    void setinfile(QString infilepath);
    void setoutfile(QString outfilepath);
    QString getinfile();
    QString getoutfile();
    void setifseek(qint64 ifseek);
    void setofseek(qint64 ofseek);
    void setsize(qint64 size);
    qint64 getifseek();
    qint64 getofseek();
    qint64 getsize();
signals:
    void rawwritestarted();
    void rawwritesuccess();
    void rawwritefailed(const QString &errortext);
    void readstarted();
    void writestarted();
    void start();
public slots:
    void onsuccess();
    void onfailed(const QString &error);
private:
    QString infile;
    QString outfile;
    RunRawwrite *run;
    QThread *runthread;
    qint64 infileseek;
    qint64 outfileseek;
    qint64 size;
};

#endif // RAWWRITEINFO_H
