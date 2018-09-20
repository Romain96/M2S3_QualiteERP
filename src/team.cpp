#include "../include/team.h"

using namespace std;

Team::Team()
{

}

Team::Team(vector<string> pdg_list, vector<string> project_manager_list, vector<string> duty_coordinator_list, vector<string> developer_list):
    pdgs(pdg_list), project_managers(project_manager_list), duty_coordinators(duty_coordinator_list), developers(developer_list)
{

}

