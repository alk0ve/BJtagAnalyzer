#include "BJtagAnalyzer.h"
#include "BJtagAnalyzerSettings.h"
#include <AnalyzerChannelData.h>

BJtagAnalyzer::BJtagAnalyzer()
:	Analyzer2(),  
	mSettings( new BJtagAnalyzerSettings() ),
	mSimulationInitilized( false )
{
	SetAnalyzerSettings( mSettings.get() );
}

BJtagAnalyzer::~BJtagAnalyzer()
{
	KillThread();
}

void BJtagAnalyzer::SetupResults()
{
	mResults.reset( new BJtagAnalyzerResults( this, mSettings.get() ) );
	SetAnalyzerResults( mResults.get() );
	mResults->AddChannelBubblesWillAppearOn( mSettings->mInputChannel );
}

void BJtagAnalyzer::WorkerThread()
{
	mSampleRateHz = GetSampleRate();

	mSerial = GetAnalyzerChannelData( mSettings->mInputChannel );

	if( mSerial->GetBitState() == BIT_LOW )
		mSerial->AdvanceToNextEdge();

	U32 samples_per_bit = mSampleRateHz / mSettings->mBitRate;
	U32 samples_to_first_center_of_first_data_bit = U32( 1.5 * double( mSampleRateHz ) / double( mSettings->mBitRate ) );

	for( ; ; )
	{
		U8 data = 0;
		U8 mask = 1 << 7;
		
		mSerial->AdvanceToNextEdge(); //falling edge -- beginning of the start bit

		U64 starting_sample = mSerial->GetSampleNumber();

		mSerial->Advance( samples_to_first_center_of_first_data_bit );

		for( U32 i=0; i<8; i++ )
		{
			//let's put a dot exactly where we sample this bit:
			mResults->AddMarker( mSerial->GetSampleNumber(), AnalyzerResults::Dot, mSettings->mInputChannel );

			if( mSerial->GetBitState() == BIT_HIGH )
				data |= mask;

			mSerial->Advance( samples_per_bit );

			mask = mask >> 1;
		}


		//we have a byte to save. 
		Frame frame;
		frame.mData1 = data;
		frame.mFlags = 0;
		frame.mStartingSampleInclusive = starting_sample;
		frame.mEndingSampleInclusive = mSerial->GetSampleNumber();

		mResults->AddFrame( frame );
		mResults->CommitResults();
		ReportProgress( frame.mEndingSampleInclusive );
	}
}

bool BJtagAnalyzer::NeedsRerun()
{
	return false;
}

U32 BJtagAnalyzer::GenerateSimulationData( U64 minimum_sample_index, U32 device_sample_rate, SimulationChannelDescriptor** simulation_channels )
{
	if( mSimulationInitilized == false )
	{
		mSimulationDataGenerator.Initialize( GetSimulationSampleRate(), mSettings.get() );
		mSimulationInitilized = true;
	}

	return mSimulationDataGenerator.GenerateSimulationData( minimum_sample_index, device_sample_rate, simulation_channels );
}

U32 BJtagAnalyzer::GetMinimumSampleRateHz()
{
	return mSettings->mBitRate * 4;
}

const char* BJtagAnalyzer::GetAnalyzerName() const
{
	return "Better JTAG";
}

const char* GetAnalyzerName()
{
	return "Better JTAG";
}

Analyzer* CreateAnalyzer()
{
	return new BJtagAnalyzer();
}

void DestroyAnalyzer( Analyzer* analyzer )
{
	delete analyzer;
}