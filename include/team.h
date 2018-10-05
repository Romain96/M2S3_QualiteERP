#ifndef TEAM_H
#define TEAM_H

#include <string>
#include <vector>
#include "../include/project.h"

class Team{

	public:

		std::vector<std::string> pdgs;
		std::vector<std::string> project_managers;
		std::vector<std::string> duty_coordinators;
		std::vector<std::string> developers;
		int team_efficiency;
        Date starting_date;

		Team();
		Team(
            std::vector<std::string> pdg_list,
			std::vector<std::string> project_manager_list,
			std::vector<std::string> duty_coordinator_list,
			std::vector<std::string> developer_list,
            int team_efficiency,
            Date start_date
			);
		Team(std::string filename);

};

#endif
