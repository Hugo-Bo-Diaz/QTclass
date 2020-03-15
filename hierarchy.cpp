#include "hierarchy.h"
#include "ui_hierarchy.h"
#include "mainwindow.h"
#include "sceneview.h"
//#include "Shapes.h"

Hierarchy::Hierarchy(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Hierarchy)
{
    ui->setupUi(this);

    connect(ui->AddEntity, SIGNAL(clicked()), this, SLOT(onAddEntityButton()));
    connect(ui->RemoveEntity, SIGNAL(clicked()), this, SLOT(onRemoveEntityButton()));
    connect(ui->EntityList, SIGNAL(currentRowChanged(int)), this, SLOT(onEntitySelected(int)));
    connect(ui->EntityList, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(onEntityChangeName(QListWidgetItem*)));

    connect(ui->MoveUpButton, SIGNAL(clicked()),this, SLOT(onEntityUpButton()));
    connect(ui->MoveDownButton, SIGNAL(clicked()),this, SLOT(onEntityDownButton()));

}

Hierarchy::~Hierarchy()
{
    delete ui;
}

//FROM UI===============================================================
void Hierarchy::onAddEntityButton()
{

    emit AddEntityButtonPressed();
    /*circle* newentity = new circle();

    newentity->SetCircle(win->sceneview->entities.count()*50,100,50,50);
    newentity->SetColorFill(QColor::fromRgb(0,0,255));
    newentity->SetColorBorder(QColor::fromRgb(0,255,0));
    newentity->SetBorderThickness(3);
    newentity->type = CIRCLE;
    //newentity->priority = ui->EntityList->count();

    win->sceneview->entities.push_back(newentity);
    ui->EntityList->addItem("Entity");*/

}

void Hierarchy::onRemoveEntityButton()
{
    emit RemoveEntityButtonPressed();

    /*int row = ui->EntityList->currentRow();
    ui->EntityList->takeItem(row);*/
}

void Hierarchy::onEntitySelected(int row)
{
    emit entitySelected(row);
}

void Hierarchy::onEntityChangeName(QListWidgetItem* item)
{
    item->setFlags(item->flags()| Qt::ItemIsEditable);
    //item->setFlags(Qt::ItemIsEnabled);
    ui->EntityList->editItem(item);
    //item->setTextColor(QColor::fromRgb(255,255,255));

    //EMIT EVENT WHEN DRAG AND DROP HAPPENS AND ORDER ALL ELEMENTS BY THAT, GIVE EACH ONE A POINTER TO ITS LIST COUNTERPART
}

void Hierarchy::onEntityUpButton()
{
    emit EntityUpButtonPressed();

    /*if(ui->EntityList->currentRow()==0)
        return;

    //win->sceneview->entities.swap(ui->EntityList->currentRow(),ui->EntityList->currentRow()-1);

    int row_start = ui->EntityList->currentRow();
    QString name = ui->EntityList->item(row_start)->text();
    ui->EntityList->takeItem(row_start);
    ui->EntityList->insertItem(row_start-1,name);
    ui->EntityList->setCurrentRow(row_start-1);*/

}

void Hierarchy::onEntityDownButton()
{
    emit EntityDownButtonPressed();

    /*
    if(ui->EntityList->currentRow()==ui->EntityList->count()-1)
        return;

    //win->sceneview->entities.swap(ui->EntityList->currentRow(),ui->EntityList->currentRow()+1);

    int row_start = ui->EntityList->currentRow();
    QString name = ui->EntityList->item(row_start)->text();
    ui->EntityList->takeItem(row_start);
    ui->EntityList->insertItem(row_start+1,name);
    ui->EntityList->setCurrentRow(row_start+1);*/
}

//FROM SCENE===============================================================================

void Hierarchy::AddedEntityList()
{
    ui->EntityList->addItem("Entity");
}

void Hierarchy::RemovedEntityList(int index)
{
    //int row = ui->EntityList->currentRow();
    ui->EntityList->takeItem(index);
}
void Hierarchy::EntityMovedUpList(int index)
{
    //int row_start = ui->EntityList->currentRow();
    QString name = ui->EntityList->item(index)->text();
    ui->EntityList->takeItem(index);
    ui->EntityList->insertItem(index-1,name);
    ui->EntityList->setCurrentRow(index-1);
}

void Hierarchy::EntityMovedDownList(int index)
{
    //int row_start = ui->EntityList->currentRow();
    QString name = ui->EntityList->item(index)->text();
    ui->EntityList->takeItem(index);
    ui->EntityList->insertItem(index+1,name);
    ui->EntityList->setCurrentRow(index+1);
}
