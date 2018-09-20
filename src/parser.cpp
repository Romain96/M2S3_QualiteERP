#include <iostream>
#include <string>

#include "../lib/cpptoml.h"
#include "../include/team.h"

using namespace std;

int main(int argc, char *argv[]){
	auto config = cpptoml::parse_file("../data/erp1.toml");
	auto team = config->get_table("team");
	
	auto pdgs = team->get_array_of<string>("pdgs");
	vector<string> pdg_list, project_manager_list,duty_coordinator_list, developer_list;
	cout << "PDGs:" << endl;
	for(const auto& pdg: *pdgs)
	{
		pdg_list.push_back(pdg);
	}
	cout << endl;

	auto project_managers = team->get_array_of<string>("project_managers");
	cout << "Project managers:" << endl;
	for(const auto& project_manager: *project_managers)
	{
		project_manager_list.push_back(project_manager);
	}
	cout << endl;

	auto duty_coordinators = team->get_array_of<string>("duty_coordinators");
	cout << "Duty coordinators:" << endl;
	for(const auto& duty_coordinator: *duty_coordinators)
	{
		duty_coordinator_list.push_back(duty_coordinator);
	}
	cout << endl;
	
	auto developers = team->get_array_of<string>("developers");
	cout << "Developers:" << endl;
	for(const auto& developer: *developers)
	{
		developer_list.push_back(developer);
	}
	cout << endl;

	Team *t = new Team(pdg_list, project_manager_list, duty_coordinator_list, developer_list);

	auto projects = config->get_table_array("projects");
	for(const auto& project: *projects)
	{
		cout << endl << "Project:" << endl;
		auto name = project->get_as<string>("name");
		auto dev_time = project->get_as<int>("dev_time");
		auto managing_time = project->get_as<int>("managing_time");
		cout << "Name: " << *name << endl;
		cout << "Dev time: " << *dev_time << endl;
		cout << "Managing time: " << *managing_time << endl;
	}

	return 1;
}
