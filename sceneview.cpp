#include "sceneview.h"
#include <QPainter>


rectangle* SceneView::CircToRect(circle* c)
{
    rectangle* ret =new rectangle();

    ret->SetRectangle(c->x,c->y,c->rx,c->ry);
    ret->bstyle=c->bstyle;
    ret->pstyle=c->pstyle;
    ret->borderThickness=c->borderThickness;
    ret->colorFill=c->colorFill;
    ret->colorBorder=c->colorBorder;
    ret->type=RECTANGLE;

    entities.insert(entities.indexOf(c),ret);
    entities.removeOne(c);
    delete c;

    return ret;
}

circle* SceneView::RectToCirc(rectangle* r)
{
    circle* ret =new circle();

    ret->SetCircle(r->x,r->y,r->w,r->h);
    ret->bstyle=r->bstyle;
    ret->pstyle=r->pstyle;
    ret->borderThickness=r->borderThickness;
    ret->colorFill=r->colorFill;
    ret->colorBorder=r->colorBorder;
    ret->type=CIRCLE;

    entities.insert(entities.indexOf(r),ret);
    entities.removeOne(r);
    delete r;

    return ret;

}


SceneView::SceneView(QWidget* parent): QWidget (parent)
{
    setAutoFillBackground(true);

    /*circle* newcircle = new circle();
    newcircle->SetCircle(100,100,50,50);
    newcircle->SetColorFill(QColor::fromRgb(255,0,0));
    newcircle->SetColorBorder(QColor::fromRgb(0,255,0));
    newcircle->SetBorderThickness(5);

    newcircle->type = CIRCLE;
    entities.push_back((shape*)newcircle);*/

}

void SceneView::EntitySelectedSlot(int row)
{
    if(row > entities.count()-1)
        return;

    selected = entities[row];
    emit EntitySelected(selected);
}

void SceneView::AddEntity()
{
    circle* newcircle = new circle();
    newcircle->SetCircle(100+entities.count()*25,100,50,50);
    newcircle->SetColorFill(QColor::fromRgb(255,0,0));
    newcircle->SetColorBorder(QColor::fromRgb(0,255,0));
    newcircle->SetBorderThickness(5);

    newcircle->type = CIRCLE;
    entities.push_back((shape*)newcircle);

    update();

    emit EntityAdded();
}

void SceneView::RemoveEntity()
{
    int index = entities.indexOf(selected);

    entities.removeOne(selected);
    update();

    emit EntityRemoved(index);
}

void SceneView::MoveEntityUp()
{
    int index = entities.indexOf(selected);
    if(index<=0)
        return;

    entities.swap(index,index-1);
    update();

    emit EntityMovedUp(index);
}

void SceneView::MoveEntityDown()
{
    int index = entities.indexOf(selected);
    if(index>entities.count()-2)
        return;

    entities.swap(index,index+1);
    update();

    emit EntityMovedDown(index);
}

void SceneView::onSceneChange()
{

    update();

}

