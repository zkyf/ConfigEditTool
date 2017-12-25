#ifndef PUBLICTOOLS_H
#define PUBLICTOOLS_H

#include <QDebug>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QVector>
#include <QVector2D>

typedef QVector<QVector2D> Points;

struct ErrorInfo
{
  enum ErrorCode{
    Error_Success = 0,
    Error_InvalidToken,
    Error_InvalidStateName,
    Error_UnexpectedEOF,
    Error_ConflictCursor,
    Error_NoSuchFile,
    Error_MultipleTarget,
    Error_NoSuchTemplate
  };

  ErrorCode code;
  QString info;
  int lineNum;

  ErrorInfo() : code(Error_Success), info("Success") {}
};

class PublicTools
{
public:
  static void DrawPoints(Points points, QGraphicsScene* scene, QSet<int> redSet = QSet<int>())
  {
    if(scene == nullptr) return;
    if(points.size() < 1) return;

    double xratio = scene->sceneRect().width();
    double yratio = scene->sceneRect().height();
    double wratio = sqrt((xratio*xratio+yratio*yratio)/2);
    double ser = 3.0;
//    qDebug() << "xratio=" << xratio << "yratio=" << yratio << "wratio=" << wratio;
    const double radius = 0.01;
    const double width = 0.01;

    for(int i=1; i<points.size(); i++)
    {
      scene->addLine(
          points[i-1].x()*xratio, points[i-1].y()*yratio,
          points[i].x()*xratio, points[i].y()*yratio,
          QPen(QColor(0, 0, 0), width*wratio));
    }

    for(int i=1; i<points.size()-1; i++)
    {
      scene->addEllipse(
            points[i].x()*xratio-radius*wratio/2, points[i].y()*yratio-radius*wratio/2,
            radius*wratio, radius*wratio,
            QPen(QColor(255, 0, 0)), QBrush(QColor(255, 0, 0)));
    }

    scene->addEllipse(
          points[0].x()*xratio-ser*radius*wratio/2,
          points[0].y()*yratio-ser*radius*wratio/2,
          ser*radius*wratio, ser*radius*wratio,
          QPen(QColor(0, 0, 255)), QBrush(QColor(0, 0, 255)));

    scene->addEllipse(
          points[points.size()-1].x()*xratio-ser*radius*wratio/2,
          points[points.size()-1].y()*yratio-ser*radius*wratio/2,
          ser*radius*wratio, ser*radius*wratio,
          QPen(QColor(0, 255, 0)), QBrush(QColor(0, 255, 0)));

    for(QSet<int>::iterator ii=redSet.begin(); ii!=redSet.end(); ii++)
    {
      int i=*ii;
      scene->addEllipse(
            points[i].x()*xratio-5*radius*wratio/2,
            points[i].y()*yratio-5*radius*wratio/2,
            5*radius*wratio, 5*radius*wratio,
            QPen(QColor(255, 0, 0)), QBrush(QColor(255, 0, 0)));
    }
  }
};

#endif // PUBLICTOOLS_H
