#ifndef MASON_MAPP_H
#define MASON_MAPP_H

#include <string>

#define mApp mason::MApp::instance()

namespace mason {

class MApp {
public:
    static MApp *instance();

    static std::string app_name();

    static std::string data_dir();

    static std::string local_data_dir();

    static std::string temp_dir();

    static std::string config_path();

    static std::string default_config_path();

public:
    MApp(int argc, char **argv, std::string app_name);

private:
    void init_data_dirs(int argc, char **argv);

private:
    static MApp *s_mApp;
    static std::string s_app_name;
    static std::string s_data_dir;
    static std::string s_local_data_dir;
    static std::string s_temp_dir;
};

}

#endif
