# C++ ORM "tutorial project": programming tasks planner

## UPP

Based upon the [UPP](https://www.ultimatepp.org/) C++ framework.
UPP is a reasonable choice for those who'd like to solve applied problems ny him/herself.

## ProgTasks

Written by [vns01](https://github.com/xpinguin), winter 2019/2020.

Released during the heated discussion with [shvmedia](https://www.instagram.com/shvmedia) and [nihilSup](https://github.com/nihilSup) about pros and cons of ORMs vs Plain SQL<s>, Python vs C++</s>, and so on.

## How to build

	git clone https://github.com/xpinguin/ProgTasks.git
	cd ProgTasks

### Using CMake

	./bootstrap.sh
	./GenerateCMakeFiles.sh
	mkdir build
	cd build
	cmake-gui ..
	make -j6
