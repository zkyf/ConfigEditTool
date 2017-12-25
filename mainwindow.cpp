#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  model = new QStandardItemModel(ui->treeView);
  model->setHorizontalHeaderLabels(QStringList()<<QStringLiteral("Name")<<QStringLiteral("Type"));
  ui->treeView->setModel(model);
  scene = nullptr;
  nowItem = -1;
  editMode = EDITMODE_VIEW;
  selectedPoint = -1;
}

MainWindow::~MainWindow()
{
  delete ui;
  delete scene;
}

void MainWindow::on_actionOpen_triggered()
{
  QString fileName = QFileDialog::getOpenFileName(this, "Select exist solution config file");
  ErrorInfo error = stateMachine.LoadConfig(fileName);
  if(!error.code==ErrorInfo::Error_Success)
  {
    QMessageBox::information(this, "Error", error.info);
    return;
  }

  QFileInfo fileInfo(fileName);
  QString bn = fileInfo.fileName();
  QString fn = fileInfo.absolutePath();
  qDebug() << bn << fn;
  model->clear();
  model->setHorizontalHeaderLabels(QStringList()<<QStringLiteral("Name")<<QStringLiteral("Type"));

  GestureItem root;
  itemList.push_back(root);
  itemList[0].LoadFile(fileName, true);
  model->appendRow(itemList[0].item);
  model->setItem(itemList[0].item->index().row(), 1, itemList[0].col2);

  QSet<QString> ts;
  for(int i=0; i<stateMachine.transferList.size(); i++)
  {
    if(ts.find(stateMachine.transferList[i].trans)!=ts.end()) continue;
    qDebug() << "new transfer:" << fn+"/"+stateMachine.transferList[i].trans;

    GestureItem newTrans;
    newTrans.LoadFile(fn+"/"+stateMachine.transferList[i].trans);
    qDebug() << "newTrans loaded";
    itemList[0].item->appendRow(newTrans.item);
    qDebug() << "append row";
    itemList[0].item->setChild(newTrans.item->index().row(), 1, newTrans.col2);
    qDebug() << "set child";
    itemList.push_back(newTrans);
  }

  ui->treeView->setModel(model);
}

void MainWindow::on_actionClose_File_triggered()
{
//  qDebug() << "on_actionClose_File_triggered";
  for(int i=1; i<itemList.size(); i++)
  {
    itemList[i].Clear();
//    qDebug() << "on_actionClose_File_triggered clear #" << i;
  }
  if(itemList.size()>0)
  {
    itemList[0].Clear();
//    qDebug() << "on_actionClose_File_triggered clear #" << 0;
  }
  itemList.clear();
//  qDebug() << "on_actionClose_File_triggered clear itemlist";
  model->clear();
  model->setHorizontalHeaderLabels(QStringList()<<QStringLiteral("Name")<<QStringLiteral("Type"));
  ui->treeView->setModel(model);
}

void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
  const QModelIndex* selected;
  qDebug() << index.row();
  if(index.column()!=0) selected = &(index.sibling(index.row(), 0));
  else selected = &index;

  for(int i=0; i<itemList.size(); i++)
  {
    if(itemList[i].name==selected->data().toString())
    {
      selectedPoint=-1;
      if(i>0)
      {
        ShowPoints(i);
      }
      ui->textEdit->clear();
      for(int l=0; l<itemList[i].content.size(); l++)
      {
        ui->textEdit->append(itemList[i].content[l]);
      }
    }
  }
}

void MainWindow::on_graphicsView_MousePressEvent(QMouseEvent *event)
{
  QVector2D p(ui->graphicsView->mapToScene(event->pos()));
  qDebug() << "p=" << p;
  if(nowItem>0)
  {
    if(editMode==EDITMODE_MOVE)
    {
      bool sel=false;
      for(int i=0; i<itemList[nowItem].points.size(); i++)
      {
        QVector2D tp = itemList[nowItem].points[i]*100;
        qDebug() << "length=" << (p-tp).length();
        if((p-tp).length()<5)
        {
          selectedPoint=i;
          sel=true;
          break;
        }
      }
      if(!sel && selectedPoint!=-1)
      {
        itemList[nowItem].points[selectedPoint]=p/100;
      }
      ShowPoints(nowItem);
    }
    if(editMode==EDITMODE_ADD)
    {
      itemList[nowItem].points.push_back(p/100);
      ShowPoints(nowItem);
    }
    if(editMode==EDITMODE_DEL)
    {
      for(int i=0; i<itemList[nowItem].points.size(); i++)
      {
        QVector2D tp = itemList[nowItem].points[i]*100;
        qDebug() << "length=" << (p-tp).length();
        if((p-tp).length()<5)
        {
          itemList[nowItem].points.remove(i);
          ShowPoints(nowItem);
          break;
        }
      }
    }
  }
}

void MainWindow::ShowPoints(int index)
{
  qDebug() << "nowItem=" << nowItem;
  if(scene)
  {
    delete scene;
    scene=nullptr;
  }
  scene = new QGraphicsScene(0.0, 0.0, 100.0, 100.0);
  QSet<int> redSet;
  if(selectedPoint!=-1)
  {
    redSet.insert(selectedPoint);
  }
  PublicTools::DrawPoints(itemList[index].points, scene, redSet);
  ui->graphicsView->setScene(scene);
  ui->graphicsView->fitInView(ui->graphicsView->scene()->sceneRect(), Qt::KeepAspectRatio);
  nowItem = index;
}

void MainWindow::on_actionEdit_Mode_triggered()
{
  editMode = EDITMODE_MOVE;
}

void MainWindow::on_actionRemove_Mode_triggered()
{
  editMode = EDITMODE_DEL;
}

void MainWindow::on_actionAdd_Mode_triggered()
{
  editMode = EDITMODE_ADD;
}

void MainWindow::on_treeView_objectNameChanged(const QString &objectName)
{
  itemList[nowItem].name=objectName;
}
