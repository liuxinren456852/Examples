#include <QApplication>
#include "SimpleView.h"

int main( int argc, char** argv )
{
  QApplication app( argc, argv );
  
  SimpleView mySimpleView;
  mySimpleView.show();
  
  return app.exec();
}