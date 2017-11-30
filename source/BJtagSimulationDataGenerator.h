#ifndef BJTAG_SIMULATION_DATA_GENERATOR
#define BJTAG_SIMULATION_DATA_GENERATOR

#include <SimulationChannelDescriptor.h>
#include <string>
class BJtagAnalyzerSettings;

class BJtagSimulationDataGenerator
{
public:
	BJtagSimulationDataGenerator();
	~BJtagSimulationDataGenerator();

	void Initialize( U32 simulation_sample_rate, BJtagAnalyzerSettings* settings );
	U32 GenerateSimulationData( U64 newest_sample_requested, U32 sample_rate, SimulationChannelDescriptor** simulation_channel );

protected:
	BJtagAnalyzerSettings* mSettings;
	U32 mSimulationSampleRateHz;

protected:
	void CreateSerialByte();
	std::string mSerialText;
	U32 mStringIndex;

	SimulationChannelDescriptor mSerialSimulationData;

};
#endif //BJTAG_SIMULATION_DATA_GENERATOR