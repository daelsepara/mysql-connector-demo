// std::any is available only in C++17
#include <any>
#include <cstdlib>
#include <iostream>

#include "db.hpp"

using namespace std;

int main(void)
{
	// use connection details of your database in the statement below: host, user, password, database
	auto db = DB::Base("tcp://localhost:3306", "user", "password", "database");

	// return the first 10 numbers of the sequence 0 to 99
	std::string query1 = "SELECT * FROM SEQUENCE_TABLE (100) AS SEQ LIMIT 0, 10";

	auto result1 = db.Query(query1.c_str());

	if (result1)
	{
		std::cerr << "Query: " << query1 << std::endl;

		while (result1->next())
		{
			std::cout << result1->getString(1) << std::endl;
		}
	}

	// return the next 10 numbers of the sequence 0 to 99
	std::string query2 = "SELECT * FROM SEQUENCE_TABLE (100) AS SEQ LIMIT ?, ?";

	auto result2 = db.Query(query2.c_str(), {10, 10});

	if (result2)
	{
		std::cerr << "Query: " << query2 << std::endl;
		std::cerr << "Values used for ?, ?: 10, 10" << std::endl;

		while (result2->next())
		{
			std::cout << result2->getString(1) << std::endl;
		}
	}

	return EXIT_SUCCESS;
}
