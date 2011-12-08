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
	-a : display hidden files
	-A : hide hidden files
	-c : color display
	-C : no color
	-h : human readable
	-H : no human readable
	-v : verbose
	-V : no verbose
	-m : mode display
	-M : no mode display
	-l : nested display
	-L : no nested display
	-f : follow links and non regular files
	-F : do not follow links and non regular files
	-t : total display
	-T : no total display
	-d depth : maximum recursion  depth 
	-D : no maximum recursion depth
	-y symbol : represent file with symbol
	-z symbol : represent folder with symbol
    -s : display size for each file
    -S : hide size for each file

