#include <ctime>
#include <thread>
using namespace std;
#include "GameWindow.hpp"
#include "Player.hpp"
using namespace gui;

GameWindow::GameWindow (vector<Player*> players) : QWidget(), players(players), button_event(false) {
    CUR_GAME = new Game(players);
    setWindowTitle("Coup");
    main_layout = new QVBoxLayout;
    sys_l = new QLabel("Game Start!");
    QVBoxLayout* sts = new QVBoxLayout;
    p_label = new QLabel(QString("**Your coins:** %1").arg(players[0]->coins()));
    p_label->setTextFormat(Qt::MarkdownText);
    sts->addWidget(p_label);
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
    const char* b_name[12] = { "Gather", "Tax", "Arrest", "Bribe", "Sanction", "Coup", "See Coins", "Block Arrest", "Undo Tax", "Undo Bribe", "Undo Coup", "Invest" };
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
}

void GameWindow::refreshButtons() {
    Player* turn = CUR_GAME->turn();
    if (turn->cpu())
        for (int i = 0; i < 6; i++)
             button_sts[i]->setEnabled(false);
    for (int i = 6; i < 12; i++)
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
            break;
    }
}

void GameWindow::refreshLabels() {
    p_label->setText(QString("**Your coins:** %1").arg(players[0]->coins()));
}

void GameWindow::seeCoinsPress() {
    Spy* turn = (Spy*)(CUR_GAME->turn());
    Player* target;
    QDialog dialog(this);
    QVBoxLayout layout(&dialog);
    QLabel label("Select a player to see their coins:", &dialog);
    QComboBox combo(&dialog);

    for (int i = 0; i < players.size(); ++i) {
        if (i != turn->index()) {
            combo.addItem(QString("Player %1").arg(i + 1), i);
        }
    }

    QPushButton ok("OK", &dialog);
    connect(&ok, &QPushButton::clicked, &dialog, &QDialog::accept);
    layout.addWidget(&label);
    layout.addWidget(&combo);
    layout.addWidget(&ok);
    if (dialog.exec() == QDialog::Accepted) {
        int targetIndex = combo.currentData().toInt();
        target = players[targetIndex];
        QMessageBox::information(this, "Coins Revealed", QString("Player %1 has %2 coins.").arg(targetIndex + 1).arg(target->coins()));
    }
    dialog.close();
    turn->ADDITIONAL = true;
}
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

std::vector<int> allowedButtons(PlayerRole role) {
    std::vector<int> buttons = {0, 1, 2, 3, 4, 5};
    switch (role) {
        case GOVERNOR:
            buttons.push_back(7);
            break;
        case SPY:
            buttons.push_back(6);
            break;
        case GENERAL:
            buttons.push_back(9);
            break;
        case JUDGE:
            buttons.push_back(8);
            break;
        case BARON:
            buttons.push_back(10);
            break;
        default:
            break;
    }
    return buttons;
}

void GameWindow::gameLoop() {
    Player* turn = CUR_GAME->turn();
    sys_l->setText(QString("Player %1's turn!").arg(turn->index()));
    refreshButtons();
    turn->start_turn();
    if(turn->cpu()) {
        std::vector<int> allowed = allowedButtons(turn->role());
        srand(time(0));
        int choice = rand() % allowed.size();
        int index = allowed[choice];
        switch (index) {
            case 0: gatherPress(); break;
            case 1: taxPress(); break;
            case 2: arrestPress(); break;
            case 3: bribePress(); break;
            case 4: sanctionPress(); break;
            case 5: coupPress(); break;
            case 6: blockArrestPress(); break;
            case 7: undoTaxPress(); break;
            case 8: undoBribePress(); break;
            case 9: undoCoupPress(); break;
            case 10: investPress(); break;
            default: break;
        }
    }
    while(!button_event) {
        this_thread::sleep_for(chrono::milliseconds(500));
    }
}
