// ConsoleApplication112.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//#include<iostre
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<iomanip>
using namespace std;
enum enOption // compilte the enum 
{
	addNewClient=1,
	showClient,  // كي تحددي البداية يزيد وحدو بلا متقوليلو
	deleteClient,
	updateClient,
	findClient,
	exIt
	
	
};
const string myfiles = "2bank1.txt";
struct stclient {
	string accountnumber;
	string pincode;
	string name;
	string phone;
	double accountbalance;
	bool markdelete = false;
};
bool existfile(vector<stclient>&vclient, string accountnumber) {
	stclient client;
	
		string line;
		client = convertrecord(line);
		if (client.accountnumber == accountnumber) {
			return true;
		}
		vclient.push_back(client);

	
	return false;
}

stclient readbank() {
	stclient client;
	vector<stclient>vclient;
	cout << "enter accountnumber:";
	getline(cin >> ws, client.accountnumber);
	while (existfile(vclient,client.accountnumber)) {

		cout << "the client with" << client.accountnumber << "its ready exist in this file ,pleae enter another accountnumber\n";

		getline(cin >> ws, client.accountnumber);
	}
	cout << "enter pincode:";
	getline(cin, client.pincode);
	cout << "enter name:";
	getline(cin, client.name);
	cout << "enter phone\n";
	getline(cin, client.phone);
	cout << "enter accountbalance: ";
	cin >> client.accountbalance;
	return client;
}
string convertrecordtoline(stclient client, string seperator = "#//#") {
	string stconvert = " ";
	stconvert = client.accountnumber + seperator;
	stconvert += client.pincode + seperator;
	stconvert += client.name + seperator;
	stconvert += client.phone + seperator;
	stconvert += to_string(client.accountbalance);
	return stconvert;
}
void organisefile(string file, string outputfile) {
	fstream myfileD;
	myfileD.open(file, ios::out | ios::app);
	if (myfileD.is_open())
	{
		myfileD << outputfile << endl;

		myfileD.close();
	}

}
void addnewclient() {
	stclient client;
	client = readbank();
	organisefile(myfiles, convertrecordtoline(client));
}
void addclient() {
	char addMORE = 'Y';
	do {
		system("cls");
		cout << " add new client:";
		addnewclient();
		cout << "do you want to add more client\n";
		cin >> addMORE;
	} while (toupper(addMORE) == 'Y');
}
vector<string>spstring(string s1, string delim) {
	vector<string>vstring;
	string sword;
	short pos = 0;
	while ((pos = s1.find(delim)) != std::string::npos) {
		sword = s1.substr(0, pos);
		if (sword != "") {
			vstring.push_back(sword);

		}
		s1.erase(0, pos + delim.length());
	}
	if (s1 != " ") {
		vstring.push_back(s1);
	}
	return vstring;
}
stclient convertrecord(string line, string seperator = "#//#") {
	stclient client;
	vector<string>vclientdata;
	vclientdata = spstring(line, seperator);
	client.accountnumber = vclientdata[0];
	client.pincode = vclientdata[1];
	client.name = vclientdata[2];
	client.phone = vclientdata[3];
	client.accountbalance = stod(vclientdata[4]);
	return client;
}
vector<stclient>loadfile(string filename) {
	vector<stclient>vclient;
	fstream myfile;
	myfile.open(filename, ios::in);
	if (myfile.is_open()) {
		string line;
		stclient client;
		while (getline(myfile, line)) {
			client = convertrecord(line);
			vclient.push_back(client);
		}
	}
	return vclient;

}
void printclientrecord(stclient client) {
	cout << "|" << setw(20) << left << client.accountnumber;
	cout << "|" << setw(20) << left << client.pincode;
	cout << "|" << setw(20) << left << client.name;
	cout << "|" << setw(20) << left << client.phone;
	cout << "|" << setw(20) << left << client.accountbalance;

}
void seperator() {
	cout << "\n---------------------------------------------------";
	cout << "---------------------------------------------------\n";

}
void printallclientdata(vector<stclient>vclient) {
	cout << "\n\t\t client list(" << vclient.size() << ")clients(s)";
	seperator();
	cout << "|" << left << setw(20) << "accountnumber";
	cout << "|" << left << setw(20) << "pincode";
	cout << "|" << left << setw(20) << "client name";
	cout << "|" << left << setw(20) << "phone";
	cout << "|" << left << setw(20) << "accountbalance";
	seperator();
	for (stclient client : vclient) {
		printclientrecord(client);

		seperator();


	}
}
void cleanscreen() {
	system("cls");
}
void preeKeyToContinue() {
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	cout << " press any key to continue...";
	getchar();

}
void printmenue() {
	cout << "***************************************\n";
	cout << "\t \t MAIN MENUE SCREEN\t\t\n ";
	cout << "***************************************\n";
	cout << " \t [1] ADD New CLIENTS\n";
	cout << " \t [2] show client list\n";
	cout << "\t[3] delete client\n";
	cout << "\t[4] update client info\n";
	cout << "\t[5] find client\n";
	cout << "\t [6] exit\n";
	cout << "*****************************************\n";
}
void showborder(string text) {
	cout << "******************************************\n";
	cout << "\t\t" << text << "\t\t\n";
	cout << "**********************************************\n";

}
void showclient() {
	vector<stclient>vclient = loadfile(myfiles);
	printallclientdata(vclient);
	preeKeyToContinue();
}
void printinfoclient(stclient client) {
	cout << "account number:" << client.accountnumber << endl;
	cout << "pincode:" << client.pincode << endl;
	cout << "name:" << client.name << endl;
	cout << "phone:" << client.phone << endl;
	cout << "account balance:" << client.accountbalance << endl;

}
bool findbyaccountnumber(string accountnumber, stclient& client) {
	vector<stclient>vclient = loadfile(myfiles);
	for (stclient c : vclient) {
		if (c.accountnumber == accountnumber) {
			client = c;
			return true;

		}
	}
	return false;
}

