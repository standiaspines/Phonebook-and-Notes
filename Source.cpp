#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

struct Data {
	string num;
	vector<string> msgs;
};

class Phone {
	public:
		unordered_map <string, Data> database;
		Phone(unordered_map<string, Data> &cnt) {
			database = cnt;
		}

		bool checkExistance(string &cnt) {
			if (database.find(cnt) != database.end()) {
				return true;
			}
			else { return false; }
		}

		string sendSMS(string contact, string message) {
			if (checkExistance(contact)) {
				database[contact].msgs.push_back(message);
				return "You said \"" + message + "\" to \'" + contact + "\'.";
			}
			else {
				return "No such contact in the list.";
			}
 		}
};


int main() {
	unordered_map<string, Data> contacts;
	//contacts["Alice"] = "412-8978-0912";

	Data dame;
	dame.num = "652-1823-0910";
	vector<string> dame_msgs = { "Hello, bro", "You up to party tonight?" };
	dame.msgs = dame_msgs;
	contacts["Damian"] = dame;

	Phone HuaweiP20Lite(contacts);
	cout << HuaweiP20Lite.sendSMS("Damian", "Good Morning, nigga!") << endl;
	for (string msg : HuaweiP20Lite.database["Damian"].msgs) {
		cout << msg << endl;
	}


	return 0;
}