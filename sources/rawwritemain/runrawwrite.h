#ifndef RUNRAWWRITE_H
#define RUNRAWWRITE_H

#include <QObject>

class QFile;
class RawwriteInfo;
class RunRawwrite : public QObject
{
    Q_OBJECT
public:
    explicit RunRawwrite(RawwriteInfo *writeinfo,QObject *parent = nullptr);
    ~RunRawwrite();
signals:
    void rawwritestarted();
    void rawwritesuccess();
    void rawwritefailed(const QString& error);
    void readstarted();
    void writestarted();
public slots:
    void rawwrite();
private:
    QFile *infile;
    QFile *outfile;
    RawwriteInfo *info;
};
#endif // RUNRAWWRITE_H
