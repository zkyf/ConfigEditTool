#ifndef GESTURETREEITEM_H
#define GESTURETREEITEM_H

#include <QObject>
#include <QStandardItem>

class GestureTreeItem : public QStandardItem
{
public:
  GestureTreeItem();
  GestureTreeItem(const QString& text);
  void* gesture;
};

#endif // GESTURETREEITEM_H
