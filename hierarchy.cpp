#include "hierarchy.h"
#include "ui_hierarchy.h"
#include "mainwindow.h"
#include "sceneview.h"

Hierarchy::Hierarchy(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Hierarchy)
{
    ui->setupUi(this);

    connect(ui->AddEntity, SIGNAL(clicked()), this, SLOT(onAddEntity()));
    connect(ui->RemoveEntity, SIGNAL(clicked()), this, SLOT(onRemoveEntity()));
    connect(ui->EntityList, SIGNAL(currentRowChanged(int)), this, SLOT(onEntitySelected(int)));
    connect(ui->EntityList, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(onEntityChangeName(QListWidgetItem*)));

    connect(ui->EntityList, SIGNAL(itemSelectionChanged(QListWidgetItem*)),this, SLOT(test(QListWidgetItem*)));
}

Hierarchy::~Hierarchy()
{
    delete ui;
}

void Hierarchy::onAddEntity()
{
    circle* newentity = new circle();

    newentity->SetCircle(win->sceneview->entities.count()*100,100,50,50);
    newentity->SetColorFill(QColor::fromRgb(0,0,255));
    newentity->SetColorBorder(QColor::fromRgb(0,255,0));
    newentity->SetBorderThickness(3);
    newentity->type = CIRCLE;

    win->sceneview->entities.push_back(newentity);
    ui->EntityList->addItem("Entity");

}

void Hierarchy::onRemoveEntity()
{
    int row = ui->EntityList->currentRow();
    ui->EntityList->takeItem(row);
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

void Hierarchy::test(QListWidgetItem* item)
{
    item->setTextColor(QColor::fromRgb(255,255,255));
}
