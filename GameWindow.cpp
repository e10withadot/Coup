#include <stdexcept>
using namespace std;
#include "GameWindow.hpp"
#include "Player.hpp"
using namespace gui;

GameWindow::GameWindow (vector<Player*> players) : QWidget(), players(players) {
    CUR_GAME = new Game(players);
    setWindowTitle("Coup");
    main_layout = new QVBoxLayout;
    sys_l = new QLabel("Game Start!");
    QVBoxLayout* sts = new QVBoxLayout;
    for (int i = 0; i < players.size(); i++) {
        QLabel* label = new QLabel(QString("**Player %1:** %2 coins").arg(i+1).arg(players[i]->coins()));
        label->setTextFormat(Qt::MarkdownText);
        player_l.push_back(label);
        sts->addWidget(label);
    }
    QVBoxLayout* actions = new QVBoxLayout;
    void (GameWindow::*funcs[12]) () = { 
		&GameWindow::gatherPress,
		&GameWindow::taxPress,
		&GameWindow::arrestPress,
		&GameWindow::bribePress,
		&GameWindow::sanctionPress,
		&GameWindow::coupPress,
		&GameWindow::seeCoinsPress,
		&GameWindow::blockArrestPress,
		&GameWindow::undoTaxPress,
		&GameWindow::undoBribePress,
		&GameWindow::undoCoupPress,
		&GameWindow::investPress
    };
    const char* b_name[12] = {
		"Gather",
		"Tax",
		"Arrest",
		"Bribe",
		"Sanction",
		"Coup",
		"See Coins",
		"Block Arrest",
		"Undo Tax",
		"Undo Bribe",
		"Undo Coup",
		"Invest"
    };
    Player* turn = CUR_GAME->turn();
    for (int i = 0; i < 12; i++) {
        QPushButton *button = new QPushButton(QString(b_name[i]));
        QObject::connect(button, &QPushButton::clicked, this, funcs[i]);
        button_sts.push_back(button);
        actions->addWidget(button);
    }
    main_layout->addWidget(sys_l);
    main_layout->addLayout(sts);
    main_layout->addLayout(actions);
    setLayout(main_layout);
    show();
    refreshButtons();
    CUR_GAME->turn()->start_turn();
}

void GameWindow::refreshButtons() {
    Player* turn = CUR_GAME->turn();
    if (turn->cpu())
        for (int i = 0; i < 6; i++)
             button_sts[i]->setEnabled(false);
    for (int i = 7; i < 12; i++)
         button_sts[i]->setEnabled(false);
    switch (turn->role()) {
        case SPY:
            button_sts[6]->setEnabled(true);
            button_sts[7]->setEnabled(true);
            break;
        case GOVERNOR:
            button_sts[8]->setEnabled(true);
            break;
        case JUDGE:
            button_sts[9]->setEnabled(true);
            break;
        case GENERAL:
            button_sts[10]->setEnabled(true);
            break;
        case BARON: 
            button_sts[11]->setEnabled(true);
            break;
        default:
            throw invalid_argument("Invalid role.");
    }
}

void GameWindow::refreshLabels(vector<Player*> affected) {
    for (Player* p : affected) {
        int i = p->index();
        player_l[i]->setText(QString("**Player %1:** %2 coins").arg(i+1).arg(p->coins()));
    }
}

void GameWindow::seeCoinsPress() {}
void GameWindow::gatherPress() {}
void GameWindow::taxPress() {}
void GameWindow::undoTaxPress() {}
void GameWindow::arrestPress() {}
void GameWindow::blockArrestPress() {}
void GameWindow::bribePress() {}
void GameWindow::undoBribePress() {}
void GameWindow::sanctionPress() {}
void GameWindow::coupPress() {}
void GameWindow::undoCoupPress() {}
void GameWindow::investPress() {}
