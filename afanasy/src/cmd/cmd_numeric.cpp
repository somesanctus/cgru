#include "cmd_numeric.h"

#include "../libafanasy/blockdata.h"
#include "../libafanasy/taskexec.h"
#include "../libafanasy/taskprogress.h"

#define AFOUTPUT
#undef AFOUTPUT
#include "../include/macrooutput.h"

CmdNumericCmd::CmdNumericCmd()
{
	setCmd("numcmd");
	setArgsCount(3);
	setInfo("Test numeric command fill with numbers.");
	setHelp("numcmd [command] [number1] [number2] Fill numeric command with two provided numbers.");
}

CmdNumericCmd::~CmdNumericCmd(){}

bool CmdNumericCmd::v_processArguments( int argc, char** argv, af::Msg &msg)
{
	std::string command = argv[0];
	int number1 = atoi(argv[1]);
	int number2 = atoi(argv[2]);

	std::cout << af::fillNumbers( command, number1, number2);
	std::cout << std::endl;
	return true;
}

CmdNumericGen::CmdNumericGen()
{
	setCmd("numgen");
	setArgsCount(1);
	setInfo("Generate tasks numbers sequence.");
	setHelp("numgen [quantity] Generate tasks numbers sequence.");
}

CmdNumericGen::~CmdNumericGen(){}

bool CmdNumericGen::v_processArguments( int argc, char** argv, af::Msg &msg)
{
	int quantity = atoi(argv[0]);
	if( quantity < 1 )
	{
		AFERROR("Quantity should be a number greater that zero.")
		return false;
	}

	printf("Tasks quantity = %d:\n", quantity);

	af::TaskProgress ** tp = new af::TaskProgress * [quantity];
	for( int i = 0; i < quantity; i++)
	{
		tp[i] = new af::TaskProgress;
		tp[i]->state = AFJOB::STATE_READY_MASK;
	}

	int task;
	while(( task = af::getReadyTaskNumber( quantity, tp, af::BlockData::FNonSequential)) != -1)
	{
		std::cout << " " << task;
	}
	std::cout << std::endl;

	for( int i = 0; i < quantity; i++)
		delete tp[i];
	delete [] tp;

	return true;
}

CmdNumeric::CmdNumeric()
{
	setCmd("num");
	setArgsCount(6);
	setInfo("Generate numeric tasks, find task by frame.");
	setHelp("num [command] [start] [end] [pertask] [increment(by)] [nonsequential] [frame to find] Generate numeric tasks, find task by frame.");
}

CmdNumeric::~CmdNumeric(){}

bool CmdNumeric::v_processArguments( int argc, char** argv, af::Msg &msg)
{
	// Get arguments:
	std::string command = argv[0];

	long long start  = af::stoi(argv[1]);
	long long end    = af::stoi(argv[2]);
	long long fpt    = af::stoi(argv[3]);
	long long inc    = af::stoi(argv[4]);
	long long nonseq = af::stoi(argv[5]);

	bool find_frame_on = argc > 6;
	long long find_frame = 0;
	if( find_frame_on )
		find_frame = af::stoi(argv[6]);

	// Print arguments:
	std::cout << "str:" << start << " end:" << end << " fpt: " << fpt << " inc:" << inc << " nonseq:" << nonseq;
	if( find_frame_on )
		std::cout << " find:" << find_frame;
	std::cout << std::endl;

	// Create block:
	af::BlockData block;
	block.setCommand( command);
	block.setNumeric( start, end, fpt, inc);
	block.setNonSequential( true);

	// Create progresses:
	af::TaskProgress ** tp = new af::TaskProgress * [block.getTasksNum()];
	for( int i = 0; i < block.getTasksNum(); i++)
	{
		tp[i] = new af::TaskProgress;
		tp[i]->state = AFJOB::STATE_READY_MASK;
	}
	// Fill tasks order:
	int * tasks_order = new int[block.getTasksNum()];
	int task; int order = 0;
//	while(( task = af::getReadyTaskNumber( block.getTasksNum(), tp, af::BlockData::FNonSequential)) != -1)
	while(( task = block.getReadyTaskNumber( tp)) != -1)
	{
		if( task < 0 )
		{
			AFERRAR("Task number is less than zero = %d (order=%d)", task, order)
			continue;
		}
		if( task >= block.getTasksNum())
		{
			AFERRAR("Task number is less than zero = %d (order=%d)", task, order)
			continue;
		}
		tasks_order[task] = order;
		order++;
	}

	// Find frame:
	int founded_task = 0;
	bool valid_range = false;
	if( find_frame_on )
		founded_task = block.calcTaskNumber( find_frame, valid_range);

	// Ouptut results:
	for( int t = 0; t < block.getTasksNum(); t++)
	{
		af::TaskExec * taskexec = block.genTask( t);
		std::cout << t << ":\t";
		std::cout << "\"" << taskexec->getCommand() << "\"";
		std::cout << " - " << taskexec->getFramesNum() << " frames";
		std::cout << ", order=" << tasks_order[t];
		if( find_frame_on && ( founded_task == t ))
		{
			std::cout << " - " << find_frame;
			if( ! valid_range )
				std::cout <<  " out-of-range";
		}
		std::cout << std::endl;
		delete taskexec;
	}

	std::cout << "Tasks Quantity = " << block.getTasksNum();
	std::cout << std::endl;

	delete [] tasks_order;

	return true;
}

