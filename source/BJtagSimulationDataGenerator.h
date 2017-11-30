#ifndef BJTAG_SIMULTAION_DATA_GENERATOR_H
#define BJTAG_SIMULTAION_DATA_GENERATOR_H

#include <AnalyzerHelpers.h>

class BJtagAnalyzerSettings;

class BJtagSimulationDataGenerator
{
public:
	BJtagSimulationDataGenerator();
	~BJtagSimulationDataGenerator();

	void Initialize(U32 simulation_sample_rate, BJtagAnalyzerSettings* settings);
	U32 GenerateSimulationData( U64 newest_sample_requested, U32 sample_rate, SimulationChannelDescriptor** simulation_channels );

protected:
	BJtagAnalyzerSettings*	mSettings;
	U32						mSimulationSampleRateHz;

	enum { SPACE_TCK = 12 };

protected:

	ClockGenerator mClockGenerator;

	void CreateBJtagTransaction();

	SimulationChannelDescriptorGroup	mBJtagSimulationChannels;

	SimulationChannelDescriptor*	mTms;
	SimulationChannelDescriptor*	mTck;
	SimulationChannelDescriptor*	mTdi;
	SimulationChannelDescriptor*	mTdo;
	SimulationChannelDescriptor*	mTrst;
};

#endif	// BJTAG_SIMULTAION_DATA_GENERATOR_H
