# Настройка VScode
## Действия, которые нужно сделать:
- в корне проекта создать файл *.gitignore* и добавить в него *build* и *.gitignore*
## Список расширений, которые нужно установить:
- Task Runner
- Python
- Pylance
- Live Share
- GitLens
- gitignore
- Docker
- Code Spell Checker
- Clang-Format
- C/C++ Extension Pack



## Конфиг VScode
Этот md файл находится директории .vscode.
Эта директория с её содержимым должна лежать в корне вашего проетка. Содержимое директории - правила сборки кода для IDE


`settings.code-workspace` file:
```json
{
    "folders": [
        {
            "path": "your_path_to_project/courcerepo",
            "name": "courcerepo"
        }
    ],
    "extensions": {
        "recommendations": [
            "ms-vscode.cpptools",
        ]
    },
    "settings": {
        "C_Cpp.intelliSenseEngine": "Default",
        "python.languageServer": "Pylance",
        "search.followSymlinks": false,
        "git.mergeEditor": false,
        "task.autoDetect": "off",
        "typescript.tsc.autoDetect": "off",
        "forbeslindesay-taskrunner.separator": ": ",
		"editor.formatOnSave": true,
		"files.trimTrailingWhitespace": true,
        "files.watcherExclude": {
            "**": true
        },
        "clang-format.executable": "/usr/local/bin/clang-format", // your path to clang-format
        "clang-format.style": "${workspaceFolder}/.clang-format",
    },

    "tasks": {
        "version": "2.0.0",
        "tasks": []
    },
    "launch": {
        "version": "2.0.0",
        "configurations": []
    },
}
```


`c_cpp_properties.json` file:
```json
{
    "configurations": [
        {
            "name": "CMake",
            "compileCommands": "${config:cmake.buildDirectory}/compile_commands.json",
            "configurationProvider": "ms-vscode.cmake-tools"
        }
    ],
    "version": 4
}

```


