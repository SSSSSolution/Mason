#include <filesystem>

#ifdef _WIN32
#include <windows.h>
#include <shlobj.h>
#endif

#include <gtest/gtest.h>
#include <core/MApp.h>

class MAppTest : public ::testing::Test {
protected:
    void SetUp() override {
        const char *argv[] = {"test_argv", "--config", "presetCfgInArgsConfig.json"};
        mason::MApp &app = mason::MApp::instance(3, const_cast<char **>(argv), expected_app_name);
    }

    void TearDown() override {
        // cleanup code here
    }

    std::string expected_app_name = "test";
    std::filesystem::path expected_data_dir = "./data";
};

TEST_F(MAppTest, TestAppName) {
    EXPECT_EQ(mason::MApp::instance().app_name(), expected_app_name);
}

TEST_F(MAppTest, TestDataDir) {
    EXPECT_EQ(mason::MApp::instance().data_dir(), expected_data_dir);
}

TEST_F(MAppTest, TestLogDir) {
    EXPECT_EQ(mason::MApp::instance().log_dir(), expected_data_dir / "log");
}

TEST_F(MAppTest, TestTmpDir) {
    EXPECT_EQ(mason::MApp::instance().tmp_dir(), expected_data_dir / "tmp");
}

TEST_F(MAppTest, TestSubDataDir) {
    EXPECT_EQ(mason::MApp::instance().sub_data_dir(), expected_data_dir / "data");
}

TEST_F(MAppTest, TestUserDir) {
    EXPECT_EQ(mason::MApp::instance().user_dir(), expected_data_dir / "user");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
