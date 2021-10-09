#include <yaml-cpp/yaml.h>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main()
{
	//read
	YAML::Node config = YAML::LoadFile("config.yaml");
	cout << "name: " << config["name"].as<string>() << endl;
	cout << "sex: " << config["sex"].as<string>() << endl;
	cout << "age: " << config["age"].as<int>() << endl;
	cout << "delete: " << config["delete"].as<string>() << endl;

	std::ofstream fout("config.yaml");

	//add
	config["add"] = "add";

	//change
	config["age"] = 25;

	//delete
	config.remove("delete");

	//write
	fout << config << endl;
	fout.close();
	return 0;
}