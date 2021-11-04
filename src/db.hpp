#ifndef __DB_HPP__
#define __DB_HPP__

#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#include <any>
#include <vector>

namespace DB
{
	// Base database class
	// ----------------------------------------------------------------------------------------
	//
	// Uses smart pointers so that we do not have to explicitly release, connection, statements
	// to avoid memory leaks. These are released automatically.
	//
	// TODO: Implement exception and error handling as well as facilities for executing queries
	// that do not return any results.
	//
	class Base
	{
	public:
		sql::Driver *driver = NULL;

		std::unique_ptr<sql::Connection> connection = nullptr;

		Base()
		{
			// Get instance of MySQL database driver
			driver = get_driver_instance();
		}

		// Initialize base class and connect to the database
		Base(const char *host, const char *user, const char *password, const char *database)
		{
			driver = get_driver_instance();

			if (driver)
			{
				// Connect to the MySQL instance
				connection.reset(driver->connect(host, user, password));

				if (connection)
				{
					// Set default database
					connection->setSchema(database);
				}
			}
		}

		// Query the database using prepared statements
		std::unique_ptr<sql::ResultSet> Query(const char *query, std::vector<std::any> parameters)
		{
			std::unique_ptr<sql::ResultSet> result = nullptr;

			if (connection)
			{
				std::unique_ptr<sql::PreparedStatement> statement = nullptr;

				statement.reset(connection->prepareStatement(query));

				auto index = 0;

				// insert the values from provided parameters into the query
				for (auto iterator = parameters.begin(); iterator != parameters.end(); iterator++)
				{
					index++;

					if (typeid(int) == iterator->type())
					{
						statement->setInt(index, std::any_cast<int>(*iterator));
					}
					else if (typeid(double) == iterator->type())
					{
						statement->setDouble(index, std::any_cast<double>(*iterator));
					}
					else if (typeid(float) == iterator->type())
					{
						statement->setDouble(index, std::any_cast<float>(*iterator));
					}
					else if (typeid(bool) == iterator->type())
					{
						statement->setBoolean(index, std::any_cast<bool>(*iterator));
					}
					else if (typeid(const char *) == iterator->type())
					{
						statement->setString(index, std::any_cast<const char *>(*iterator));
					}
					else if (typeid(std::string) == iterator->type())
					{
						statement->setString(index, std::any_cast<std::string>(*iterator).c_str());
					}
				}

				// execute the query and return the result set
				if (statement)
				{
					result.reset(statement->executeQuery());
				}
			}

			return result;
		}

		// Query the database
		std::unique_ptr<sql::ResultSet> Query(const char *query)
		{
			std::unique_ptr<sql::ResultSet> result = nullptr;

			// execute the query and return the result set
			if (connection)
			{
				std::unique_ptr<sql::Statement> statement = nullptr;

				statement.reset(connection->createStatement());

				if (statement)
				{
					result.reset(statement->executeQuery(query));
				}
			}

			return result;
		}
	};
};
#endif
