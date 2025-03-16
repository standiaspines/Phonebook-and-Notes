#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

// contatc data type: has a hyphen-seperated 11 numbers in a string as a phone number & a dynamic array(vector) as a sequence of messages.
struct Data {
	string num;
	vector<string> msgs;
};

// saved note data type: has 3 string elements(props), content of a note; root (where did the note originated from); type = textual\media note;
struct Note {
	string content;
	string root;
	string type;
};

// reusable function to get a keyboard input
string requestInput() {
	string num;
	cout << "Enter a new number: ";
	cin >> num;

	return num;
}


// phonebook class
class Phonebook {
public:
	// database of all contacts, implemented using a hash table. key=contact's name, value=Data datatype (all info).
	unordered_map <string, Data> database;

	//constructor to get an initial sequence of contacts
	Phonebook(unordered_map<string, Data>& cnts) {
		database = cnts;
	}

	// method to check if a contact exist in the database
	bool checkExistance(string& cnt) {
		if (database.find(cnt) != database.end()) {
			return true;
		}
		else { return false; }
	}

	// method to initiate and append a new contact to the database.
	string createContact(string name, string num) {
		Data new_cnt;
		new_cnt.num = num;

		database[name] = new_cnt;

		return name;
	}

	// method for 'sending a message' (actually required in TASK);
	string sendSMS(string contact, string message) {
		// the method receives contact name and message string as parameters

		// first we check if the contact is in the database
		if (!checkExistance(contact)) {
			// if not we create one
			createContact(contact, requestInput());
		}

		// so as we resolved the possible problem of a contact being non-existant, now we can freely add our message to the chat.
		database[contact].msgs.push_back(message);
		return "You said \"" + message + "\" to \'" + contact + "\'.\n"; // and then return approving message
	}
};


// notebook app
class Notes {
public:
	// dynamic array for all notes
	vector<Note> all_notes;

	// contructor to get initiative sequence of notes
	Notes(vector<string>& pre_saved_nts) {

		// since it receieves an array of strins it has to create Note type objects here, running a loop over the sequence
		for (string note : pre_saved_nts) {
			// Note object formation
			Note memo;
			memo.content = note;
			memo.root = "local";
			memo.type = "txt";

			// adding them to the array of all notes
			all_notes.push_back(memo);
		}
	}

	// method to import a text message from phonebook as a Note to the Memo.
	void importMSG(unordered_map<string, Data>& database) {
		// the method refers to the database in the phonebook

		// i :: iteration index, chosen :: for a contact choice indice, to_import :: for a message choice indice;
		int i, chosen, to_import;
		string ext_from;

		// since hash tables do NOT allow indexing, I'm extracting all keys to an array
		vector<string> names;

		i = 1;
		// ui - presenting list of contacts
		for (const auto& contact : database) {
			cout << "[" << i << "] " << contact.first << " :: (" << contact.second.num << ");\n";
			names.push_back(contact.first);
			i++;
		}

		// letting the user choose a contact
		cout << "Which chat are we importing a message from? [enter index]: ";
		cin >> chosen;
		ext_from = names[chosen - 1];


		i = 1;
		// ui - presenting list of messages in the chat
		for (string msg : database[ext_from].msgs) {
			cout << "[" << i << "] " << msg << "\n";
			i++;
		}

		// letting the user choose one
		cout << "Which message are we importing? [enter index]: ";
		cin >> to_import;

		// messages in phonebook are kept in a string form so we have to form a Note type here
		Note formedNote;
		formedNote.content = database[ext_from].msgs[to_import - 1];
		formedNote.root = "pb";
		formedNote.type = "txt";

		all_notes.push_back(formedNote); // the add it to the global array
	};

	// method (ui) to print out all notes in the base
	void showAll() {
		int i = 1;
		for (Note memo : all_notes) {
			cout << "\nMemo #" << i << endl;
			cout << memo.content << endl;
			cout << "(" << memo.root << ")" << endl;
			i++;
		}
	}

	// method for selecting single memo (I should implement multiple selection, too)
	Note selectMemo() {
		int to_select;

		showAll();

		cout << "Which MEMO you wanna select? [enter index]: ";
		cin >> to_select;
		return all_notes[to_select - 1];
	}
};


// function that connects both Phonebook & Memo classes
void sendMemoAsMSG(string cnt, Notes& nb, Phonebook& phb) {
	phb.checkExistance(cnt);
	cout << phb.sendSMS(cnt, nb.selectMemo().content);
}

int main() {
	// pre-initiating list of contacts
	unordered_map<string, Data> contacts;

	Data dame;
	dame.num = "652-1823-0910";
	vector<string> dame_msgs = { "Hello, bro", "You up to party tonight?" };
	dame.msgs = dame_msgs;
	contacts["Damian"] = dame;

	Data alice;
	alice.num = "542-1093-5102";
	vector<string> alice_msgs = { "Hey, Alice...", "imgonna tel you smth very important", "I thnk I developed feelings 4 you.. :D"};
	alice.msgs = alice_msgs;
	contacts["Alice"] = alice;


	// pre-initiating memo list
	vector<string> reminders = { "Take Pills at 9AM", "Requst money from the boss.\nTIll 12.00PM", "EAT Oatmeal 3 Times/Day" };

	// creating phonebook app instance
	Phonebook phone(contacts);
	// testing the 'send message' method
	cout << phone.sendSMS("Damian", "Good Morning, nigga!") << endl;

	// creating memo app instance
	Notes memosave(reminders);
	// testing the 'import message as a note' method
	memosave.importMSG(phone.database);

	// testing a binding function
	sendMemoAsMSG("Alice", memosave, phone);

	// checking if the binding fuction executed properly
	for (string msg : phone.database["Damian"].msgs) {
		cout << msg << endl;
	}

	return 0;
}