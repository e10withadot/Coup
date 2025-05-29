#include "GameWindow.hpp"
#include <qpushbutton.h>
using namespace gui;

GameWindow::GameWindow (vector<Player> players) {
    setWindowTitle("Coup");
    for (int i = 0; i < players.size(); i++) {
        QLabel* label = new QLabel((new QString("**Player %1:** %2 coins"))->arg(i).arg(players[i].coins()));
        label->setTextFormat(Qt::MarkdownText);
        player_sts->addWidget(label);
    }
    sys_l = new QLabel("Game Start!");
    main_layout->addWidget(sys_l);
    main_layout->addLayout(player_sts);
    main_layout->addLayout(actions);
}

void GameWindow::refreshButtons() {
    actions = new QVBoxLayout;
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
    Player *turn = CUR_GAME->turn();
    for (int i = 0; i < 7; i++) {
        if (i != 6 || turn->role() == BARON) {
            QPushButton *button = new QPushButton(QString(b_name[i]));
            QObject::connect(button, &QPushButton::clicked, this, funcs[i]);
            if (turn->cpu())
            actions->addWidget(button);
        }
    }
}
