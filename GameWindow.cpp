#include "GameWindow.hpp"
using namespace gui;
#include "Game.hpp"
using namespace coup;

GameWindow::GameWindow (vector<Player> players) {
	main_layout = new QVBoxLayout;
	setWindowTitle("Coup");
    for (int i = 0; i < players.size(); i++) {
        QLabel* label = new QLabel("**Player " + i + ":** " + players[i].coins() + "coins");
        label->setTextFormat(Qt::MarkdownText);
        pl_labels.push_back(label);
    }
}
