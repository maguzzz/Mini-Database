#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

class Person {
public:
	std::string first;
	std::string last;
	std::string street;
	std::string houseNum;
	std::string number;
	std::string plz;
	std::string city;
	std::string birthDate;
	std::string salary;

};

void Space() {
	std::cout << std::endl << std::setw(114) << std::right << "------------------------------------------------------------------------------------------------\n\n";
}

void ClearConsole() {
	system("CLS");
}

void InputQuest(std::string quest, std::string &x) {
	std::cout << std::setw(65) << std::right << quest;
	std::cin >> x;
}

std::string optioMain(std::string& x) {
	std::cout << std::setw(33) << "Pick a Option | ";
	std::cin >> x;
	return x;
}

int main()
{
	//Creating a vector with starter data
	std::vector<Person> storage;

	storage.push_back(Person{ "Mark","First","BaumStreet","5","06921239039", "1190", "Vienna","13.12.2000","89.000" });
	storage.push_back(Person{ "Stella","Parker","OllStreet","9","05494239532", "1010", "Vienna","2.9.2004","92.000" });
	storage.push_back(Person{ "Miles","Moral","QuanStreet","19","06923923926", "1190", "Graz","19.5.2000","100.000" });


	std::string first;
	std::string last;
	std::string street;
	std::string houseNum;
	std::string number;
	std::string plz;
	std::string city;
	std::string birthDate;
	std::string salary;

	std::string mainOption = "0";
	std::string option;


	do {
		//Showing Options Ui
		ClearConsole();
		std::cout << "\n" << std::setw(112) << std::right << "|         [0] Show list         |        [1] New user         |         [2] Delete user        |";
		Space();

		//Displaying all Users
		if (mainOption == "0") {
			while (true) {
				for (int i = 0; i < storage.size(); i++) {
					std::cout << std::setw(18) << std::right << "        ";
					std::cout << std::setw(12) << std::left << storage[i].first;
					std::cout << std::setw(12) << std::left << storage[i].last;
					std::cout << std::setw(10) << std::left << storage[i].street;
					std::cout << std::setw(8) << std::left << storage[i].houseNum;
					std::cout << std::setw(12) << std::left << storage[i].number;
					std::cout << std::setw(6) << std::left << storage[i].plz;
					std::cout << std::setw(10) << std::left << storage[i].city;
					std::cout << std::setw(12) << std::left << storage[i].birthDate;
					std::cout << std::setw(8) << std::left << storage[i].salary << "\n";
				}
				Space();

				optioMain(mainOption);
				break;
			}
		}
		//Costume User Input
		else if (mainOption == "1") {
			while (true) {
				try
				{
					InputQuest("First Name | ", first);
					InputQuest("Last Name | ", last);
					InputQuest("Street | ", street);
					InputQuest("House Number | ", houseNum);
					InputQuest("Phone Number | ", number);
					InputQuest("PLZ | ", plz);
					InputQuest("City | ", city);
					InputQuest("Birth Date | ", birthDate);
					InputQuest("Slary | ", salary);

					storage.push_back(Person{ first, last, street, houseNum,number, plz, city, birthDate, salary });

					Space();

					std::cout << std::setw(77) << std::right << "Person added to Database \n";

					Space();

					optioMain(mainOption);
					break;
				}
				catch (const std::exception&)
				{
					std::cout << std::setw(16) << "[ERROR] Try Again\n\n";
				}
			}
		}
		//User Delete
		else if (mainOption == "2") {
			while (true) {
				for (int i = 0; i < storage.size(); i++) {
					std::cout << std::setw(18) << std::right << i << " | ";
					std::cout << std::setw(12) << std::left << storage[i].first;
					std::cout << std::setw(12) << std::left << storage[i].last;
					std::cout << std::setw(10) << std::left << storage[i].street;
					std::cout << std::setw(8) << std::left << storage[i].houseNum;
					std::cout << std::setw(12) << std::left << storage[i].number;
					std::cout << std::setw(6) << std::left << storage[i].plz;
					std::cout << std::setw(10) << std::left << storage[i].city;
					std::cout << std::setw(12) << std::left << storage[i].birthDate;
					std::cout << std::setw(8) << std::left << storage[i].salary << "\n";
				}

				Space();

				std::cout << std::setw(45) << std::right << "Number to Delete or [E]xit| ";
				std::cin >> option;

				//Checking if the picked number is not out of bounds and Deleting it
				if (option != "E") {
					try
					{
						if (stoi(option) <= storage.size() - 1) {
							//Deleting User by option Selection
							storage.erase(storage.begin() + stoi(option));
							break;
						}
					}
					catch (const std::exception&)
					{
						break;
					}
				}
				else {
					Space();
					optioMain(mainOption);
					break;
				}
				break;
			}
		}
		else mainOption = "0";

	} while (mainOption != "E");
}