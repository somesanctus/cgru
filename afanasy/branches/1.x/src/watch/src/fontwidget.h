#pragma once

#include <QtGui/QWidget>

class QLineEdit;

#include <name_afqt.h>

class FontWidget : public QWidget
{
Q_OBJECT
public:
   FontWidget( QWidget * parent, afqt::Attr * attrString);
   ~FontWidget();

private slots:
   void editingFinished();

private:
   afqt::Attr * attr;
   QLineEdit * lineedit;
};
