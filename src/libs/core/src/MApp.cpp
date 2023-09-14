#include "core/MApp.h"

#include <stdexcept>

namespace mason {

    MApp *MApp::s_mApp = nullptr;
    std::string MApp::s_app_name = "";
    std::string MApp::s_data_dir = "";
    std::string MApp::s_local_data_dir = "";
    std::string MApp::s_temp_dir = "";


    MApp *MApp::instance() {
        return s_mApp;
    }

    std::string MApp::app_name() {
        return s_app_name;
    }

    std::string MApp::data_dir() {
        return s_data_dir;
    }

    std::string MApp::local_data_dir() {
        return s_local_data_dir;
    }

    std::string MApp::temp_dir() {
        return s_temp_dir;
    }

    MApp::MApp(int argc, char **argv, std::string app_name) {
        if (s_mApp != nullptr) {
            throw std::runtime_error("MApp already exists");
        }
        s_mApp = this;
        s_app_name = app_name;

        init_data_dirs(argc, argv);

        // todo: init logger

        // todo: init config

        // todo: load plugins
    }

    void MApp::init_data_dirs(int argc, char **argv) {
        // todo: get data dir from default locations

        // todo: get data dir from config file (config file location is get from args)

        // todo: create data dir if it doesn't exist

        // todo: create local data dir if it doesn't exist

        // todo: create temp dir if it doesn't exist

        // todo: check if data dir is writable

        // todo: check if local data dir is writable

        // todo: check if temp dir is writable
    }
}
