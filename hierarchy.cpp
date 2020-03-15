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
}

void Hierarchy::onRemoveEntityButton()
{
    emit RemoveEntityButtonPressed();
}

void Hierarchy::onEntitySelected(int row)
{
    emit entitySelected(row);
}

void Hierarchy::onEntityChangeName(QListWidgetItem* item)
{
    item->setFlags(item->flags()| Qt::ItemIsEditable);
    ui->EntityList->editItem(item);
    emit NameChanged(ui->EntityList->currentRow(),item->text());
}

void Hierarchy::onEntityUpButton()
{
    emit EntityUpButtonPressed();

}

void Hierarchy::onEntityDownButton()
{
    emit EntityDownButtonPressed();
}

//FROM SCENE===============================================================================

void Hierarchy::AddedEntityList()
{
    ui->EntityList->addItem("Entity");
}

void Hierarchy::RemovedEntityList(int index)
{
    ui->EntityList->takeItem(index);
}
void Hierarchy::EntityMovedUpList(int index)
{
    QString name = ui->EntityList->item(index)->text();
    ui->EntityList->takeItem(index);
    ui->EntityList->insertItem(index-1,name);
    ui->EntityList->setCurrentRow(index-1);
}

void Hierarchy::EntityMovedDownList(int index)
{
    QString name = ui->EntityList->item(index)->text();
    ui->EntityList->takeItem(index);
    ui->EntityList->insertItem(index+1,name);
    ui->EntityList->setCurrentRow(index+1);
}
