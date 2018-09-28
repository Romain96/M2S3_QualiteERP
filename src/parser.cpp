#include <iostream>
#include <string>
#include <vector>

#include "../lib/cpptoml.h"

#include "../include/erp_config.h"

using namespace std;

#define DEBUG

#ifdef DEBUG 
#define D(x) x
#else 
#define D(x)
#endif

void debug(ERPConfig *config)
{
	D(cerr << "PDGS:" << endl);
	for(string pdg: config->get_team()->pdgs)
	{
		D(cerr << pdg << endl);
	}
	D(cerr << endl);

	for(Project *p: config->get_project_list())
	{
		D(cerr << p->get_name() << endl);
		D(cerr << p->get_dev_time() << endl);
		D(cerr << p->get_managing_time() << endl);
		D(cerr << p->get_deadline() << endl << endl);
	}
}

int main(int argc, char *argv[]){
	if (argc != 2)
	{
		cerr << "Usage: " << argv[0] << " <config file>";
		return 1;
	}
	try{
		ERPConfig *config = new ERPConfig(argv[1]);
		debug(config);
	}
	catch(const cpptoml::parse_exception& e)
	{
		cerr << e.what() << endl;
		return 1;
	}
	return 0;
}
