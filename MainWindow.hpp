#include <Qt>
#include <QApplication>
#include <QLabel>
#include <QStyle>
#include <QPushButton>
#include <QVBoxLayout>
#include <QComboBox>
#include "Roles.hpp"
using namespace coup;

namespace gui {
	class GameWindow;
	class MainWindow : public QWidget {
		public:
			QComboBox *player_sel;
			QComboBox *role_sel;
			QVBoxLayout* layout;
			QVector<QWidget*> playerWidgets;
			QPushButton* sub_button;
//			MainWindow(vector<Player> players);
			MainWindow();
		private slots:
			int pnum;
			void addPlayer();
			void subPlayer();
			void startGame();
	};
}
