#include <QDialog>
#include <QCloseEvent>
#include <QRandomGenerator>
#include "MainWindow.hpp"
#include "Game.hpp"
#include "GameWindow.hpp"
using namespace gui;
#include <vector>
#include <stdexcept>
using namespace std;

MainWindow::MainWindow() {
    setWindowTitle("Coup");
    layout = new QVBoxLayout;

    QLabel* label = new QLabel("# Welcome to Coup!\nSelect number of players:");
    label->setAlignment(Qt::AlignHCenter);
    label->setTextFormat(Qt::MarkdownText);

    pnumSpin = new QSpinBox;
    pnumSpin->setRange(2, 6);
    pnumSpin->setValue(2);

    startButton = new QPushButton("Start Game");
    connect(startButton, &QPushButton::clicked, this, &MainWindow::startSetup);

    layout->addWidget(label);
    layout->addWidget(pnumSpin);
    layout->addWidget(startButton);

    setLayout(layout);
}

void MainWindow::startSetup() {
    int pnum = pnumSpin->value();
    vector<Player*> players;
    QStringList roleNames = {"Spy", "Governor", "Judge", "Merchant", "General", "Baron"};
    QStringList roleDescs = {
        "Can see the number of coins another player has, and blocks arrest.",
        "+1 coin during tax. Can also cancel tax.",
        "Can cancel bribes, and a sanction against them costs 1 coin.",
        "When coins > 3, +1 coin each turn. Arrest makes them pay the bank, not the attacker.",
        "Can undo a coup. Also nullifies arrest.",
        "Can invest. Receives +1 coin if attacked with sanction."
    };

    QVector<int> roleIndices;
    for (int i = 0; i < 6; ++i) roleIndices.push_back(i);
	int h_ind;
    for (int i = 0; i < pnum; ++i) {
		int choice = QRandomGenerator::global()->bounded(0, 6);
		bool is_cpu = (i != 0);
		if(!is_cpu)
			h_ind = choice;
        Player* p;
        switch (choice) {
            case 0:
		    p = new Spy(i, is_cpu);
		    break;
            case 1:
		    p = new Governor(i, is_cpu);
		    break;
            case 2:
		    p = new Judge(i, is_cpu);
		    break;
            case 3:
		    p = new Merchant(i, is_cpu);
		    break;
            case 4:
		    p = new General(i, is_cpu);
		    break;
            case 5:
		    p = new Baron(i, is_cpu);
		    break;
            default:
		    throw std::invalid_argument("Invalid role.");
        }
        players.push_back(p);
    }

    QDialog* roleDialog = new QDialog;
    QVBoxLayout* dlayout = new QVBoxLayout(roleDialog);
    QLabel* roleLabel = new QLabel(QString("Your role: <b>%1</b>").arg(roleNames[h_ind]));
    QLabel* descLabel = new QLabel(QString("Description: %1").arg(roleDescs[h_ind]));
    QPushButton* okButton = new QPushButton("OK");
    connect(okButton, &QPushButton::clicked, roleDialog, &QDialog::accept);

    dlayout->addWidget(roleLabel);
    dlayout->addWidget(descLabel);
    dlayout->addWidget(okButton);
    roleDialog->exec();

    close();
    GameWindow* game_win = new GameWindow(players);
    game_win->show();
}
