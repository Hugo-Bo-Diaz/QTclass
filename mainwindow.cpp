#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_transform.h"

#include "QMessageBox"
#include "QFileDialog"
#include "hierarchy.h"
#include "inspector.h"
#include "sceneview.h"
#include "QJsonArray"
#include "QJsonObject"
#include "QJsonDocument"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    uiMainWindow(new Ui::MainWindow)
{
    uiMainWindow->setupUi(this);

    //create empty widget
    QWidget *widget = new QWidget();
    //execute setup
    inspector = new Inspector(widget);
    //set the widget in the dock
    uiMainWindow->InspectorDock->setWidget(widget);

    //uiTransform->PosXSpinBox->setValue(10.0);

    sceneview = new SceneView();

    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(sceneview);
    uiMainWindow->centralWidget->setLayout(layout);

    connect(uiMainWindow->LoadFileButton,SIGNAL(triggered()),this,SLOT(onLoadFile()));
    connect(uiMainWindow->SaveFileButton,SIGNAL(triggered()),this,SLOT(onSaveFile()));

    connect(uiMainWindow->actionExit,SIGNAL(triggered()),qApp,SLOT(quit()));

    connect(uiMainWindow->actionRedo,SIGNAL(triggered()),sceneview,SLOT(onRedoButton()));
    connect(uiMainWindow->actionUndo,SIGNAL(triggered()),sceneview,SLOT(onUndoButton()));

    hierarchy = new Hierarchy;
    uiMainWindow->HierarchyDock->setWidget(hierarchy);


    //HIERARCHY -> SCENE
    connect(hierarchy,SIGNAL(entitySelected(int)),sceneview, SLOT(EntitySelectedSlot(int)));
    connect(hierarchy,SIGNAL(AddEntityButtonPressed()),sceneview,SLOT(AddEntity()));
    connect(hierarchy,SIGNAL(RemoveEntityButtonPressed()),sceneview,SLOT(RemoveEntity()));
    connect(hierarchy,SIGNAL(EntityUpButtonPressed()),sceneview,SLOT(MoveEntityUp()));
    connect(hierarchy,SIGNAL(EntityDownButtonPressed()),sceneview,SLOT(MoveEntityDown()));

    connect(hierarchy,SIGNAL(SceneChange()),sceneview,SLOT(onSceneChange()));
    connect(hierarchy,SIGNAL(NameChanged(int,QString)),sceneview,SLOT(onNewName(int,QString)));

    //SCENE -> HIERARCHY
    connect(sceneview,SIGNAL(EntityAdded()),hierarchy,SLOT(AddedEntityList()));
    connect(sceneview,SIGNAL(EntityRemoved(int)),hierarchy,SLOT(RemovedEntityList(int)));
    connect(sceneview,SIGNAL(EntityMovedUp(int)),hierarchy,SLOT(EntityMovedUpList(int)));
    connect(sceneview,SIGNAL(EntityMovedDown(int)),hierarchy,SLOT(EntityMovedDownList(int)));

    //SCENE -> INSPECTOR
    connect(sceneview, SIGNAL(EntitySelected(shape*)),inspector,SLOT(onEntitySelected(shape*)));

    //INSPECTOR ->SCENE
    connect(inspector,SIGNAL(AttributeChanged(AttribType,float)),sceneview,SLOT( onAttributeChanged(AttribType,float)));
    connect(inspector,SIGNAL(ActionDone()),sceneview,SLOT(onActionDone()));

    connect(inspector,SIGNAL(SceneChange()),sceneview,SLOT(onSceneChange()));


}

MainWindow::~MainWindow()
{
    delete uiMainWindow;
   //delete uiTransform;
}

