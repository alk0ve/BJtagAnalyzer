#ifndef BJTAG_ANALYZER_RESULTS_H
#define BJTAG_ANALYZER_RESULTS_H

#include <AnalyzerResults.h>

#include <set>

#include "BJtagTypes.h"

class BJtagAnalyzer;
class BJtagAnalyzerSettings;

class BJtagAnalyzerResults: public AnalyzerResults
{
public:
	BJtagAnalyzerResults(BJtagAnalyzer* analyzer, BJtagAnalyzerSettings* settings);
	virtual ~BJtagAnalyzerResults();

	virtual void GenerateBubbleText(U64 frame_index, Channel& channel, DisplayBase display_base);
	virtual void GenerateExportFile(const char* file, DisplayBase display_base, U32 export_type_user_id);

	virtual void GenerateFrameTabularText(U64 frame_index, DisplayBase display_base);
	virtual void GeneratePacketTabularText(U64 packet_id, DisplayBase display_base);
	virtual void GenerateTransactionTabularText(U64 transaction_id, DisplayBase display_base);

	void AddShiftedData(const BJtagShiftedData& shifted_data);

	// returns the TAP state description
	static const char* GetStateDescLong(const BJtagTAPState mCurrTAPState);
	static const char* GetStateDescShort(const BJtagTAPState mCurrTAPState);

protected:	// functions

protected:	// vars

	BJtagAnalyzerSettings*	mSettings;
	BJtagAnalyzer*			mAnalyzer;

	// TDI/TDO bits
	std::set<BJtagShiftedData>		mShiftedData;
};

#endif	// BJTAG_ANALYZER_RESULTS_H
