# CPP-PassMan
Simple offline password manager.
This is the MVP version available only with REPL interface for now, which You can find inside the "repl" directory.
---
## Key features
- **Saving/loading** entries to/from **encrypted file**. Encryption realized through the [Libsodium](https://github.com/jedisct1/libsodium).
- **Password generation**. Generated password contains upper- and lowercase letters, numbers and special characters according to common security guidelines. Size can be adjusted.
---
## Usage
### REPL (Read-Eval-Print Loop)
To run build, where You can communicate with the app by typing commands and pressing ENTER until You terminate the program (Ctrl+C or by closing CMD window on Windows),
find the release You want or download the repository and build PassMan executable on Your own.


When the application is started You have access to the following commands with parameters added below of each command (if exists any):
- **help** - prints the info similar to one You are reading right now.
- **add** - adds new entry
  - --help - displays info about following parameters
  - --name - specifies entry name
  - --login - specifies entry login
  - --password - specifies entry password (leave it empty to use generated one)
  - --notes (optional) - specifies notes
- **remove** - removes entry
  - --help - displays info about following parameters
  - --name - specifies the name of entry You want to remove
- **list** - lists loaded entries;
- **storage** - saves/loads entries from the file set in the settings
  - --help - displays info about following parameters
  - --save - saves entries to the file (pass Your main password as a parameter)
  - --load - loads entries from the file (pass Your main password as a parameter)
- **settings** - sets apps settings
  - --help - displays info about following parameters
  - --display - displays all available settings an its values
  - --path - sets path to the file, where data will be stored
  - --gen-pass-size - sets the size of generated passwords
- **generate** - generates new password


Example of usage with parameters:
```
add --name Gmail --login example@gmail.com --password P.@$$!234 --notes "Example of simple note."
```
Example of usage without parameters:
```
add
```