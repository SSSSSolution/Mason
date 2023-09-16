#ifndef MASON_MAPP_H
#define MASON_MAPP_H

#include <string>
#include <filesystem>

#include "core/nlohmann/json.hpp"

#define mApp mason::MApp::instance()

namespace mason {

class MApp {
public:
    static MApp &instance(int argc = 0, char **argv = nullptr, std::string app_name = "");

    std::string app_name();

    std::filesystem::path data_dir();

    std::filesystem::path log_dir();

    std::filesystem::path tmp_dir();

    std::filesystem::path sub_data_dir();

    std::filesystem::path user_dir();

    nlohmann::json get_config();

public:
    MApp(int argc, char **argv, std::string app_name);

private:
    void parse_args(int argc, char **argv);
    std::filesystem::path find_config_in_working_dir();
    void load_config();
    std::string get_platform_data_dir();
    bool is_data_dir_valid();
    void init_data_dirs();


private:
    static MApp *s_mApp;

    std::string m_app_name = "";
    nlohmann::json m_config;
    std::filesystem::path m_config_path = "";

    std::filesystem::path m_data_dir = "";
    std::filesystem::path m_log_dir = "";
    std::filesystem::path m_tmp_dir = "";
    std::filesystem::path m_sub_data_dir = "";
    std::filesystem::path m_user_dir = "";
};

}

#endif
