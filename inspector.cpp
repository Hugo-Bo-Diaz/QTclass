#include "inspector.h"
#include "ui_transform.h"
#include "ui_mesh.h"

Inspector::Inspector(QWidget *parent) :
    QWidget(parent),
    uiTransform(new Ui::Transform),
    uiMesh(new Ui::Mesh)
{
    QWidget *transformWidget = new QWidget;
    uiTransform->setupUi(transformWidget);

    QWidget *meshWidget = new QWidget;
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
