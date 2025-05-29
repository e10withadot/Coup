#include <Qt>
#include <QApplication>
#include <QLabel>
#include <QStyle>
#include <QPushButton>
#include <QBoxLayout>
#include "Game.hpp"
using namespace coup;
#include <vector>
using namespace std;

namespace gui {
	class GameWindow : public QWidget {
		public:
			vector<QLabel*> pl_labels;
			QVBoxLayout* main_layout;
 			GameWindow(vector<Player> players);
		private slots:
			void gatherPress();
			void taxPress();
			void arrestPress();
			void investPress();
			void bribePress();
			void sanctionPress();
			void coupPress();
	};
}
