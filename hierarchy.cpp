#include "hierarchy.h"
#include "ui_hierarchy.h"

Hierarchy::Hierarchy(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Hierarchy)
{
    ui->setupUi(this);

    connect(ui->AddEntity, SIGNAL(clicked()), this, SLOT(onAddEntity()));
    connect(ui->RemoveEntity, SIGNAL(clicked()), this, SLOT(onRemoveEntity()));
    connect(ui->EntityList, SIGNAL(currentRowChanged(int)), this, SLOT(onEntitySelected(int)));

}

Hierarchy::~Hierarchy()
{
    delete ui;
}

void Hierarchy::onAddEntity()
{
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
