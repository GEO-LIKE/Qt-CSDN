#include "mainwindow.h"
#include "ui_mainwindow.h"

#define PLUGIN_SUBFOLDER "/plugins/"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(this,SIGNAL(pluginLoaded()),this,SLOT(on_pluginLoaded()));
    getPluginList();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pluginLoaded()
{
    QAction* pluginAction = new QAction(tr("&open"),this);
    QPixmap p(100,100);
    QPainter painter(&p);
    painter.drawText(QRectF(0,0,100,100),tr("Qt"));
    pluginAction->setIcon(p);
    connect(pluginAction,SIGNAL(triggered()),this,SLOT(on_btnRect_clicked()));
    QToolBar *toolBar = addToolBar(tr("tool bar"));
    toolBar->addAction(pluginAction);


}

void MainWindow::getPluginList()
{
    QDir pluginsDir(qApp->applicationDirPath() +
                    PLUGIN_SUBFOLDER);
    QFileInfoList plugins = pluginsDir.entryInfoList(
                QDir::NoDotAndDotDot |
                QDir::Files,
                QDir::Name);
    foreach (QFileInfo plugin, plugins) {
        if(QLibrary::isLibrary(plugin.absoluteFilePath())){
            QPluginLoader pluginLoader(plugin.absoluteFilePath(),this);
            if(dynamic_cast<ShapePluginInterface*>(pluginLoader.instance())) {
                ui->pluginList->addItem(plugin.fileName());
                ShapePluginInterface *shape_plugin =
                        dynamic_cast<ShapePluginInterface*>(pluginLoader.instance());
                shape_plugin->initialization(this);
//                pluginLoader.unload();
                emit pluginLoaded();
            }
            else{
                QMessageBox::warning(
                            this,tr("Warring"),
                            QString(tr("Make sure %1 is a coorrect"
                                       "plugin for this application<br>"
                                       "and it's not in use by some other"
                                       "application!").arg(plugin.fileName())));

            }
        }
        else{
            QMessageBox::warning(this, tr("Warning"),
                            QString(tr("Make sure only plugins"
                                " exist in plugins folder.<br>"
                                "%1 is not a plugin."))
                                .arg(plugin.fileName()));
        }
        if(ui->pluginList->count() <= 0)
                  {
                    QMessageBox::critical(this, tr("No Plugins"),
                    tr("This application cannot work without plugins!"
                    "<br>Make sure that filter_plugins folder exists "
                    "in the same folder as the application<br>and that "
                    "there are some filter plugins inside it"));
                    this->setEnabled(false);
                  }
    }
}

void MainWindow::on_btnRect_clicked()
{
    if(ui->pluginList->count() >= 0){
        QPluginLoader pluginLoader(qApp->applicationDirPath() +
                                   PLUGIN_SUBFOLDER +
                                   ui->pluginList->currentItem()->text());
        ShapePluginInterface *plugin =
                dynamic_cast<ShapePluginInterface*>(pluginLoader.instance());
        if(plugin){
            plugin->generateShape("Rect");
        }
        else{
            QMessageBox::warning(this,tr("warning"),
                                 QString(tr("Make Sure plugin is complete.")));
        }

    }
    else
    {
        QMessageBox::warning(this, tr("Warning"),
                             QString(tr( "First select a filter plugin from the list." )));
    }
}

void MainWindow::on_btnCircle_clicked()
{
    if(ui->pluginList->count() >= 0){
        QPluginLoader pluginLoader(qApp->applicationDirPath() +
                                   PLUGIN_SUBFOLDER +
                                   ui->pluginList->currentItem()->text());
        ShapePluginInterface *plugin =
                dynamic_cast<ShapePluginInterface*>(pluginLoader.instance());
        if(plugin){
            plugin->generateShape("Circle");
        }
        else{
            QMessageBox::warning(this,tr("warning"),
                                 QString(tr("Make Sure plugin is complete.")));
        }

    }
    else
    {
        QMessageBox::warning(this, tr("Warning"),
                             QString(tr( "First select a filter plugin from the list." )));
    }
}

