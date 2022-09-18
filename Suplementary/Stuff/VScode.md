# Настройка VScode
## Действия, которые нужно сделать:
- Склонируйте репозиторий
- В корне проекта создайте файл `.gitignore`

```
.gitignore
.cmake
build
.cache
.idea
.clang-tidy
*.code-workspace
settings.json
*properties.json
```
---


- Проверьте, есть ли у вас директория `.vscode`. Если нет - создайте её. Содержимое директории - правила сборки кода для IDE
- В `.vscode` создайте следующие файлы:<br />

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
        "clang-format.executable": "your_path_to_clang_format",
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
---
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


## Список расширений, которые нужно установить:
- Task Runner
- Live Share
- GitLens
- gitignore
- Code Spell Checker
- Clang-Format
- C/C++ Extension Pack





