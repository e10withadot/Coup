#include <Qt>
#include <QApplication>
#include <QLabel>
#include <QStyle>
#include <QPushButton>
#include <QBoxLayout>
#include "Game.hpp"
#include "Roles.hpp"
using namespace coup;
#include <vector>
using namespace std;

namespace gui {
	class GameWindow : public QWidget {
		public:
			QVBoxLayout* main_layout;
			QLabel* sys_l;
			QVBoxLayout* player_sts;
			QVBoxLayout* actions;

 			GameWindow(vector<Player> players);
			void refreshButtons();
		private slots:
			Game* CUR_GAME;
			void gatherPress();
			void taxPress();
			void arrestPress();
			void investPress();
			void bribePress();
			void sanctionPress();
			void coupPress();
	};
}
