#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMessageBox>
#include<QMediaPlaylist>
#include <QMediaContent>
#include <QMediaResource>
#include<QDir>
#include<QFileDialog>
#include <QtWidgets>
#include <QMediaPlayer>
#include <QVideoWidget>
#include<QFile>
#include<QString>
#include<string>
#include<sstream>
#include<fstream>
#include<QUrl>
using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->shengyintiaojie->setMaximum(100);
    ui->shengyintiaojie->setMinimum(0);
    ui->shengyintiaojie->setValue(volume);
    player = new QMediaPlayer;
    playerList = new QMediaPlaylist;
    volume = 80;
    player->setVolume(volume);
    ifstream in;
    in.open("F:\\QT\\music\\music.txt");
    string temp;
    while(getline(in, temp, ';')) {
        QString path = QString::fromStdString(temp);
        stringlist.push_back(path);
        playerList->addMedia(QUrl::fromLocalFile(path));
        QString fileName=path.split("\\").last();
        int rownum=ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(rownum);
        ui->tableWidget->setItem(rownum, 0, new QTableWidgetItem(fileName.split(".").front()));
        ui->tableWidget->setItem(rownum, 1, new QTableWidgetItem(fileName.split(".").last()));
        ui->tableWidget->setItem(rownum, 2, new QTableWidgetItem(path));
    }
    in.close();


    //playerList->addMedia(QUrl::fromLocalFile("F:\\04.mp3"));
    trayIcon = new QSystemTrayIcon(this);
    const QIcon icon("F:\\库\\图片\\1.jpg");
    trayIcon->setIcon(icon);
    trayIcon->setToolTip(tr("简易音乐播放器"));
    QMenu menu(this);
    menu.addAction(ui->actionPrevious);
    menu.addAction(ui->actionPause);
    menu.addAction(ui->actionNext);
    menu.addAction(ui->actionExit);
    QAction restoreAction=new QAction(tr("打开主面板"), this);
    connect(restoreAction, SIGNAL(triggered()), this, SLOT(show()));
    menu.addAction(restoreAction);
    trayIcon->setContextMenu(menu);
    trayIcon->show();


    playerList->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
    player->setPlaylist(playerList);
    playOrpause = true;
    player->play();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete player;
    delete playerList;
    ofstream out;
    out.open("F:\\QT\\music\\music.txt");
    while(!stringlist.empty()) {
        QString qtemp = stringlist.front();
        string temp = qtemp.toStdString();
        out << temp << ';';
        stringlist.pop_front();
    }
    out.close();
}

void MainWindow::on_actionAbout_me_triggered()
{
    const QUrl url("http://weibo.com/u/2673490922/home?wvr=5&lf=reg");
    const QUrl url2("https://github.com/wilbertwu");
    QDesktopServices::openUrl(url);
    QDesktopServices::openUrl(url2);
}

void MainWindow::on_actionImport_song_triggered()
{
    this->addsongs();
}

void MainWindow::on_actionPrevious_triggered()
{
    this->previous();
}

void MainWindow::on_actionNext_triggered()
{
    this->next();
}

void MainWindow::on_actionPause_triggered()
{
    this->pauseOrplay();
}

void MainWindow::on_actionDanquxunhuang_triggered()
{
    this->setDanQu();
}

void MainWindow::on_actionShunxubofang_triggered()
{
    this->setShunXu();
}



void MainWindow::previous() {
    int currentindex = playerList->currentIndex();
    if (currentindex == 0) {
        player->pause();
        playOrpause = false;
    } else {
        currentindex--;
        playerList->setCurrentIndex(currentindex);
        playOrpause = true;
        player->play();
         ui->playing->setText(tr("正在播放: %1").arg(ui->tableWidget->item(playerList->currentIndex(), 0)->text()));
    }

}
void MainWindow::next() {
    int currentindex = playerList->currentIndex();
    if (currentindex == (playerList->mediaCount()-1)) {
        playOrpause = false;
        player->pause();
    }  else {
        currentindex++;
        playerList->setCurrentIndex(currentindex);
        playOrpause = true;
        player->play();
        ui->playing->setText(tr("正在播放: %1").arg(ui->tableWidget->item(playerList->currentIndex(), 0)->text()));
    }
}
void MainWindow::addsongs() {
    QString initialName=tr("F:\\库\\music");
    QStringList pathList=QFileDialog::getOpenFileNames(this, tr("选择文件"), initialName, tr(".mp3"));
    for(int i=0; i<pathList.size(); ++i) {
        QString path=QDir::toNativeSeparators(pathList.at(i));
        if(!path.isEmpty()) {
            playerList->addMedia(QUrl::fromLocalFile(path));
            QString fileName=path.split("\\").last();
            int rownum=ui->tableWidget->rowCount();
            ui->tableWidget->insertRow(rownum);
            ui->tableWidget->setItem(rownum, 0, new QTableWidgetItem(fileName.split(".").front()));
            ui->tableWidget->setItem(rownum, 1, new QTableWidgetItem(fileName.split(".").last()));
            ui->tableWidget->setItem(rownum, 2, new QTableWidgetItem(path));
            stringlist.push_back(path);
            /*QFile file(tr("F:\\QT\\music\\music.txt"));
            file.open(QIODevice::Append);
            QTextStream textstream = file.readAll();
            textstream << tr(";") << path;
            file.close();*/
        }
    }
}
void MainWindow::pauseOrplay() {
    if (playOrpause) {
        player->pause();
        playOrpause = false;
        return;
    }  else {
        player->play();
        playOrpause = true;
        return;
    }
}
void MainWindow::setDanQu() {
    playerList->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
}

void MainWindow::setShunXu() {
    playerList->setPlaybackMode(QMediaPlaylist::Sequential);
}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}

void MainWindow::on_actionRadom_triggered()
{
    playerList->setPlaybackMode(QMediaPlaylist::Random);
}

void MainWindow::on_tableWidget_cellDoubleClicked(int row, int column)
{
    playerList->setCurrentIndex(row);
    player->play();
    ui->playing->setText(tr("正在播放: %1").arg(ui->tableWidget->item(row, 0)->text()));
}

void MainWindow::on_jindutiaojie_sliderMoved(int position)
{
    player->durationChanged(position);
}

void MainWindow::on_shengyintiaojie_sliderMoved(int position)
{
    volume = position;
    player->setVolume(volume);
}

void MainWindow::on_tableWidget_cellClicked(int row, int column)
{

}

void MainWindow::on_shengyintiaojie_valueChanged(int value)
{

}

void MainWindow::on_jindutiaojie_valueChanged(int value)
{
    player->setPosition(value);
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, tr("关于"), tr("简易音乐播放器V1.0"));
}
