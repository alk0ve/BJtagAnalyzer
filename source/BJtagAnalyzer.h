#ifndef BJTAG_ANALYZER_H
#define BJTAG_ANALYZER_H

#include <Analyzer.h>

#include "BJtagAnalyzerSettings.h"
#include "BJtagAnalyzerResults.h"
#include "BJtagSimulationDataGenerator.h"

class BJtagAnalyzer : public Analyzer2
{
public:
	BJtagAnalyzer();
	virtual ~BJtagAnalyzer();
	virtual void WorkerThread();

	virtual U32 GenerateSimulationData(U64 newest_sample_requested, U32 sample_rate, SimulationChannelDescriptor** simulation_channels);
	virtual U32 GetMinimumSampleRateHz();

	virtual const char* GetAnalyzerName() const;
	virtual bool NeedsRerun();
    virtual void SetupResults();

protected:	// functions

	void Setup();
	void SyncToSample(U64 to_sample);

	// advances to the next TCK edge while taking care of transitions on TRST
	void AdvanceTck(Frame& frm, BJtagShiftedData& shifted_data);

	// closes the frame, and handles the tdi/tdo data
	void CloseFrame(Frame& frm, BJtagShiftedData& shifted_data, U64 ending_sample_number);

protected:	// vars

	BJtagAnalyzerSettings				mSettings;
	std::auto_ptr<BJtagAnalyzerResults>	mResults;

	AnalyzerChannelData*	mTms;
	AnalyzerChannelData*	mTck;
	AnalyzerChannelData*	mTdi;
	AnalyzerChannelData*	mTdo;
	AnalyzerChannelData*	mTrst;

	BJtagSimulationDataGenerator mSimulationDataGenerator;

	BJtagTAP_Controller		mTAPCtrl;

	bool mSimulationInitilized;
};

extern "C" ANALYZER_EXPORT const char* __cdecl GetAnalyzerName();
extern "C" ANALYZER_EXPORT Analyzer* __cdecl CreateAnalyzer();
extern "C" ANALYZER_EXPORT void __cdecl DestroyAnalyzer(Analyzer* analyzer);

#endif	// BJTAG_ANALYZER_H
