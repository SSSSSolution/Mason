# App initialization


## Step 1: init data dir and load config

This section outlines the default configurations for the application's data directories and  
configuration files.

### Definitions
  * Working Directory(WorkDir): the directory where the application is executed.
  * Data Directory(DataDir): the central storage location for the application's data,  
    configuration files, logs, etc.

### Configurations File Details
* Loading Priority
  1. Command Line Args
  2. Configuration file inside WorkDir
  3. Configuration file inside DataDir

* Default Content
  ```json
  {
    "data_dir": "<path to data dir>"
  }
  ```
  
* Default Locations
  1. WorkDir
  2. DataDir
  
### Data Directory Details
* Initialization Priority
  1. From the configuration file specified in the command line args
  2. From the configuration file inside WorkDir
  3. From the Platform Default Data Directory

* Default Content
  * 'config.json': Main configuration file
  * 'log/': Log directory
  * 'data/': Data directory
  * 'cache/': Cache directory
  * 'tmp/': Temporary directory
  * 'user/': User directory
  
* Default Locations
  Platform Default Data Directory(For example, %APPDATA% on Windows, $HOME on Linux, etc.)

### Flowchart
  ```mermaid
  ---
  title: App initialization (step1. init data dir and load config)
  ---
  flowchart TD
  
      Start([Start]) --> input[/AppName, Command Line Args/]
      input --> A{Config in args?}
      A -->|Yes| B{Load config}
      A -->|No| C{Config in work dir?}
      C -->|Yes| B
      B --> |Succeeded| E{Data dir in config?}
      B --> |Failed| I([Throw runtime exception])
      E -->|Yes| F[Init data dirs]
      E -->|No| G[Use platform default data dir]
      G -->F
      F --> H{Is data dir valid?}
      H --> |No| I([Throw runtime exception])
      C --> |No| G
      H --> |Yes| J{Config loaded earlier?}
      J --> |No| K[Look up config in data dir]
      J --> |Yes| M([Next step])
      K --> L[Load cfg, If fail, throw exception. If cfg absent, use default]
      L --> M([Next step])
  ```

### chargpt sugesstion
1. 硬编码: 存在一些硬编码的部分，例如 "config.json", "log", "tmp" 等。考虑将这些值提取为常量或配置参数。
2. 错误处理: 当 load_config 或 parse_args 出现问题时，考虑更详细的错误处理，而不仅仅是抛出异常。例如，给出详细的错误信息或提供恢复策略。
3. 线程安全: instance 方法使用了一个静态局部变量来实现单例模式，这在C++11之后是线程安全的。但在多线程程序中使用其他成员变量和函数时，需要注意同步。
4. 单例对象在程序结束时不会被删除。这不是一个真正的问题，因为操作系统会在程序退出时回收内存。但对于某些需要在析构函数中执行特定操作的情况，可能需要考虑如何手动删除该单例或使用智能指针。
5. 考虑将平台相关的代码，如 get_platform_data_dir，移到一个独立的平台抽象层或工具类中，这样可以更容易地添加其他平台的支持。