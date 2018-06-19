#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "shapeplugininterface.h"
#include <QPainter>
#include <QToolBar>
#include <QMainWindow>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QPluginLoader>
#include <QFileInfoList>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
signals:
    void pluginLoaded();
private slots:
    void on_pluginLoaded();

    void on_btnRect_clicked();

    void on_btnCircle_clicked();

private:
    void getPluginList();
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
