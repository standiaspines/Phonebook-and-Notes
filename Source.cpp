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

string requestInput() {
	string num;
	cout << "Enter a new number: ";
	cin >> num;

	return num;
}

class Phonebook {
	public:
		unordered_map <string, Data> database;
		Phonebook(unordered_map<string, Data>& cnts) {
			database = cnts;
		}

		bool checkExistance(string& cnt) {
			if (database.find(cnt) != database.end()) {
				return true;
			}
			else { return false; }
		}

		string createContact(string name, string num) {
			Data new_cnt;
			new_cnt.num = num;

			database[name] = new_cnt;

			return name;
		}

		string sendSMS(string contact, string message) {
			if (!checkExistance(contact)) {
				createContact(contact, requestInput());	
			}

			database[contact].msgs.push_back(message);
			return "You said \"" + message + "\" to \'" + contact + "\'.\n";
		}
};

class Notes {
	public:
		vector<Note> all_notes;
		Notes(vector<string>& pre_saved_nts) {
			for (string note : pre_saved_nts) {
				Note memo;
				memo.content = note;
				memo.root = "local";
				memo.type = "txt";
				all_notes.push_back(memo);
			}
		}

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
			formedNote.content = database[ext_from].msgs[to_import-1];
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
				i++;
			}
		}

		Note selectMemo() {
			int to_select;

			showAll();
			
			cout << "Which MEMO you wanna select? [enter index]: ";
			cin >> to_select;
			return all_notes[to_select - 1];
		}
};



void sendMemoAsMSG(string cnt, Notes& nb, Phonebook& phb) {
	phb.checkExistance(cnt);
	cout << phb.sendSMS(cnt, nb.selectMemo().content);
}

int main() {
	unordered_map<string, Data> contacts;
	//contacts["Alice"] = "412-8978-0912";

	Data dame;
	dame.num = "652-1823-0910";
	vector<string> dame_msgs = { "Hello, bro", "You up to party tonight?" };
	dame.msgs = dame_msgs;
	contacts["Damian"] = dame;

	vector<string> reminders = { "Take Pills at 9AM", "Requst money from the boss.\nTIll 12.00PM", "EAT Oatmeal 3 Times/Day" };

	Phonebook phone(contacts);
	cout << phone.sendSMS("Damian", "Good Morning, nigga!") << endl;

	Notes memosave(reminders);
	memosave.importMSG(phone.database);
	//memosave.showAll();

	sendMemoAsMSG("Damian", memosave, phone);

	for (string msg : phone.database["Damian"].msgs) {
		cout << msg << endl;
	}
	//cout << phone.database["Damian"].msgs[3];

	return 0;
}