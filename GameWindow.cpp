#include "GameWindow.hpp"
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
    void (GameWindow::*funcs[7]) () = { 
        &GameWindow::gatherPress, 
        &GameWindow::taxPress, 
        &GameWindow::arrestPress, 
        &GameWindow::bribePress, 
        &GameWindow::sanctionPress, 
        &GameWindow::coupPress, 
        &GameWindow::investPress
    };
    const char* b_name[7] = { "Gather", "Tax", "Arrest",  "Bribe", "Sanction", "Coup", "Invest" };
    Player* turn = CUR_GAME->turn();
    for (int i = 0; i < 7; i++) {
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
}

void GameWindow::refreshButtons() {
    Player* turn = CUR_GAME->turn();
    if (turn->cpu())
        for (int i = 0; i < 7; i++)
             button_sts[i]->setEnabled(false);
    else if (turn->role() == BARON) 
         button_sts[6]->setEnabled(false);
}

void GameWindow::refreshLabels(vector<Player*> affected) {
    for (Player* p : affected) {
        int i = p->index();
        player_l[i]->setText(QString("**Player %1:** %2 coins").arg(i+1).arg(p->coins()));
    }
}

void GameWindow::gatherPress() {}
void GameWindow::taxPress() {}
void GameWindow::arrestPress() {}
void GameWindow::investPress() {}
void GameWindow::coupPress() {}
void GameWindow::bribePress() {}
void GameWindow::sanctionPress() {}
