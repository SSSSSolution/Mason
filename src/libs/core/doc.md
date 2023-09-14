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