#pragma once

#include <qboxlayout.h>
#include <qpainter.h>
#include <qpainterpath.h>
#include <qslider.h>
#include <qwidget.h>

// Source - https://stackoverflow.com/a/42794690
// Posted by dtech, modified by community. See post 'Timeline' for change
// history Retrieved 2026-08-13, License - CC BY-SA 3.0
class CPBar : public QWidget {
  Q_OBJECT
  qreal p;  // progress 0.0 to 1.0
 public:
  CPBar(QWidget* p = 0) : QWidget(p), p(0) { setMinimumSize(208, 208); }
  void upd(qreal pp) {
    if (p == pp) return;
    p = pp;
    update();
  }
  void paintEvent(QPaintEvent*) {
    qreal pd = p * 360;
    qreal rd = 360 - pd;
    QPainter p(this);
    p.fillRect(rect(), Qt::white);
    p.translate(4, 4);
    p.setRenderHint(QPainter::Antialiasing);
    QPainterPath path, path2;
    path.moveTo(100, 0);
    path.arcTo(QRectF(0, 0, 200, 200), 90, -pd);
    QPen pen, pen2;
    pen.setCapStyle(Qt::FlatCap);
    pen.setColor(QColor("#30b7e0"));
    pen.setWidth(8);
    p.strokePath(path, pen);
    path2.moveTo(100, 0);
    pen2.setWidth(8);
    pen2.setColor(QColor("#d7d7d7"));
    pen2.setCapStyle(Qt::FlatCap);
    pen2.setDashPattern(QVector<qreal>{0.5, 1.105});
    path2.arcTo(QRectF(0, 0, 200, 200), 90, rd);
    pen2.setDashOffset(2.2);
    p.strokePath(path2, pen2);
  }
};

// class Test : public QWidget {
//   Q_OBJECT
//
//  public:
//   Test() {
//     QVBoxLayout* l = new QVBoxLayout(this);
//     CPBar* p = new CPBar;
//     QSlider* s = new QSlider(Qt::Horizontal, this);
//     s->setMinimum(0);
//     s->setMaximum(100);
//     l->addWidget(p);
//     l->addWidget(s);
//     setLayout(l);
//     connect(s, &QSlider::valueChanged,
//             [=]() { p->upd((qreal)s->value() / s->maximum()); });
//   }
// };
