#include <gtest/gtest.h>
#include <core/MApp.h>

class MAppTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialization code here
    }

    void TearDown() override {
        // cleanup code here
    }
};

TEST_F(MAppTest, test1) {
    mason::MApp &app = mason::MApp::instance(0, nullptr, "test");
//    ASSERT_NE(app, nullptr);

}
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
