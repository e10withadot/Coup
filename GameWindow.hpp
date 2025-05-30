#include <Qt>
#include <QApplication>
#include <QLabel>
#include <QStyle>
#include <QPushButton>
#include <QComboBox>
#include <QBoxLayout>
#include <QMessageBox>
#include <QDialog>
#include <QRandomGenerator>
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
			QLabel* p_label;
			vector<QPushButton*> button_sts;
			QVBoxLayout* actions;
			int moves_left = 1;

 			GameWindow(vector<Player*> players);
			void refreshButtons();
			void refreshLabels();
			void gameLoop();
			void nextTurn();
		private:
			Game* CUR_GAME;
			bool button_event;
			vector<int> allowedButtons(Player* p);
			int playerSelect(const char* msg);
			Player* selectionInterface(Player* turn, const char* msg);
		signals:
			void moveComplete();
		private slots:
			void onMove();
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
