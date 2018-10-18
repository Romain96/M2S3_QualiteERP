#include <iostream>
#include "../include/team.h"
#include "../lib/cpptoml.h"

using namespace std;

Team::Team()
{

}

Team::Team(vector<string> pdg_list, vector<string> project_manager_list, vector<string> duty_coordinator_list, vector<string> developer_list, int efficiency, QDate start_date):
    pdgs(pdg_list), project_managers(project_manager_list), duty_coordinators(duty_coordinator_list), developers(developer_list), team_efficiency(efficiency), starting_date(start_date)
{

}

Team::Team(string filename)
{
	try
	{
		auto config = cpptoml::parse_file(filename);
        this->team_efficiency = config->get_as<int>("team_efficiency").value_or(100);
        cpptoml::local_date date;
        auto starting_date = config->get_as<cpptoml::local_date>("starting_date").value_or(date);
        this->starting_date = QDate(starting_date.year, starting_date.month, starting_date.day);
		auto team = config->get_table("team");
		
		auto pdgs = team->get_array_of<string>("pdgs");
		vector<string> pdg_list, project_manager_list,duty_coordinator_list, developer_list;
		for(const auto& pdg: *pdgs)
		{
			this->pdgs.push_back(pdg);
		}

		auto project_managers = team->get_array_of<string>("project_managers");
		for(const auto& project_manager: *project_managers)
		{
			this->project_managers.push_back(project_manager);
		}

		auto duty_coordinators = team->get_array_of<string>("duty_coordinators");
		for(const auto& duty_coordinator: *duty_coordinators)
		{
			this->duty_coordinators.push_back(duty_coordinator);
		}
			
		auto developers = team->get_array_of<string>("developers");
		for(const auto& developer: *developers)
		{
			this->developers.push_back(developer);
		}
	}
	catch(const cpptoml::parse_exception& e)
	{
		cerr << "Team: ";
		throw;
	}
}


