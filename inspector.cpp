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


    //CONNECT WITH UI
    connect(uiProperties->FillColor, SIGNAL(clicked()),this, SLOT(onFillColorButtonPressed()));
    connect(uiProperties->BorderColor, SIGNAL(clicked()),this, SLOT(onBorderColorButtonPressed()));
    connect(uiTransform->PosXSpinBox, SIGNAL(valueChanged(double)),this, SLOT(onPosXChanged(double)));
    connect(uiTransform->PosYSpinBox, SIGNAL(valueChanged(double)),this, SLOT(onPosYChanged(double)));
    connect(uiTransform->RotXSpinBox, SIGNAL(valueChanged(double)),this, SLOT(onScaleXChanged(double)));
    connect(uiTransform->RotYSpinBox, SIGNAL(valueChanged(double)),this, SLOT(onScaleYChanged(double)));

    connect(uiProperties->ShapeShift, SIGNAL(currentIndexChanged(int)),this, SLOT(onChangeShape(int)));
    connect(uiProperties->FillPattern, SIGNAL(currentIndexChanged(int)),this, SLOT(onFillPatternChanged(int)));
    connect(uiProperties->BorderPattern, SIGNAL(currentIndexChanged(int)),this, SLOT(onBorderPatternChanged(int)));
    connect(uiProperties->BorderWidth, SIGNAL(valueChanged(double)),this, SLOT(onBorderWidthChanged(double)));

}

Inspector::~Inspector()
{
    delete uiTransform;
    delete uiProperties;
}


void Inspector::onEntitySelected(shape*s)
{
    //shape* s = win->sceneview->entities[entityId];

    switch (s->type)
    {
    case CIRCLE:
    {
        circle* c = ((circle*)s);
        uiTransform->PosXSpinBox->setValue(c->x);
        uiTransform->PosYSpinBox->setValue(c->y);
        uiTransform->RotXSpinBox->setValue(c->rx);
        uiTransform->RotYSpinBox->setValue(c->ry);
    }
        break;
    case RECTANGLE:
    {
        rectangle* r = ((rectangle*)s);
        uiTransform->PosXSpinBox->setValue(r->x);
        uiTransform->PosYSpinBox->setValue(r->y);
        uiTransform->RotXSpinBox->setValue(r->w);
        uiTransform->RotYSpinBox->setValue(r->h);
    }
        break;
    default:
        break;

    }
    uiProperties->BorderWidth->setValue(s->borderThickness);
}

void Inspector::onPosXChanged(double val){
        emit AttributeChanged(AttribType::POSITIONX,val);
        emit ActionDone();

};
void Inspector::onPosYChanged(double val){
        emit AttributeChanged(AttribType::POSITIONY,val);
        emit ActionDone();

}
void Inspector::onScaleXChanged(double val){
        emit AttributeChanged(AttribType::W,val);
        emit AttributeChanged(AttribType::RX,val);
        emit ActionDone();

}
void Inspector::onScaleYChanged(double val){
        emit AttributeChanged(AttribType::H,val);
        emit AttributeChanged(AttribType::RY,val);
        emit ActionDone();

}

void Inspector::onChangeShape(int index){
        emit AttributeChanged(AttribType::SHAPE_TYPE,index);
        emit ActionDone();
}

void Inspector::onFillPatternChanged(int index){
        emit AttributeChanged(AttribType::BRUSHSTYLE,index);
        emit ActionDone();

}

void Inspector::onFillColorButtonPressed(){

    QColor c = QColorDialog::getColor(Qt::white,this,"Choose color");
    emit AttributeChanged(AttribType::COLORFILLR,c.red());
    emit AttributeChanged(AttribType::COLORFILLG,c.green());
    emit AttributeChanged(AttribType::COLORFILLB,c.blue());

    emit ActionDone();


}
void Inspector::onBorderPatternChanged(int index){
        emit AttributeChanged(AttribType::PENSTYLE,index);
        emit ActionDone();
}

void Inspector::onBorderColorButtonPressed(){

    QColor c = QColorDialog::getColor(Qt::white,this,"Choose color");
    emit AttributeChanged(AttribType::COLORBORDERR,c.red());
    emit AttributeChanged(AttribType::COLORBORDERG,c.green());
    emit AttributeChanged(AttribType::COLORBORDERB,c.blue());

    emit ActionDone();


}

void Inspector::onBorderWidthChanged(double val){
        emit AttributeChanged(AttribType::BORDERTHICKNESS,val);
        emit ActionDone();

}