void MainWindow::onLoadFile()
{

    QString filepath = QFileDialog::getOpenFileName(this, "Load file");
    if(filepath.isEmpty())
    {
        return;
    }

    QFile loadFile(filepath);
    if(!loadFile.open(QIODevice::ReadOnly)){
        return;
    }
    sceneview->ClearScene();

    QByteArray scene = loadFile.readAll();
    QJsonDocument doc(QJsonDocument::fromJson(scene));
    QJsonArray elements = doc.array();

    for (int i=0;i<elements.size();++i) {
        sceneview->AddEntity();
    }

    for (int i=0;i<sceneview->entities.size();++i) {
        QJsonObject obj = elements[i].toObject();
        sceneview->entities[i]->name=obj["name"].toString();
        sceneview->entities[i]->type=(shapetype)obj["type"].toInt();
        sceneview->entities[i]->bstyle=(Qt::BrushStyle)obj["bstyle"].toInt();
        sceneview->entities[i]->pstyle=(Qt::PenStyle)obj["pstyle"].toInt();
        sceneview->entities[i]->SetColorFill(QColor(obj["fillcolR"].toInt(),obj["fillcolG"].toInt(),obj["fillcolB"].toInt()));;

        sceneview->entities[i]->SetColorBorder(QColor(obj["bordcolR"].toInt(),obj["bordcolG"].toInt(),obj["bordcolB"].toInt()));;

        sceneview->entities[i]->borderThickness = obj["bordthick"].toDouble();

        switch (obj["type"].toInt()) {
        case CIRCLE:
            {
                ((circle*)sceneview->entities[i])->x = obj["x"].toDouble();
                ((circle*)sceneview->entities[i])->y= obj["y"].toDouble();
                ((circle*)sceneview->entities[i])->rx= obj["rx"].toDouble();
                ((circle*)sceneview->entities[i])->ry= obj["ry"].toDouble();
            }
            break;
        case RECTANGLE:
            {
                sceneview->CircToRect((circle*)sceneview->entities[i]);
                ((rectangle*)sceneview->entities[i])->x = obj["x"].toDouble();
                ((rectangle*)sceneview->entities[i])->y= obj["y"].toDouble();
                ((rectangle*)sceneview->entities[i])->w= obj["rx"].toDouble();
                ((rectangle*)sceneview->entities[i])->h= obj["ry"].toDouble();
            }
            break;
        }

    }


}

void MainWindow::onSaveFile()
{
    QString filepath = QFileDialog::getSaveFileName(this, "Save file");
    if(filepath.isEmpty())
    {
        return;
    }

    QJsonArray scene;

    for (int i=0;i<sceneview->entities.size();++i) {
        QJsonObject obj;
        obj["name"]=sceneview->entities[i]->name;
        obj["type"]=sceneview->entities[i]->type;
        obj["bstyle"]=sceneview->entities[i]->bstyle;
        obj["pstyle"]=sceneview->entities[i]->pstyle;
        obj["fillcolR"]=sceneview->entities[i]->colorFill.red();
        obj["fillcolG"]=sceneview->entities[i]->colorFill.green();
        obj["fillcolB"]=sceneview->entities[i]->colorFill.blue();

        obj["bordcolR"]=sceneview->entities[i]->colorBorder.red();
        obj["bordcolG"]=sceneview->entities[i]->colorBorder.green();
        obj["bordcolB"]=sceneview->entities[i]->colorBorder.blue();

        obj["bordthick"]=sceneview->entities[i]->borderThickness;

        switch (sceneview->entities[i]->type) {
        case CIRCLE:
            {
                obj["x"]=((circle*)sceneview->entities[i])->x;
                obj["y"]=((circle*)sceneview->entities[i])->y;
                obj["rx"]=((circle*)sceneview->entities[i])->rx;
                obj["ry"]=((circle*)sceneview->entities[i])->ry;
            }
            break;
        case RECTANGLE:
            {
                obj["x"]=((rectangle*)sceneview->entities[i])->x;
                obj["y"]=((rectangle*)sceneview->entities[i])->y;
                obj["w"]=((rectangle*)sceneview->entities[i])->w;
                obj["h"]=((rectangle*)sceneview->entities[i])->h;
            }
            break;
        }

        scene.append(obj);
    }

    QJsonDocument doc(scene);
    QFile saveFile(filepath);
    if (!saveFile.open(QIODevice::WriteOnly)) {
             return;
         }
    saveFile.write(doc.toJson());

}
