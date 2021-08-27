#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "rawwriteinfo.h"
#include <QFileDialog>
#include <QCloseEvent>
#include <QMessageBox>

QString waittext="单击“写入”开始写入。";
QString starttext = "写入开始.";
QString readtext="正在读取输入文件。";
QString writetext="正在写入输出文件。";
QString successtext="写入成功。";
QString failtext="写入失败。";

long long mypow(long long x, long long y) {
    if (y < 0) return (-1);
    long long result = 1;
    for (long long i = 0; i < y; i++) {
        result *= x;
    }
    return result;
}
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{   
    ifpath = "";
    ofpath = "";
    size = 0;
    sizetype = 0;
    passifsize = 0;
    passifsizetype = 0;
    passofsize = 0;
    passofsizetype = 0;
    iswriting = false;
    ui->setupUi(this);
    ui->writestatu->setText(waittext);
    info = new RawwriteInfo(this);
    connect(ui->exit, &QPushButton::clicked, this, &MainWindow::close);
    connect(ui->write, &QPushButton::clicked, this, &MainWindow::writein);
    connect(ui->ifbrowse, &QPushButton::clicked, this, &MainWindow::browseif);
    connect(ui->ofbrowse, &QPushButton::clicked, this, &MainWindow::browseof);
    connect(ui->ifedit, &QLineEdit::textChanged, this, &MainWindow::ifeditchanged);
    connect(ui->ofedit, &QLineEdit::textChanged, this, &MainWindow::ofeditchanged);
    connect(ui->sizeBox, &QSpinBox::valueChanged, this, &MainWindow::sizechanged);
    connect(ui->passifsizebox, &QSpinBox::valueChanged, this, &MainWindow::passifsizechanged);
    connect(ui->passofsizebox, &QSpinBox::valueChanged, this, &MainWindow::passofsizechanged);
    connect(ui->sizetype, &QComboBox::currentIndexChanged, this, &MainWindow::sizetypechanged);
    connect(ui->passifsizetype, &QComboBox::currentIndexChanged, this, &MainWindow::passifsizetypechanged);
    connect(ui->passofsizetype, &QComboBox::currentIndexChanged, this, &MainWindow::passofsizetypechanged);
    connect(info, &RawwriteInfo::rawwritestarted, this, &MainWindow::start);
    connect(info, &RawwriteInfo::rawwritesuccess, this, &MainWindow::success);
    connect(info, &RawwriteInfo::rawwritefailed, this, &MainWindow::failed);
    connect(info, &RawwriteInfo::readstarted, this, &MainWindow::read);
    connect(info, &RawwriteInfo::writestarted, this, &MainWindow::write);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::browseif() {
    QString path = QFileDialog::getOpenFileName(this, "输入文件", ".", "所有文件(*.*)");
    path.replace("/", "\\");
    ui->ifedit->setText(path);
}

void MainWindow::browseof()
{
    QString path = QFileDialog::getOpenFileName(this, "输出文件", ".", "所有文件(*.*)");
    path.replace("/", "\\");
    ui->ofedit->setText(path);
}

void MainWindow::writein()
{
    if (QMessageBox::question(this, "Raw Write", "是否开始写入？", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes) == QMessageBox::Yes) {
        info->setinfile(ifpath);
        info->setoutfile(ofpath);
        info->setsize(size * mypow(2, sizetype * 10));
        info->setifseek(passifsize * mypow(2, passifsizetype * 10));
        info->setofseek(passofsize * mypow(2, passofsizetype * 10));
        info->startrawwrite();
    }
}

void MainWindow::ifeditchanged(const QString& path)
{
    ifpath = path;
#ifdef Q_OS_WIN
    ifpath.replace("\\", "/");
#endif
}

void MainWindow::ofeditchanged(const QString& path)
{
    ofpath = path;
#ifdef Q_OS_WIN
    ofpath.replace("\\", "/");
#endif
}

void MainWindow::sizetypechanged(int index)
{
    sizetype = index;
}

void MainWindow::sizechanged(int value)
{
    size = value;
}

void MainWindow::passifsizechanged(int value)
{
    passifsize = value;
}

void MainWindow::passifsizetypechanged(int index)
{
    passifsizetype = index;
}

void MainWindow::passofsizechanged(int value)
{
    passofsize = value;
}

void MainWindow::passofsizetypechanged(int index)
{
    passofsizetype = index;
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    if (iswriting == true) {
        QMessageBox::warning(this, "Raw Write", "正在写入,尝试关闭会导致文件损坏。");
        event->ignore();
    }
    else {
        event->accept();
    }
}

void MainWindow::start()
{
    ui->writeprogress->setValue(0);
    ui->writestatu->setText(starttext);
    disable();
}

void MainWindow::success()
{
    ui->writeprogress->setValue(100);
    ui->writestatu->setText(successtext);
    QMessageBox::information(this, "Raw Write", "写入成功。");
    enable();
    ui->writeprogress->setValue(0);
    ui->writestatu->setText(waittext);
}

void MainWindow::failed(const QString& error)
{
    ui->writeprogress->setValue(100);
    ui->writestatu->setText(failtext);
    QMessageBox::critical(this, "Raw Write", "写入失败：" + error);
    enable();
    ui->writeprogress->setValue(0);
    ui->writestatu->setText(waittext);
}

void MainWindow::read()
{
    ui->writeprogress->setValue(33);
    ui->writestatu->setText(readtext);
}

void MainWindow::write() {
    ui->writeprogress->setValue(66);
    ui->writestatu->setText(writetext);
}

void MainWindow::disable()
{
    iswriting = true;
    setCursor(Qt::WaitCursor);
    ui->ifbrowse->setDisabled(true);
    ui->ofbrowse->setDisabled(true);
    ui->ifedit->setDisabled(true);
    ui->ofedit->setDisabled(true);
    ui->sizeBox->setDisabled(true);
    ui->sizetype->setDisabled(true);
    ui->passifsizebox->setDisabled(true);
    ui->passifsizetype->setDisabled(true);
    ui->passofsizebox->setDisabled(true);
    ui->passofsizetype->setDisabled(true);
    ui->write->setDisabled(true);
    ui->exit->setDisabled(true);
}

void MainWindow::enable() {
    iswriting = false;    
    setCursor(Qt::ArrowCursor);
    ui->ifbrowse->setEnabled(true);
    ui->ofbrowse->setEnabled(true);
    ui->ifedit->setEnabled(true);
    ui->ofedit->setEnabled(true);
    ui->sizeBox->setEnabled(true);
    ui->sizetype->setEnabled(true);
    ui->passifsizebox->setEnabled(true);
    ui->passifsizetype->setEnabled(true);
    ui->passofsizebox->setEnabled(true);
    ui->passofsizetype->setEnabled(true);
    ui->write->setEnabled(true);
    ui->exit->setEnabled(true);
}