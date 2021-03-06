#ifndef BJTAG_TYPES_H
#define BJTAG_TYPES_H

#include <LogicPublicTypes.h>
#include <AnalyzerResults.h>

#include <stdio.h>

// these define the TAP controller states
const int NUM_TAP_STATES = 16;

enum BJtagTAPState
{
	TestLogicReset,		// the first two states
	RunTestIdle,

	SelectDRScan,		// data register branch
	CaptureDR,
	ShiftDR,
	Exit1DR,
	PauseDR,
	Exit2DR,
	UpdateDR,

	SelectIRScan,		// instruction register branch
	CaptureIR,
	ShiftIR,
	Exit1IR,
	PauseIR,
	Exit2IR,
	UpdateIR,
};

// TAP controller states
class BJtagTAP_Controller
{
private:
	BJtagTAPState	mCurrTAPState;

public:
	BJtagTAP_Controller();

	// Used when initializing the object
	void SetState(BJtagTAPState newState)
	{
		mCurrTAPState = newState;
	}

	// This function implements the TAP state machine transitions.
	// It returns true if the state has changed.
	bool AdvanceState(BitState tms_state);

	BJtagTAPState GetCurrState() const
	{
		return mCurrTAPState;
	}
};

// Contains data that is being shifted on TDI/TDO, and functions for converting that data to strings
struct BJtagShiftedData
{
	U64		mStartSampleIndex;

	std::vector<U8>		mTdiBits;
	std::vector<U8>		mTdoBits;

	static std::string GetStringFromBitStates(const std::vector<U8>& bits, DisplayBase display_base);
	static std::string GetDecimalString(const std::vector<U8>& bits);
	static std::string GetASCIIString(const std::vector<U8>& bits);
	static std::string GetHexOrBinaryString(const std::vector<U8>& bits, DisplayBase display_base);

	std::string GetTDIString(DisplayBase display_base) const
	{
		return GetStringFromBitStates(mTdiBits, display_base);
	}

	std::string GetTDOString(DisplayBase display_base) const
	{
		return GetStringFromBitStates(mTdoBits, display_base);
	}

	std::string GetTDILengthString( bool with_parentheses = true ) const
	{
		U64 bit_count = mTdiBits.size();
		S8 bit_count_buffer[128];
		if( with_parentheses )
			sprintf( bit_count_buffer, "(%llu)", bit_count );
		else
			sprintf( bit_count_buffer, "%llu", bit_count );
		std::string bit_count_string = bit_count_buffer;
		return bit_count_string;
	}

	std::string GetTDOLengthString( bool with_parentheses = true ) const
	{
		U64 bit_count = mTdoBits.size();
		S8 bit_count_buffer[128];
		if( with_parentheses )
			sprintf( bit_count_buffer, "(%llu)", bit_count );
		else
			sprintf( bit_count_buffer, "%llu", bit_count );
		std::string bit_count_string = bit_count_buffer;
		return bit_count_string;
	}

	bool operator < (const BJtagShiftedData& lhs) const
	{
		return mStartSampleIndex < lhs.mStartSampleIndex;
	}
};

#endif	// BJTAG_TYPES_H
