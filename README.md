# C++ ORM "tutorial project": programming tasks planner

## UPP

Based upon the [UPP](https://www.ultimatepp.org/) C++ framework.
UPP is a reasonable choice for those who'd like to solve applied problems by themselves.

## ProgTasks

Written by [vns](https://github.com/xpinguin), winter 2019/2020.

Released during the heated discussion with [shvmedia](https://www.instagram.com/shvmedia) and [nihilSup](https://github.com/nihilSup) about pros and cons of ORMs vs Plain SQL<s>, Python vs C++</s>, and so on.

**NB** don't forget to change DB [credentials](https://github.com/xpinguin/ProgTasks/blob/5105ebdff5dba607bd7c59bf2132bb8e5784431f/src/main.cpp#L123)

## Why, man?!

I don't know, I'm tired of useless Python typing annotations, overly complex ORMs and the vibe of unconfidence as any line could fail, unless well-thought. Let's do it in a normal language now.

## How to build

	git clone https://github.com/xpinguin/ProgTasks.git
	cd ProgTasks

### Install dependencies

#### MacOS X

	brew install pkg-config
	brew install bash
	brew install --cask cmake

#### Linux

	...

### Build using CMake

	bash ./bootstrap.sh
	bash ./GenerateCMakeFiles.sh
	mkdir build
	cd build
	cmake-gui ..
	make -j6
	./bin/ProgTasks

## How does it look

### Linux

![image](https://user-images.githubusercontent.com/2728060/145338608-93647f56-543e-4810-97f3-78436784dadd.png)
