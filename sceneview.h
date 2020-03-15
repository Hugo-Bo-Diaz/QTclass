#ifndef SCENEVIEW_H
#define SCENEVIEW_H

#include <QWidget>
#include <list>
#include <qstack.h>
#include "Shapes.h"

struct modification
{
    shape* mod;
    AttribType type;
    float num;
};

class SceneView : public QWidget
{
    Q_OBJECT
public:

    explicit SceneView(QWidget *parent = nullptr);
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

    QList<shape*>entities;
    QStack<modification> actions;
    QStack<modification> undoneActions;

    void AddActionToStack(AttribType,float);
    void ClearScene();

    rectangle* CircToRect(circle* c);
    circle* RectToCirc(rectangle* r);

    shape* selected = nullptr;

signals:
    void EntityAdded();
    void EntityRemoved(int initialpos);
    void EntityMovedUp(int initialpos);
    void EntityMovedDown(int initialpos);

    void EntitySelected(shape* s);

public slots:

    //FROM HIERARCHY
    void AddEntity();
    void RemoveEntity();
    void EntitySelectedSlot(int pos);
    void MoveEntityUp();
    void MoveEntityDown();
    void onNewName(int,QString);

    //FROM INSPECTOR
    void onAttributeChanged(AttribType type, float att);
    void onActionDone();

    //FROM MAINWINDOW
    void onUndoButton();
    void onRedoButton();

    //FUNCTION TO UPDATE THE GRAPHICS
    void onSceneChange();

private:
    void paintEvent(QPaintEvent* event)override;

    Qt::BrushStyle GetBrushStyle(int num);
    Qt::PenStyle GetPenStyle(int num);

};

#endif // SCENEVIEW_H
