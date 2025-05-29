#include <Qt>
#include <QApplication>
#include <QLabel>
#include <QStyle>
#include <QPushButton>
#include <QBoxLayout>
#include <qpushbutton.h>
#include "Game.hpp"
#include "Roles.hpp"
using namespace coup;
#include <vector>
using namespace std;

namespace gui {
	class GameWindow : public QWidget {
		public:
			vector<Player*> players;
			QVBoxLayout* main_layout;
			QLabel* sys_l;
			vector<QLabel*> player_l;
			vector<QPushButton*> button_sts;
			QVBoxLayout* actions;

 			GameWindow(vector<Player*> players);
			void refreshButtons();
			void refreshLabels(vector<Player*> affected);
		private:
			Game* CUR_GAME;
		private slots:
			void seeCoinsPress();
			void gatherPress();
			void taxPress();
			void undoTaxPress();
			void arrestPress();
			void blockArrestPress();
			void bribePress();
			void undoBribePress();
			void sanctionPress();
			void coupPress();
			void undoCoupPress();
			void investPress();
	};
}
