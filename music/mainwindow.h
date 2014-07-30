#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlaylist>
#include<QMediaPlayer>
#include<QFile>
#include<QTextStream>
#include<list>
#include<string>
using namespace std;
namespace Ui {
class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void addsongs();
    void previous();
    void next();
    void pauseOrplay();
    void setDanQu();
    void setShunXu();
private slots:
    void on_actionAbout_me_triggered();

    void on_actionImport_song_triggered();

    void on_actionPrevious_triggered();

    void on_actionNext_triggered();

    void on_actionPause_triggered();

    void on_actionDanquxunhuang_triggered();

    void on_actionShunxubofang_triggered();

    void on_actionExit_triggered();

    void on_actionRadom_triggered();

    void on_tableWidget_cellClicked(int row, int column);

    void on_tableWidget_cellDoubleClicked(int row, int column);

    void on_jindutiaojie_sliderMoved(int position);

    void on_shengyintiaojie_sliderMoved(int position);

    void on_shengyintiaojie_valueChanged(int value);

    void on_jindutiaojie_valueChanged(int value);

    void on_actionAbout_triggered();

private:
    Ui::MainWindow *ui;
    QMediaPlayer *player;
    QMediaPlaylist *playerList;
    bool playOrpause;
    int volume;
    list<QString> stringlist;
};

#endif // MAINWINDOW_H
