#include <QComboBox>
#include <vector>
using namespace std;

class ComboBox : public QComboBox {
	public:
		vector<string> options;
		ComboBox(char* options[]);
};
