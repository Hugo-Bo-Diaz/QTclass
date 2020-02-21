#include "inspector.h"
#include "ui_transform.h"
#include "ui_mesh.h"

Inspector::Inspector(QWidget *parent) :
    QWidget(parent),
    uiTransform(new Ui::Transform),
    uiMesh(new Ui::Mesh)
{
    transformWidget = new QWidget;
    uiTransform->setupUi(transformWidget);

    meshWidget = new QWidget;
    uiMesh->setupUi(meshWidget);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(transformWidget);
    layout->addWidget(meshWidget);
    layout->addItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Expanding));
    setLayout(layout);

}

Inspector::~Inspector()
{
    delete uiTransform;
    delete uiMesh;
}


void Inspector::onEntitySelected(int entityId)
{
    if(entityId%2==0)
    {
        meshWidget->show();
    }
    else {
        meshWidget->hide();
    }
}
