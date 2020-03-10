#include <QColorDialog>
#include "inspector.h"
#include "sceneview.h"
#include "mainwindow.h"
#include "ui_transform.h"
#include "ui_properties.h"

Inspector::Inspector(QWidget *parent) :
    QWidget(parent),
    uiTransform(new Ui::Transform),
    uiProperties(new Ui::Properties)
{
    transformWidget = new QWidget;
    uiTransform->setupUi(transformWidget);

    propertiesWidget = new QWidget;
    uiProperties->setupUi(propertiesWidget);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(transformWidget);
    QSpacerItem* spacer = new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout->addItem(spacer);
    layout->addWidget(propertiesWidget);

    setLayout(layout);

}

Inspector::~Inspector()
{
    delete uiTransform;
    delete uiProperties;
}


void Inspector::onEntitySelected(int entityId)
{

    win->sceneview->entities[entityId]->SetColorBorder(QColor::fromRgb(255,255,255));
}
