#ifndef INSPECTOR_H
#define INSPECTOR_H

#include <QWidget>

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

public slots:
    void onEntitySelected(int entity);

private:
    Ui::Transform *uiTransform;
    Ui::Properties *uiProperties;

    QWidget *transformWidget;
    QWidget *propertiesWidget;
};

#endif // HIERARCHY_H
