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
	class MainWindow : public QWidget {
		public:
			QComboBox *player_sel, *role_sel;
			QVBoxLayout* layout;
			QVector<QWidget*> playerWidgets;
			QPushButton* sub_button;
			MainWindow();
			private slots:
			int pnum = 1;
			void addPlayer();
			void subPlayer();
			void startGame();
	};
}
