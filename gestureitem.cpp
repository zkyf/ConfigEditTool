#include "gestureitem.h"

GestureItem::GestureItem()
{
  item = nullptr;
  col2 = nullptr;
}

void GestureItem::LoadFile(QString fn, bool c)
{
  QFile file(fn);
  if(!file.open(QIODevice::Text | QIODevice::ReadOnly))
  {
    return;
  }

  name = QFileInfo(fn).fileName();
  fileName = fn;
  config = c;
  QTextStream in(&file);
  Clear();

  // load config file
  while(!in.atEnd())
  {
    content << in.readLine();
  }

  in.seek(0);

  if(!c)
  {
    // load template file
    while(!in.atEnd())
    {
      double x, y;
      in >> x;
      if(in.atEnd()) break;
      in >> y;
      points.push_back(QVector2D(x, y));
      qDebug() << x << y;
    }
  }

//  qDebug() << "file : " << fn;
//  qDebug() << "content=" << content;
//  qDebug() << "points=" << points;

  item = new GestureTreeItem(QFileInfo(fn).fileName());
  item->gesture = this;
  if(c) col2 = new GestureTreeItem("Config File");
  else col2 = new GestureTreeItem("Template");
  col2->gesture = this;

  points = DollarOne::Normalize(points, 1.0);
  points = DollarOne::TranslateTo(points, QVector2D(0.5, 0.5));
}

void GestureItem::Clear()
{
  points.clear();
  content.clear();
  dirty=false;
  if(item) delete item;
  if(col2) delete col2;
  item = nullptr;
  col2 = nullptr;
}
