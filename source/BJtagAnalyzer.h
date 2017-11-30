#ifndef BJTAG_ANALYZER_H
#define BJTAG_ANALYZER_H

#include <Analyzer.h>
#include "BJtagAnalyzerResults.h"
#include "BJtagSimulationDataGenerator.h"

class BJtagAnalyzerSettings;
class ANALYZER_EXPORT BJtagAnalyzer : public Analyzer2
{
public:
	BJtagAnalyzer();
	virtual ~BJtagAnalyzer();

	virtual void SetupResults();
	virtual void WorkerThread();

	virtual U32 GenerateSimulationData( U64 newest_sample_requested, U32 sample_rate, SimulationChannelDescriptor** simulation_channels );
	virtual U32 GetMinimumSampleRateHz();

	virtual const char* GetAnalyzerName() const;
	virtual bool NeedsRerun();

protected: //vars
	std::auto_ptr< BJtagAnalyzerSettings > mSettings;
	std::auto_ptr< BJtagAnalyzerResults > mResults;
	AnalyzerChannelData* mSerial;

	BJtagSimulationDataGenerator mSimulationDataGenerator;
	bool mSimulationInitilized;

	//Serial analysis vars:
	U32 mSampleRateHz;
	U32 mStartOfStopBitOffset;
	U32 mEndOfStopBitOffset;
};

extern "C" ANALYZER_EXPORT const char* __cdecl GetAnalyzerName();
extern "C" ANALYZER_EXPORT Analyzer* __cdecl CreateAnalyzer( );
extern "C" ANALYZER_EXPORT void __cdecl DestroyAnalyzer( Analyzer* analyzer );

#endif //BJTAG_ANALYZER_H
