#ifndef BASICSHAPEPLUGIN_H
#define BASICSHAPEPLUGIN_H

#include "basicshapeplugin_global.h"
#include "shapeplugininterface.h"
#include <QtPlugin>
#include <QDebug>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QAction>

//QT_BEGIN_NAMESPACE
//class QPainterPath;
//QT_END_NAMESPACE

class BASICSHAPEPLUGINSHARED_EXPORT BasicShapePlugin:
        public QObject,
        public ShapePluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.geolike.shapeplugininterface")
    Q_INTERFACES(ShapePluginInterface)

public:
    BasicShapePlugin();
    ~BasicShapePlugin();
    QString description();
    void generateShape(QString shapeType);
    void initialization(QMainWindow* window);

public slots:
    void on_Action_triggered();
};

#endif // BASICSHAPEPLUGIN_H
