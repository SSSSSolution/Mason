#include "core/MApp.h"

#include <stdexcept>
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#include <shlobj.h>
#endif

#include "CLI11.hpp"

namespace mason {

    MApp &MApp::instance(int argc, char **argv, std::string app_name) {
        static MApp sMApp(argc, argv, app_name);
        return sMApp;
    }

    std::string MApp::app_name() {
        return m_app_name;
    }

    std::filesystem::path MApp::data_dir() {
        return m_data_dir;
    }

    std::filesystem::path MApp::log_dir() {
        return m_log_dir;
    }

    std::filesystem::path MApp::tmp_dir() {
        return m_tmp_dir;
    }

    std::filesystem::path MApp::sub_data_dir() {
        return m_sub_data_dir;
    }

    std::filesystem::path MApp::user_dir() {
        return m_user_dir;
    }

    nlohmann::json MApp::get_config() {
        return m_config;
    }

    MApp::MApp(int argc, char **argv, std::string app_name) {
        // step 1. init data dir and load config
        m_app_name = app_name;

        parse_args(argc, argv);

        if (m_config_path.empty()) {
            m_config_path = find_config_in_working_dir();
        }

        if (!m_config_path.empty()) {
            load_config();
        }

        init_data_dirs();

        if (!is_data_dir_valid()) {
            throw std::runtime_error("Data dir is invalid");
        }

        if (m_config_path.empty() ) {
            if (std::filesystem::exists(m_data_dir / "config.json")) {
                m_config_path = (m_data_dir / "config.json").string();
                load_config();
            }
        }
    }

    void MApp::parse_args(int argc, char **argv) {
        CLI::App cli_parser(m_app_name);
        cli_parser.add_option("-c,--config", m_config_path, "Config file path");

        try {
            cli_parser.parse(argc, argv);
        } catch (const CLI::ParseError &e) {
            cli_parser.exit(e);
        }
    }

    std::filesystem::path MApp::find_config_in_working_dir() {
        std::filesystem::path working_dir = std::filesystem::current_path();
        std::filesystem::path config_path = working_dir / "config.json";
        if (std::filesystem::exists(config_path)) {
            return config_path;
        }
        return "";
    }

    void MApp::load_config() {
        if (m_config_path.empty()) {
            return;
        }

        std::ifstream config_file(m_config_path);
        if (!config_file.is_open()) {
            throw std::runtime_error("Failed to open config file: " + m_config_path.string());
        }

        try {
            config_file >> m_config;
        } catch (const nlohmann::json::parse_error &e) {
            throw std::runtime_error("Failed to parse config file: " + m_config_path.string());
        }
    }

    std::string MApp::get_platform_data_dir() {
#ifdef _WIN32
        char path[MAX_PATH];
        if (SUCCEEDED(SHGetFolderPathA(nullptr, CSIDL_LOCAL_APPDATA, nullptr, 0, path))) {
            return std::string(path) + "\\" + m_app_name;
        }
        return "";
#endif
    }

    static bool create_dir(const std::filesystem::path &dir) {
        try {
            std::filesystem::create_directory(dir);
            return true;
        } catch (...) {
            return false;
        }
    }

    bool MApp::is_data_dir_valid() {
        if (!std::filesystem::exists(m_data_dir)) {
            if (!create_dir(m_data_dir)) {
                return false;
            }
        }

        // test if data dir is writable
        try {
            std::filesystem::path test_file = m_data_dir / "test.tmp";
            std::ofstream test_output(test_file);
            if (test_output) {
                test_output << "test";
                test_output.close();
                std::filesystem::remove(test_file);
            } else {
                return false;
            }
        } catch (...) {
            return false;
        }

        std::vector<std::string> subdirs = {
            "log",
            "tmp",
            "data",
            "user",
        };

        for (const std::string &subdir : subdirs) {
            std::filesystem::path path = m_data_dir / subdir;
            if (!std::filesystem::exists(path)) {
                if (!create_dir(path)) {
                    return false;
                }
            }
        }

        m_log_dir = m_data_dir / "log";
        m_tmp_dir = m_data_dir / "tmp";
        m_sub_data_dir = m_data_dir / "data";
        m_user_dir = m_data_dir / "user";

        return true;
    }

    void MApp::init_data_dirs() {
        if (!m_config_path.empty() && m_config.contains("app") && m_config["app"].contains("data_dir")) {
            m_data_dir = m_config["app"]["data_dir"].get<std::string>();
        } else {
            m_data_dir = get_platform_data_dir();
        }
    }
}
