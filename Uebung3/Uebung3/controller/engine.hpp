#pragma once

namespace controller {

class Engine{	

public:
	virtual void init(int argc, char** argv) = 0;
	virtual void run() = 0;
};

}