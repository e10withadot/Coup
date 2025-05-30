#include <ctime>
#include <system_error>
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
    const char* b_name[12] = { 
        "Gather - Free", 
        "Tax - Free", 
        "Arrest - Free", 
        "Bribe - 4 coins", 
        "Sanction - 3 coins", 
        "Coup - 7 coins", 
        "See Coins - Free", 
        "Block Arrest - Free", 
        "Undo Tax - Free", 
        "Undo Bribe - Free", 
        "Undo Coup - 5 coins", 
        "Invest - 3 coins"
    };
    Player* turn = CUR_GAME->turn();
    for (int i = 0; i < 12; i++) {
        QPushButton *button = new QPushButton(QString(b_name[i]));
        connect(button, &QPushButton::clicked, this, funcs[i]);
        if (i != 6) connect(button, &QPushButton::clicked, this, &GameWindow::onMove);
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
    for (int i = 6; i < 12; i++)
         button_sts[i]->setEnabled(false);
    if (turn->cpu()) 
        for (int i = 0; i < 6; i++)
            button_sts[i]->setEnabled(false);
    else {
        if (!turn->ECONOMY) {
            button_sts[0]->setEnabled(false);
            button_sts[1]->setEnabled(false);
        }
        if (!turn->ARREST)
            button_sts[2]->setEnabled(false);
        if (turn->coins() < 7) {
            button_sts[5]->setEnabled(false);
            if (turn->coins() < 4 || turn->ADDITIONAL) {
                button_sts[3]->setEnabled(false);
                if (turn->coins() < 3)
                    button_sts[4]->setEnabled(false);
            }
        }
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
                if (turn->coins() >= 5) button_sts[10]->setEnabled(true);
                break;
            case BARON: 
                if (turn->coins() >= 3) button_sts[11]->setEnabled(true);
                break;
            default:
                break;
        }
    }
}

void GameWindow::refreshLabels() {
    p_label->setText(QString("**Your coins:** %1").arg(players[0]->coins()));
}

int GameWindow::playerSelect() {
    Player* turn = CUR_GAME->turn();
    QDialog dialog(this);
    QVBoxLayout layout(&dialog);
    QLabel label("Select a player to see their coins:", &dialog);
    QComboBox combo(&dialog);
    combo.setAccessibleName(QString("select"));

    for (int i = 0; i < players.size(); ++i)
        if (i != turn->index())
            combo.addItem(QString("Player %1").arg(i + 1), i);

    QPushButton ok("OK", &dialog);
    connect(&ok, &QPushButton::clicked, &dialog, &QDialog::accept);
    layout.addWidget(&label);
    layout.addWidget(&combo);
    layout.addWidget(&ok);
    int retval = -1;
    if (dialog.exec() == QDialog::Accepted) {
        retval = combo.currentData().toInt();
    }
    dialog.close();
    return retval;
}

void GameWindow::seeCoinsPress() {
    Spy* turn = (Spy*)(CUR_GAME->turn());
    int targetIndex;
    if ((targetIndex = playerSelect()) < 0)
        throw errc::operation_canceled;
    Action a = turn->see_coins(players[targetIndex]);
    QMessageBox::information(this, "Coins Revealed", QString("Player %1 has %2 coins.").arg(targetIndex + 1).arg(a.reciever->coins()));
    gameLoop();
}
void GameWindow::gatherPress() {}
void GameWindow::taxPress() {}
void GameWindow::undoTaxPress() {}
void GameWindow::arrestPress() {}

void GameWindow::blockArrestPress() {
    Spy* turn = (Spy*)(CUR_GAME->turn());
    Player* target;
    int targetIndex;
    if (turn->cpu()) {
        QVector<int> possibleTargets;
        for (int i = 0; i < players.size(); ++i) {
            if (i != turn->index()) {
                possibleTargets.push_back(i);
            }
        }
        targetIndex = possibleTargets[QRandomGenerator::global()->bounded(possibleTargets.size())];
        target = players[targetIndex];
    }
    else {
        if ((targetIndex = playerSelect()) < 0)
            throw errc::operation_canceled;
        target = players[targetIndex];
    }
    Action a = turn->block_arrest(target);
    sys_l->setText(QString("Player %1 blocked arrest on Player %2!").arg(turn->index() + 1).arg(targetIndex + 1));
}

void GameWindow::bribePress() {}
void GameWindow::undoBribePress() {}
void GameWindow::sanctionPress() {}
void GameWindow::coupPress() {}
void GameWindow::undoCoupPress() {}
void GameWindow::investPress() {}

void GameWindow::nextTurn() {
    CUR_GAME->moveTurn();
    if (CUR_GAME->winner() == "")
        gameLoop();
    else {
        QMessageBox::information(
            this,
            "Game Over",
            QString("%1 wins the game!").arg(CUR_GAME->winner())
        );
        QApplication::quit();
    }
}
void GameWindow::onMove() {
    moves_left--;
    if (moves_left > 0) {
        refreshButtons();
    } else {
        nextTurn();
    }
}

std::vector<int> allowedButtons(Player* p) {
    std::vector<int> buttons;
    if (p->ECONOMY) {
        buttons.push_back(0);
        buttons.push_back(1);
    }
    if (p->ARREST)
        buttons.push_back(2);
    if (p->coins() >= 7) {
        buttons.push_back(5);
            if (p->coins() >= 4 || !p->ADDITIONAL) {
                buttons.push_back(3);
                if (p->coins() >= 3)
                    buttons.push_back(4);
        }
    }
    switch (p->role()) {
        case GOVERNOR:
            buttons.push_back(7);
            break;
        case SPY:
            buttons.push_back(6);
            break;
        case GENERAL:
            if (p->coins() >= 5) buttons.push_back(9);
            break;
        case JUDGE:
            buttons.push_back(8);
            break;
        case BARON:
            if (p->coins() >= 3) buttons.push_back(10);
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
    if (turn->ADDITIONAL) {
        moves_left = 2;
        turn->ADDITIONAL = false;
    } else {
        moves_left = 1;
    }
    turn->start_turn();

    if (turn->cpu()) {
        std::vector<int> allowed = allowedButtons(turn);
        if (!allowed.empty()) {
            int choice = QRandomGenerator::global()->bounded(static_cast<int>(allowed.size()));
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
        onMove();
    }
}
