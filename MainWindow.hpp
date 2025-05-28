#include <Qt>
#include <QApplication>
#include <QLabel>
#include <QStyle>
#include <QPushButton>
#include <QVBoxLayout>
#include <QComboBox>
#include <vector>
using namespace std;
#include "Roles.hpp"
using namespace coup;

namespace gui {
	class MainWindow : public QWidget {
	    public:
		QComboBox *player_sel, *role_sel;
		QVBoxLayout* layout;
		QVector<QWidget*> playerWidgets;
		QPushButton* sub_button;
		MainWindow() {
			layout = new QVBoxLayout;
			setWindowTitle("Coup");
			QLabel* label = new QLabel("# Welcome to Coup!\nPick players and choose roles!\n###### To see what roles do, hover on them.");
			label->setAlignment(Qt::AlignHCenter);
			label->setTextFormat(Qt::MarkdownText);
			QPushButton* add_button = new QPushButton("+");
			sub_button = new QPushButton("-");
			QPushButton* play = new QPushButton("Play");
			QObject::connect(add_button, &QPushButton::clicked, this, &MainWindow::addPlayer);
			QObject::connect(sub_button, &QPushButton::clicked, this, &MainWindow::subPlayer);
			QObject::connect(play, &QPushButton::clicked, this, &MainWindow::startGame);
			layout->addWidget(label);
			layout->addWidget(add_button);
			layout->addWidget(sub_button);
			layout->addWidget(play);
			setLayout(layout);
			addPlayer();
			sub_button->setEnabled(false);
		}
	    private slots:
		int pnum = 1;
		void addPlayer() {
			QLabel* plabel = new QLabel(QString("Player %1").arg(this->pnum));
			this->pnum++;
			if (!sub_button->isEnabled())
				sub_button->setEnabled(true);
			player_sel->addItem("Human");
			player_sel->addItem("CPU");
			role_sel->addItem("Spy");
			role_sel->setItemData(0, "Can see the number of coins another player has, and blocks arrest.", Qt::ToolTipRole);
			role_sel->addItem("Governor");
			role_sel->setItemData(1, "+1 coin during tax. Can also cancel tax.", Qt::ToolTipRole);
			role_sel->addItem("Judge");
			role_sel->setItemData(2, "Can cancel bribes, and a sanction against them costs 1 coin.", Qt::ToolTipRole);
			role_sel->addItem("Merchant");
			role_sel->setItemData(3, "When coins > 3, +1 coin each turn. Arrest makes them pay the bank, not the attacker.", Qt::ToolTipRole);
			role_sel->addItem("General");
			role_sel->setItemData(4, "Can undo a coup. Also nullifies arrest.", Qt::ToolTipRole);
			role_sel->addItem("Baron");
			role_sel->setItemData(5, "Can invest. Recieves +1 coin if attacked with sanction.", Qt::ToolTipRole);
			QWidget *player_wid = new QWidget();
			QHBoxLayout* h_layout = new QHBoxLayout();
			h_layout->addWidget(plabel);
			h_layout->addWidget(player_sel);
			h_layout->addWidget(role_sel);
			player_wid->setLayout(h_layout);
			layout->insertWidget(layout->count() -1, player_wid);
			playerWidgets.append(player_wid);
		}
		void subPlayer() {
			QWidget* lastpl = playerWidgets.takeLast();
			layout->removeWidget(lastpl);
			delete lastpl;
			this->pnum--;
			if (pnum == 1)
				sub_button->setEnabled(false);
		}
		void startGame() {
			vector<Player> players;
			for (int i = 0; i < pnum; i++) {
				QComboBox* pl_sel = qobject_cast<QComboBox *>(playerWidgets[i]->layout()->itemAt(1)->widget());
				QComboBox* rl_sel = qobject_cast<QComboBox *>(playerWidgets[i]->layout()->itemAt(2)->widget());
				int role_n = rl_sel->currentIndex();
				bool is_cpu = pl_sel->currentIndex();
				switch (role_n) {
					case 0:
						players.push_back(new Spy(is_cpu));
						break;
					case 1:
						players.push_back(new Governor(is_cpu));
						break;
					case 2:
						players.push_back(new Judge(is_cpu));
						break;
					case 3:
						players.push_back(new Merchant(is_cpu));
						break;
					case 4:
						players.push_back(new General(is_cpu));
						break;
					case 5:
						players.push_back(new Baron(is_cpu));
						break;
				}
			}
		}
	};
}
