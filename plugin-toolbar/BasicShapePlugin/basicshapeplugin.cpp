#include "basicshapeplugin.h"


BasicShapePlugin::BasicShapePlugin()
{
}

BasicShapePlugin::~BasicShapePlugin()
{

}

QString BasicShapePlugin::description()
{
    return "This is a plugin to generate shapes.";
}

void BasicShapePlugin::generateShape(QString shapeType)
{
    qDebug() << shapeType;
}

void BasicShapePlugin::on_Action_triggered()
{
    qDebug() << "trigered!";
    generateShape("Action Triggered!");
}

void BasicShapePlugin::initialization(QMainWindow *window)
{
    auto *toolBar = new QToolBar;
    auto *addShapeAction = toolBar->addAction("Shapes");
    addShapeAction->setToolTip("Return a shape");
    connect(addShapeAction, &QAction::triggered, this, &BasicShapePlugin::on_Action_triggered);
    window->addToolBar(toolBar);
}




