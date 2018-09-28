#include <string>
#include <vector>

#include "team.h"
#include "project.h"

class ERPConfig{
    public:
        ERPConfig();
        ERPConfig(std::string filename);
        Team *get_team();
        std::vector<Project*> get_project_list();
    protected:
        Team *team;
        std::vector<Project*> project_list;
};