#include "sceneview.h"
#include <QPainter>

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

    /*brush.setColor(blueColor);
    brush.setStyle(Qt::BrushStyle::SolidPattern);
    pen.setStyle(Qt::PenStyle::NoPen);
    painter.setBrush(brush);
    painter.setPen(pen);

    painter.drawRect(rect());

    brush.setColor(whiteColor);
    pen.setWidth(4);
    pen.setColor(blackColor);
    pen.setStyle(Qt::PenStyle::DashLine);
    painter.setBrush(brush);
    painter.setPen(pen);

    int r=64;int w=r*2;int h =r*2; int x = rect().width()/2-r;int y = rect().height()/2-r;
    QRect circleRect(x,y,w,h);
    painter.drawEllipse(circleRect);
    */

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

















