#ifndef SHAPES_H
#define SHAPES_H

#include <QRectF>
#include <QColor>

enum shapetype
{
    NONE,
    CIRCLE,
    RECTANGLE
};

class shape
{
public:

    shapetype type;
    QColor colorFill = QColor::fromRgb(255,255,255);
    QColor colorBorder = QColor::fromRgb(0,0,0);
    Qt::BrushStyle bstyle = Qt::BrushStyle::SolidPattern;
    Qt::PenStyle pstyle = Qt::PenStyle::SolidLine;

    float borderThickness;

    void SetColorBorder(QColor border)
    {
        colorBorder = border;
    }
    void SetColorFill(QColor fill)
    {
        colorFill = fill;
    }
    void SetBorderThickness(float thickness)
    {
        borderThickness = thickness;
    }
};

class rectangle : public shape
{
public:

  float x;
  float y;
  float w;
  float h;
  QRectF* Qrectangle;

  rectangle(){};

  void SetRectangle(float _x,float _y,float _w, float _h)
  {
      x=_x;
      y=_y;
      w=_w;
      h=_h;
      Qrectangle = new QRectF();
      Qrectangle->setRect(x,y,w,h);
  };

};

class circle : public shape
{
public:

    float x;
    float y;
    float rx;
    float ry;

    QPointF* Qcenter;

    circle(){};

    void SetCircle(float _x,float _y,float _rx, float _ry)
    {
        x=_x;
        y=_y;
        rx=_rx;
        ry=_ry;
        Qcenter = new QPointF(x,y);
    };
};

#endif // SHAPES_H
