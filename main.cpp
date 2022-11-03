/* **************************************************************************************
 * ce projet est réalisé par :
 *
 * - ASSOUMANOU Sarakata
 *
 * - ALAIN Ledoux
 *
 * - HOAREAU Grégory
 *
 * **************************************************************************************/

#include <QApplication>
#include "snake.h"
#include<QtWidgets>

int main(int argc, char *argv[]) {

  QApplication app(argc, argv);

  Snake window;

  window.setWindowTitle("Snake");
  window.show();

  return app.exec();
}
