## DirBrowser

DirBrowser is a  mix of du and ls unix commands
It's compatible on all unix platforms

### Features
DirBrowser has many features

- Color display
- Hidden files display/hide
- Human readable size
- Mode display
- Nested display of files/folders
- Total size display
- Total number of files/folders display
- ...

### Installation

#### Using make

	make
	sudo make install

#### Using cmake (recommended)
    
    mkdir build&&cd build
    cmake ../
    make
    sudo make install

### Usage

	browsed [options] path

#### Options:
     --help                 : Display help
-a | --hidden               : Display hidden files
-A | --no-hidden            : Hide hidden files
-c | --color                : Color display
-C | --no-color             : No color
-h | --human-readable       : Human readable
-v | --verbose              : Verbose
-V | --no-verbose           : No verbose
-m | --mode                 : Mode display
-M | --no-mode              : No mode display
-l | --list                 : Nested display
-L | --tree                 : No nested display
-f | --follow-links         : Follow links and non regular files
-F | --no-follow-links      : Do not follow links and non regular files
-t | --total                : Total display
-T | --no-total             : No total display
-d | --depth depth          : Maximum recursion  depth 
-y | --file-symbol symbol   : Represent file with symbol
-z | --folder-symbol symbol : Represent folder with symbol
-s | --size                 : Display size for each file
-S | --no-size              : Hide size for each file

