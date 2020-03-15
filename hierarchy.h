#ifndef HIERARCHY_H
#define HIERARCHY_H

#include <QWidget>
#include <QListWidget>

namespace Ui {
class Hierarchy;
}

class Hierarchy : public QWidget
{
    Q_OBJECT

public:
    explicit Hierarchy(QWidget *parent = nullptr);
    ~Hierarchy();

signals:

    void entitySelected(int entityId);

    void AddEntityButtonPressed();
    void RemoveEntityButtonPressed();

    void EntityUpButtonPressed();
    void EntityDownButtonPressed();

    void SceneChange();

public slots:

    //FROM UI
    void onAddEntityButton();
    void onRemoveEntityButton();

    void onEntitySelected(int row);
    void onEntityChangeName(QListWidgetItem *item);

    void onEntityUpButton();
    void onEntityDownButton();

    //FROM OTHER MODULES
    void AddedEntityList();
    void RemovedEntityList(int);
    void EntityMovedUpList(int);
    void EntityMovedDownList(int);


private:
    Ui::Hierarchy *ui;
};

#endif // HIERARCHY_H
