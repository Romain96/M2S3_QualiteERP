#include <iostream>

#include "../lib/cpptoml.h"

#include "../include/erp_config.h"

using namespace std;

ERPConfig::ERPConfig(string filename)
{
    try{
        this->team = new Team(filename);
    }
	catch(const cpptoml::parse_exception& e)
    {
        cerr << "Team: ";
        throw;
    }
    try{
		auto config = cpptoml::parse_file(filename);

		auto projects = config->get_table_array("projects");
		for(const auto& project: *projects)
		{
			auto name = project->get_as<string>("name").value_or("Unnamed project");
			auto dev_time = project->get_as<int>("dev_time").value_or(0);
			auto managing_time = project->get_as<int>("managing_time").value_or(0);
			cpptoml::local_datetime date;
			auto deadline = project->get_as<cpptoml::local_datetime>("deadline").value_or(date);
			// cout << deadline.day << "/" << deadline.month << "/" << deadline.year << endl;
			this->project_list.push_back(new Project(name, dev_time, managing_time, deadline.year, deadline.month, deadline.day));
		}
	}
	catch(const cpptoml::parse_exception& e)
	{
		cerr << "Project list: ";
        throw;
	}
}

Team* ERPConfig::get_team()
{
    return this->team;
}

vector<Project*> ERPConfig::get_project_list()
{
    return this->project_list;
}