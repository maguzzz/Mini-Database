#include <iostream>
#include <string>
#include <vector>

class Person {
public:
	std::string index;
	std::string first;
	std::string last;
	std::string street;
	std::string houseNum;
	std::string number;
	std::string plz;
	std::string city;
	std::string birthDate;
	std::string salary;

	std::string allInfos = { index + "  " + first + "  " + last + "  " + street + "  " + houseNum + "  " + number + "  " + plz + "  " + city + "  " + birthDate + "  " + salary };
};

void Space() {
	std::cout << "\n-------------------------------------------------------------------------------\n\n";
}

void ClearConsole() {
	system("CLS");
}

std::string optioMain(std::string& x) {
	std::cout << "Pick a Option | ";
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
		std::cout << "      [0] Show list      |      [1] New user      |      [2] Delete user      | ";
		Space();

		//Displaying all Users
		if (mainOption == "0") {
			while (true) {
				for (const auto& person : storage) {
					std::cout << person.allInfos << std::endl;
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
					std::cout << "  Enter your First Name| ";
					std::cin >> first;
					std::cout << "   Enter your Last Name| ";
					std::cin >> last;
					std::cout << "      Enter your Street| ";
					std::cin >> street;
					std::cout << "Enter your House Number| ";
					std::cin >> houseNum;
					std::cout << "Enter your Phone Number| ";
					std::cin >> number;
					std::cout << "         Enter your PLZ| ";
					std::cin >> plz;
					std::cout << "        Enter your City| ";
					std::cin >> city;
					std::cout << "  Enter your Birth Date| ";
					std::cin >> birthDate;
					std::cout << "       Enter your Slary| ";
					std::cin >> salary;

					storage.push_back(Person{ first, last, street, houseNum,number, plz, city, birthDate, salary });

					Space();

					std::cout << "Person added to Database \n";

					Space();

					std::cout << "Pick a Option | ";
					std::cin >> mainOption;
					break;
				}
				catch (const std::exception&)
				{
					std::cout << "[ERROR] Try Again\n\n";
				}
			}
		}
		//User Delete
		else if (mainOption == "2") {
			while (true) {
				for (int i = 0; i < storage.size(); i++) {
					std::cout << i << "|" << storage[i].allInfos << std::endl;
				}
				Space();

				std::cout << "Pick a User or [E]xit Delete options | ";
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

					std::cout << "Pick a Option | ";
					optioMain(mainOption);
					break;
				}
				break;
			}
		}
		else mainOption = "0";

	} while (mainOption != "E");
}