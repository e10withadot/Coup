#include "MainWindow.hpp"
using namespace gui;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow main_win;
    main_win.show();
    return app.exec();
}
