#include <filesystem>

#ifdef _WIN32
#include <windows.h>
#include <shlobj.h>
#endif

#include <gtest/gtest.h>
#include <core/MApp.h>

static std::filesystem::path get_platform_local_app_data_dir(const std::string &app_name) {
#ifdef _WIN32
    char path[MAX_PATH];
    if (SUCCEEDED(SHGetFolderPathA(nullptr, CSIDL_LOCAL_APPDATA, nullptr, 0, path))) {
        return std::string(path) + "\\" + app_name;
    }
    return "";
#endif
}

class MAppTest : public ::testing::Test {
protected:
    void SetUp() override {
        const char *argv[] = {"test_argv"};
        mason::MApp &app = mason::MApp::instance(1, const_cast<char **>(argv), expected_app_name);
    }

    void TearDown() override {
        // cleanup code here
    }

    std::string expected_app_name = "test";
    std::filesystem::path expected_data_dir = get_platform_local_app_data_dir(expected_app_name);
};

TEST_F(MAppTest, TestAppName) {
    EXPECT_EQ(mason::MApp::instance().get_app_name(), expected_app_name);
}

TEST_F(MAppTest, TestDataDir) {
    EXPECT_EQ(mason::MApp::instance().get_data_dir(), expected_data_dir);
}

TEST_F(MAppTest, TestLogDir) {
    EXPECT_EQ(mason::MApp::instance().get_log_dir(), expected_data_dir / "log");
}

TEST_F(MAppTest, TestTmpDir) {
    EXPECT_EQ(mason::MApp::instance().get_tmp_dir(), expected_data_dir / "tmp");
}

TEST_F(MAppTest, TestSubDataDir) {
    EXPECT_EQ(mason::MApp::instance().get_sub_data_dir(), expected_data_dir / "data");
}

TEST_F(MAppTest, TestUserDir) {
    EXPECT_EQ(mason::MApp::instance().get_user_dir(), expected_data_dir / "user");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
