#include <Qt>
#include <QApplication>
#include <QLabel>
#include <QStyle>
#include <QPushButton>
#include <QVBoxLayout>
#include <QComboBox>

namespace gui {
	class MainWindow : public QWidget {
	    public:
		QVBoxLayout* layout;
		MainWindow() {
			this->layout = new QVBoxLayout;
			this->setWindowTitle("Coup");
			QLabel* label = new QLabel("# Welcome to Coup!\nPick players and choose roles!\n###### To see what roles do, hover on them.");
			label->setAlignment(Qt::AlignHCenter);
			label->setTextFormat(Qt::MarkdownText);
			QPushButton* add_button = new QPushButton("+");
			QObject::connect(add_button, &QPushButton::clicked, this, &MainWindow::addPlayer);
			QPushButton* play = new QPushButton("Play");
			this->layout->addWidget(label);
			this->layout->addWidget(add_button);
			this->layout->addWidget(play);
			this->setLayout(this->layout);
		addPlayer();
		}
	    private slots:
		int pnum = 1;
		void addPlayer() {
			QLabel* plabel = new QLabel(QString("Player %1").arg(this->pnum));
			this->pnum++;
			QComboBox *player_sel = new QComboBox();
			player_sel->addItem("Human");
			player_sel->addItem("CPU");
			QComboBox *role_sel = new QComboBox();
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
		}
	};
}
