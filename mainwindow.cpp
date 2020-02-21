#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_transform.h"

#include "QMessageBox"
#include "QFileDialog"
#include "hierarchy.h"
#include "inspector.h"
#include "sceneview.h"

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

    hierarchy = new Hierarchy;
    uiMainWindow->HierarchyDock->setWidget(hierarchy);


    connect(hierarchy,SIGNAL(entitySelected(int)),inspector, SLOT(onEntitySelected(int)));



}

MainWindow::~MainWindow()
{
    delete uiMainWindow;
   //delete uiTransform;
}

void MainWindow::onLoadFile()
{
    /*QMessageBox::StandardButton button = QMessageBox::question(
                this,
                "Exit app",
                "Do you want to exit?"
                );
    if(button == QMessageBox::Yes)
    {
        qApp->exit();
    }*/

    QString filepath = QFileDialog::getOpenFileName(this, "Load file");
    if(!filepath.isEmpty())
    {
        QMessageBox::information(this,"Info",filepath);
    }

}

void MainWindow::onSaveFile()
{
    QString filepath = QFileDialog::getSaveFileName(this, "Save file");
    if(!filepath.isEmpty())
    {
        QMessageBox::information(this,"Info",filepath);
    }
}
