#include <Qt>
#include <QApplication>
#include <QLabel>
#include <QStyle>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSpinBox>
#include "Roles.hpp"
using namespace coup;

namespace gui {
class GameWindow;
class MainWindow : public QWidget {
public:
    QSpinBox* pnumSpin;
    QVBoxLayout* layout;
    QVector<QWidget*> playerWidgets;
    QPushButton* startButton;
    MainWindow();
private slots:
    void startSetup();
    void startGame();
};
}
