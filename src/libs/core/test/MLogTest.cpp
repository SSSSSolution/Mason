#include <fstream>

#include "gtest/gtest.h"
#include "core/MApp.h"

class MLogTest : public ::testing::Test {
protected:
    void SetUp() override {
        const char *argv[] = {"test_argv"};
        mason::MApp &app = mason::MApp::instance(1, const_cast<char **>(argv), "test");
        expected_log_path = app.get_log_dir() / "log.txt";
    }

    void TearDown() override {
        // cleanup code here
    }

    std::filesystem::path expected_log_path;

    std::string get_log_contents() {
        std::ifstream ifs(expected_log_path);
        std::string content((std::istreambuf_iterator<char>(ifs)),
                            (std::istreambuf_iterator<char>()));
        return content;
    }
};

TEST_F(MLogTest, TestInitilization) {
    MInfo("test");
    EXPECT_TRUE(std::filesystem::exists(expected_log_path));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
