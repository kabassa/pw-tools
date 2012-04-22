#pragma once

#include "task.h"

Task^ Task::Clone()
{
	// insted of real cloning we use save / load to a memory stream of the current task ;)
	// we use 9999 as version to make sure saving the max. supported version
	MemoryStream^ ms = gcnew MemoryStream();

	BinaryWriter^ bw = gcnew BinaryWriter(ms);
	BinaryReader^ br = gcnew BinaryReader(ms);

	this->Save(9999, bw);
	Task^ result = gcnew Task(9999, br, 0, nullptr);

	bw->Close();
	br->Close();

	ms->Close();

	return result;
}