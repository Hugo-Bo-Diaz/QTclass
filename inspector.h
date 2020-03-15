#ifndef INSPECTOR_H
#define INSPECTOR_H

#include <QWindow>

#include <QWidget>
#include <QColorDialog>
#include "Shapes.h"

namespace Ui {
class Transform;
class Properties;
}

class Inspector : public QWidget
{
    Q_OBJECT

public:
    explicit Inspector(QWidget *parent = nullptr);
    ~Inspector();

signals:
    void AttributeChanged(AttribType aty,float att);
    void SceneChange();

public slots:
    void onEntitySelected(shape*s);

    void onPosXChanged(double val);
    void onPosYChanged(double val);
    void onScaleXChanged(double val);
    void onScaleYChanged(double val);

    void onChangeShape(int index);

    void onFillPatternChanged(int index);

    void onFillColorButtonPressed();

    void onBorderPatternChanged(int index);

    void onBorderColorButtonPressed();

    void onBorderWidthChanged(double val);

private:
    Ui::Transform *uiTransform;
    Ui::Properties *uiProperties;

    QWidget *transformWidget;
    QWidget *propertiesWidget;
};

#endif // HIERARCHY_H
