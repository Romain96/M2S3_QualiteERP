#include <string>

#include "../include/cpptoml.h"

class Project{
    public:
        Project();
        Project(std::string name, int dev_time, int managing_time, cpptoml::local_datetime deadline);
        Project(std::string name);

        std::string get_name();
        int get_dev_time();
        int get_managing_time();
        cpptoml::local_datetime get_deadline();
    protected:
        std::string name;
        int dev_time;
        int managing_time;
        cpptoml::local_datetime deadline;
};