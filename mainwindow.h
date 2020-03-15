#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}
class Hierarchy;
class Inspector;
class SceneView;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:

    void onLoadFile();
    void onSaveFile();

private:
    Ui::MainWindow *uiMainWindow;

    SceneView *sceneview;
    Inspector *inspector;
    Hierarchy *hierarchy;
};

#endif // MAINWINDOW_H
