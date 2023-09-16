# CMake
## Test
### enable_testing()的作用？
1. 在生成的build system中启用CTest: CTest是CMake自带的测试工具，用于进行自动化测试
2. 允许add_test()命令
3. 在使用build system构建项目时生成test target, 例如Makefiles中的 make test

### add_test()的作用？
1. 基本用法： add_test(NAME test_name COMMAND executable [args...])
2. test_name: 测试名称，需要唯一
3. executable: 运行的测试程序或脚本
4. args：传递给executable的参数
5. executable返回0， CTest会认为测试成功
6. add_test()还有一些高级用法，例如设置测试属性，环境变量等

# GoogleTest
## 如何在main函数里运行测试用例
1. ::testing::InitGoogleTest(&argc, argv) 初始化gtest框架
2. RUN_ALL_TESTS() 运行所有测试

## 基础测试宏
### TEST_F
1. TEST_F是用来定义一个基于test fixture的测试的宏， F代表Fixture
2. 使用步骤：
  * 定义测试夹具类，继承自::testing::Test
  * 定义SetUp(), TearDown()
  * 使用TEST_F定义基于夹具的测试
