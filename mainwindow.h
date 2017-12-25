#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QFileDialog>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMainWindow>
#include <QMessageBox>
#include <QMouseEvent>
#include <QStandardItemModel>
#include <QStandardItem>

#include "dollarone.h"
#include "publictools.h"
#include "statemachine.h"
#include "gestureitem.h"

#define EDITMODE_VIEW (0)
#define EDITMODE_ADD  (1)
#define EDITMODE_DEL  (2)
#define EDITMODE_MOVE (3)

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private slots:
  void on_actionOpen_triggered();

  void on_actionClose_File_triggered();

  void on_treeView_clicked(const QModelIndex &index);

  void on_graphicsView_MousePressEvent(QMouseEvent *);

  void ShowPoints(int index);

  void on_actionEdit_Mode_triggered();

  void on_actionRemove_Mode_triggered();

  void on_actionAdd_Mode_triggered();

  void on_treeView_objectNameChanged(const QString &objectName);

private:
  Ui::MainWindow *ui;
  QStandardItemModel* model;
  QGraphicsScene* scene;

  DollarOne dollarOne;
  StateMachine stateMachine;
  QVector<GestureItem> itemList;
  int nowItem;

  int editMode;
  int selectedPoint;
};

#endif // MAINWINDOW_H
