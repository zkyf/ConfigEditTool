#ifndef GESTUREITEM_H
#define GESTUREITEM_H

#include <QFile>
#include <QStandardItem>
#include <QString>
#include <QStringList>
#include <QTextStream>
#include <QVector>
#include <QVector2D>

#include "publictools.h"
#include "dollarone.h"
#include "gesturetreeitem.h"

class GestureItem
{
public:
  GestureItem();
  void LoadFile(QString fn, bool c=false);
  void Clear();

  bool config;
  QString name;
  QString fileName;
  Points points;
  QStringList content;
  GestureTreeItem* item;
  bool dirty;
  GestureTreeItem* col2;
};

#endif // GESTUREITEM_H