void SceneView::onAttributeChanged(AttribType aty, float num)
{
    if(selected == nullptr)
        return;

    switch (aty) {
    case SHAPE_TYPE:
        {
        switch ((int)num) {
        case 0:
            {
            if(selected->type != CIRCLE)
                selected = RectToCirc((rectangle*)selected);
            }
            break;
        case 1:
            {
            if(selected->type != RECTANGLE)
                selected = CircToRect((circle*)selected);            }
            break;
        default:
            break;
        }
        }
        break;
    case POSITIONX:
        {
            switch (selected->type) {
            case CIRCLE:
                {
                //((circle*)selected)->x = num;
                ((circle*)selected)->SetCircle(num,((circle*)selected)->y,((circle*)selected)->rx,((circle*)selected)->ry);
                }
                break;
            case RECTANGLE:
                {
                //((rectangle*)selected)->x = num;
                ((rectangle*)selected)->SetRectangle(num,((rectangle*)selected)->y,((rectangle*)selected)->w,((rectangle*)selected)->h);
                }
                break;
            default:
                break;
            }
        }
        break;
    case POSITIONY:
        {
        switch (selected->type) {
        case CIRCLE:
            {
            //((circle*)selected)->y = num;
            ((circle*)selected)->SetCircle(((circle*)selected)->x,num,((circle*)selected)->rx,((circle*)selected)->ry);
            }
            break;
        case RECTANGLE:
            {
            //((rectangle*)selected)->y = num;
            ((rectangle*)selected)->SetRectangle(((rectangle*)selected)->x,num,((rectangle*)selected)->w,((rectangle*)selected)->h);
            }
            break;
        default:
            break;
        }
        }
        break;
    case BRUSHSTYLE:
        {
            selected->bstyle = GetBrushStyle(num);
        }
        break;
    case PENSTYLE:
        {
            selected->pstyle = GetPenStyle(num);
        }
        break;
    case BORDERTHICKNESS:
        {
            selected->borderThickness = num;
        }
        break;
    case W:
        {
        if(selected->type == RECTANGLE)
            //((rectangle*)selected)->w = num;
            ((rectangle*)selected)->SetRectangle(((rectangle*)selected)->x,((rectangle*)selected)->y,num,((rectangle*)selected)->h);

        }
        break;
    case H:
        {
        if(selected->type == RECTANGLE)
            //((rectangle*)selected)->h = num;
            ((rectangle*)selected)->SetRectangle(((rectangle*)selected)->x,((rectangle*)selected)->y,((rectangle*)selected)->w,num);

        }
        break;
    case RX:
        {
        if(selected->type == CIRCLE)
            ((circle*)selected)->rx = num;
        }
        break;
    case RY:
        {
        if(selected->type == CIRCLE)
            ((circle*)selected)->ry = num;
        }
        break;
    case COLORFILLR:
        {
        QColor c = selected->colorFill;
        c.setRed(num);
        selected->SetColorFill(c);
        }
        break;
    case COLORFILLG:
        {
        QColor c = selected->colorFill;
        c.setGreen(num);
        selected->SetColorFill(c);
        }
        break;
    case COLORFILLB:
        {
        QColor c = selected->colorFill;
        c.setBlue(num);
        selected->SetColorFill(c);
        }
        break;
    case COLORBORDERR:
        {
        QColor c = selected->colorFill;
        c.setRed(num);
        selected->SetColorBorder(c);
        }
        break;
    case COLORBORDERG:
        {
        QColor c = selected->colorFill;
        c.setGreen(num);
        selected->SetColorBorder(c);
        }
        break;
    case COLORBORDERB:
        {
        QColor c = selected->colorFill;
        c.setBlue(num);
        selected->SetColorBorder(c);
        }
        break;

    }

    update();
}

Qt::BrushStyle SceneView::GetBrushStyle(int num)
{
    switch (num) {
    case 0:
        return Qt::BrushStyle::SolidPattern;
        break;
    case 1:
        return Qt::BrushStyle::Dense2Pattern;
        break;
    case 2:
        return Qt::BrushStyle::CrossPattern;
        break;
    case 3:
        return Qt::BrushStyle::DiagCrossPattern;
        break;
    }
}

Qt::PenStyle SceneView::GetPenStyle(int num)
{
    switch (num) {
    case 0:
        return Qt::PenStyle::SolidLine;
        break;
    case 1:
        return Qt::PenStyle::DashLine;
        break;
    case 2:
        return Qt::PenStyle::DotLine;
        break;
    case 3:
        return Qt::PenStyle::DashDotLine;
        break;
    }
}

QSize SceneView::sizeHint() const
{

    return QSize(256,256);

}

QSize SceneView::minimumSizeHint() const
{

    return QSize(64,64);
}

void SceneView::paintEvent(QPaintEvent *event)
{
    QColor blueColor = QColor::fromRgb(127,190,220);
    QColor whiteColor = QColor::fromRgb(255,255,255);
    QColor blackColor = QColor::fromRgb(0,0,0);

    QPainter painter(this);

    QBrush brush;
    QPen pen;

    for (int i=0; i<entities.count(); ++i) {
        brush.setColor(entities[i]->colorFill);
        brush.setStyle(entities[i]->bstyle);
        painter.setBrush(brush);
        pen.setWidth(entities[i]->borderThickness);
        pen.setColor(entities[i]->colorBorder);
        pen.setStyle(entities[i]->pstyle);
        painter.setPen(pen);

        switch (entities[i]->type)
        {
        case CIRCLE:
        {
            circle* c = ((circle*)entities[i]);
            qreal rx = c->rx;
            qreal ry = c->ry;

            painter.drawEllipse(*(c->Qcenter), rx, ry);
        }
            break;
        case RECTANGLE:
        {
            rectangle* r = ((rectangle*)entities[i]);

            painter.drawRect(*(r->Qrectangle));
        }
            break;
        default:
            break;

        }

    };


}

