string paccountnumber() {
	string accountnumber = "";
	cout << " eneter accountnumber\n";
	cin >> accountnumber;
	return accountnumber;
}

void addNewClientScreen() {
	cleanscreen();
	showborder("add client");
	addclient();
}
void showAllClients() {
	cleanscreen();
	showborder("show client");
	showclient();
}
void youfindbyaacountnumber() {
	vector<stclient>vclient;
	stclient client;
	string accountnumber = paccountnumber();
	if (findbyaccountnumber(accountnumber, client)) {
		printinfoclient(client);
	}
	else {
		cout << "aacountnumber(" << accountnumber << ")isn't find" << endl;
	}
	preeKeyToContinue();
	cout << "\n";
}
void findAllClient() {
	cleanscreen();
	showborder("find info");
	youfindbyaacountnumber();

}
bool ifindbyaccountnumber(string accountnumber, vector<stclient>vclient, stclient& client) {
	vclient = loadfile(myfiles); // here vclient is paramater 
	for (stclient c : vclient) {
		if (c.accountnumber == accountnumber) {
			client = c;
			return true;

		}
	}
	return false;
}

bool markedelete(string accountnumber, vector<stclient>& vclient)
{
	for (stclient& c : vclient) {
		if (c.accountnumber == accountnumber) {
			c.markdelete = true;
			return true;
		}
	}
	return false;
}

vector<stclient>savemyfile(string filename, vector<stclient>& vclient) {
	fstream myfile;
	myfile.open(filename, ios::out);
	string file;
	if (myfile.is_open()) {
		for (stclient& c : vclient) { 
			if (c.markdelete == false) {
				file = convertrecordtoline(c);
				myfile << file << endl;

			}

		}
		myfile.close();
	}
	return vclient;
}

bool deleteclient(string accountnumber, vector<stclient>& vclient) {
	stclient client;
	char answer = 'n';
	if (ifindbyaccountnumber(accountnumber, vclient, client)) {// كلش مليح
		printinfoclient(client);
		cout << "do you want to delete a client ? yes or no\n";
		cin >> answer;
		if (answer == 'y' || answer == 'Y') {
			markedelete(accountnumber, vclient);
			savemyfile(myfiles, vclient);
			vclient = loadfile(myfiles); // صاي تحذف
			return true;
		}
	}

	else {
		cout << "aacountnumber(" << accountnumber << ")isn't find" << endl;
	}
	return false;
}
void deleteallclient() {
	vector<stclient>vclient = loadfile(myfiles);
	string accountnumber = paccountnumber();
	deleteclient(accountnumber, vclient);
}
void deleteByAccountNumber() {  
	cleanscreen();
	showborder("delete a client");
	deleteallclient();

}
stclient changeInformation(string accountnumber) {
	stclient client;
	client.accountnumber = accountnumber;
	cout << "enter pincode\n";
	getline(cin >> ws, client.pincode);
	cout << "enter name client\n";
	getline(cin, client.name);
	cout << "enter phone number\n";
	getline(cin, client.phone);
	cout << "enter accountbalance\n";
	cin >> client.accountbalance;
	return client;
}
bool fupdateClient(string accountnumber, vector<stclient>& vclient) {
	char answer = 'n';
	stclient client;
	if (ifindbyaccountnumber(accountnumber, vclient, client))
	{
		printinfoclient(client);
		cout << "do you want to update this client\n";
		cin >> answer;
		if (answer == 'y' || answer == 'Y') {
			for (stclient& c : vclient) {
				if (c.accountnumber == accountnumber) {
					c = changeInformation(accountnumber);
					break;
				}
			}
				savemyfile(myfiles, vclient);
				return true;
			
		}
	}
		else {
			cout << "aacountnumber(" << accountnumber << ")isn't find" << endl;
		}
		return false;


	
}
void updateByClient() {
	vector<stclient>vclient = loadfile(myfiles);
	string accountnumber = paccountnumber();
	fupdateClient(accountnumber, vclient);
}
void updateClientByAccountnumber() {
	cleanscreen();
	showborder("update");
	updateByClient();
}


void choose() { // fix switch with enum not numbers 

	int number;
	do {
		do {
			cleanscreen();
			printmenue();
			cout << " choose what do you want?[1 to 6]\n";
			cin >> number;

		} while (number < 1 || number >6);

		switch ((enOption)number) {
		case enOption::addNewClient:
			addNewClientScreen();
			break;
		case enOption::showClient:
			showAllClients();
			break;
		case enOption::findClient:
			findAllClient();
			break;
		case enOption::deleteClient:
			deleteByAccountNumber();  // 4 is apdate not delete ......
			break;
		case enOption::updateClient:
			updateClientByAccountnumber();
			break;
		case enOption::exIt:

			showborder("exit");
			exit(0);
			break;


		}
	} while (1);
}


int main() {
	choose();
}
