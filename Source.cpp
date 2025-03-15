#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

struct Data {
	string num;
	vector<string> msgs;
};

struct Note {
	string content;
	string root;
	string type;
};

class Phonebook {
	public:
		unordered_map <string, Data> database;
		Phonebook(unordered_map<string, Data> &cnt) {
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

class Notes {
	public:
		vector<Note> all_notes;

		void importMSG(unordered_map<string, Data>& database) {
			int i, chosen, to_import;
			string ext_from;
			vector<string> names;

			i = 1;
			for (const auto& contact : database) {
				cout << "[" << i << "] " << contact.first << " :: (" << contact.second.num << ");\n";
				names.push_back(contact.first);
				i++;
			}


			cout << "Which chat are we importing a message from? [enter index]: ";
			cin >> chosen;
			ext_from = names[chosen - 1];


			i = 1;
			for (string msg : database[ext_from].msgs) {
				cout << "[" << i << "] " << msg << "\n";
				i++;
			}

			cout << "Which message are we importing? [enter index]: ";
			cin >> to_import;
			Note formedNote;
			formedNote.content = database[ext_from].msgs[to_import];
			formedNote.root = "pb";
			formedNote.type = "txt";

			all_notes.push_back(formedNote);
		};
		void showAll() {
			int i = 1;
			for (Note memo : all_notes) {
				cout << "\nMemo #" << i << endl;
				cout << memo.content << endl;
				cout << "(" << memo.root << ")" << endl;
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

	Phonebook phone(contacts);
	cout << phone.sendSMS("Damian", "Good Morning, nigga!") << endl;
	for (string msg : phone.database["Damian"].msgs) {
		cout << msg << endl;
	}

	Notes app;
	app.importMSG(phone.database);
	app.showAll();

	return 0;
}