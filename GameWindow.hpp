#include <Qt>
#include <QApplication>
#include <QLabel>
#include <QStyle>
#include <QPushButton>
#include <QComboBox>
#include <QBoxLayout>
#include <QMessageBox>
#include <QDialog>
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

 			GameWindow(vector<Player*> players);
			void refreshButtons();
			void refreshLabels();
			void gameLoop();
		private:
			Game* CUR_GAME;
			bool button_event;
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
