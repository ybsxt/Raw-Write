#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

extern QString waittext;
extern QString readtext;
extern QString writetext;
extern QString successtext;
extern QString failtext;

class RawwriteInfo;
class QCloseEvent;

long long mypow(long long x, long long y);

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void browseif();
    void browseof();
    void writein();
    void ifeditchanged(const QString &path);
    void ofeditchanged(const QString &path);
    void sizetypechanged(int index);
    void sizechanged(int value);
    void passifsizechanged(int value);
    void passifsizetypechanged(int index);
    void passofsizechanged(int value);
    void passofsizetypechanged(int index);
    void start();
    void success();
    void failed(const QString &error);
    void read();
    void write();
protected:
    void closeEvent(QCloseEvent* event);
private:
    Ui::MainWindow *ui;
    RawwriteInfo* info;
    QString ifpath;
    QString ofpath;
    int size;
    int sizetype;
    int passifsize;
    int passifsizetype;
    int passofsize;
    int passofsizetype;
    bool iswriting;
    void disable();
    void enable();
};
#endif // MAINWINDOW_H
