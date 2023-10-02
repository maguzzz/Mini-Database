#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <mysql.h>

class Person {
public:
	std::string pos;
	std::string first;
	std::string last;
	std::string street;
	std::string houseNum;
	std::string number;
	std::string plz;
	std::string city;
	std::string birthDate;
};

void Space() {
	std::cout << std::endl << std::setw(114) << std::right << "------------------------------------------------------------------------------------------------\n\n";
}

void ClearConsole() {
	system("CLS");
}

void InputQuest(std::string quest, std::string& x) {
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
	//Connecting to DB

	MYSQL* conn;
	MYSQL_RES* res;
	MYSQL_ROW row;

	conn = mysql_init(NULL);
	conn = mysql_real_connect(conn, "localhost", "root", "Passwort", "db_usermanage", 3306, NULL, 0);


	//Creating a vector with starter data
	std::vector<Person> storage;

	std::string first;
	std::string last;
	std::string street;
	std::string houseNum;
	std::string number;
	std::string plz;
	std::string city;
	std::string birthDate;
	std::string query;

	int posCount = 0;
	std::string mainOption = "0";
	std::string option;


	if (conn) {
		query = "SELECT * FROM tb_user";

		mysql_query(conn, query.c_str());

		MYSQL_RES* res = mysql_store_result(conn);

		while ((row = mysql_fetch_row(res))) {
			storage.push_back(Person{ row[1], row[2], row[3], row[4], row[5], row[6], row[7], row[8], row[9] });
			posCount++;
		}
	}

	do {
		//Showing Options Ui
		ClearConsole();

		if (conn) {
			std::cout << std::setw(30) << std::right << "[DB] CONNECTED" << std::endl;
		}
		else {
			std::cout << std::setw(30) << std::right << "[DB] NO CONNECTION" << std::endl;
		}

		std::cout << "\n" << std::setw(112) << std::right << "|         [0] Show list         |        [1] New user         |         [2] Delete user        |";
		Space();

		//Displaying all Users
		if (mainOption == "0") {
			while (true) {
				for (int i = 0; i < storage.size(); i++) {
					std::cout << std::setw(18) << std::right << "        ";
					std::cout << std::setw(4) << std::left << storage[i].pos;
					std::cout << std::setw(11) << std::left << storage[i].first;
					std::cout << std::setw(11) << std::left << storage[i].last;
					std::cout << std::setw(16) << std::left << storage[i].street;
					std::cout << std::setw(6) << std::left << storage[i].houseNum;
					std::cout << std::setw(14) << std::left << storage[i].number;
					std::cout << std::setw(10) << std::left << storage[i].plz;
					std::cout << std::setw(10) << std::left << storage[i].city;
					std::cout << std::setw(12) << std::left << storage[i].birthDate << "\n";
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

					storage.push_back(Person{ std::to_string(posCount), first, last, street, houseNum,number, plz, city, birthDate });

					query = "INSERT INTO tb_user (pos, firstN, lastN, street, houseNum, number, plz, city, birthdate) VALUES ('" + std::to_string(posCount) + "' , '" + first + "', '" + last + "', '" + street + "', '" + houseNum + "', '" + number + "', '" + plz + "', '" + city + "', '" + birthDate + "')";
					posCount++;

					if (mysql_query(conn, query.c_str())) {
						mysql_close(conn);
					}

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
					std::cout << std::setw(18) << std::right << "        ";
					std::cout << std::setw(4) << std::left << storage[i].pos;
					std::cout << std::setw(11) << std::left << storage[i].first;
					std::cout << std::setw(11) << std::left << storage[i].last;
					std::cout << std::setw(16) << std::left << storage[i].street;
					std::cout << std::setw(6) << std::left << storage[i].houseNum;
					std::cout << std::setw(14) << std::left << storage[i].number;
					std::cout << std::setw(10) << std::left << storage[i].plz;
					std::cout << std::setw(10) << std::left << storage[i].city;
					std::cout << std::setw(12) << std::left << storage[i].birthDate << "\n";
				}

				Space();

				std::cout << std::setw(45) << std::right << "Number to Delete or [E]xit| ";
				std::cin >> option;

				//Checking if the picked number is not out of bounds and Deleting it
				if (option != "E") {
					try
					{
						if (stoi(option) <= storage.size() - 1) {

							//Deleting From DB
							query = "DELETE FROM tb_user WHERE pos = " + option + ";";
							if (mysql_query(conn, query.c_str())) {
								mysql_close(conn);
							}

							//Deleting Form Vector
							storage.erase(storage.begin() + stoi(option));

							//Updating current data
							query = "SELECT * FROM tb_user";
							if (mysql_query(conn, query.c_str())) {
								mysql_close(conn);
							}

							MYSQL_RES* res = mysql_store_result(conn);

							posCount = 0;

							//Updating all Pos numbers
							while ((row = mysql_fetch_row(res))) {
								query = "UPDATE tb_user SET pos = " + std::to_string(posCount) + " WHERE pos = " + std::string(row[1]);
								if (mysql_query(conn, query.c_str())) {
									mysql_close(conn);
								}

								posCount++;
							}
							
							posCount = 0;

							for (int i = 0; i < storage.size(); i++) {
								storage[i].pos = std::to_string(posCount);
								posCount++;
							}

							mysql_free_result(res);

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