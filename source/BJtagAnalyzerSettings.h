#ifndef BJTAG_ANALYZER_SETTINGS_H
#define BJTAG_ANALYZER_SETTINGS_H

#include <AnalyzerSettings.h>
#include <AnalyzerTypes.h>

#include "BJtagTypes.h"

enum BitOrder
{
	MSB_First,
	LSB_First,
};

class BJtagAnalyzerSettings : public AnalyzerSettings
{
public:
	BJtagAnalyzerSettings();
	virtual ~BJtagAnalyzerSettings();

	virtual bool SetSettingsFromInterfaces();
	virtual void LoadSettings(const char* settings);
	virtual const char* SaveSettings();

	void UpdateInterfacesFromSettings();

	Channel		mTmsChannel;
	Channel		mTckChannel;
	Channel		mTdiChannel;
	Channel		mTdoChannel;
	Channel		mTrstChannel;

	BJtagTAPState	mTAPInitialState;

	BitOrder		mInstructRegBitOrder;
	BitOrder		mDataRegBitOrder;

	bool			mShowBitCount;

protected:
	AnalyzerSettingInterfaceChannel		mTmsChannelInterface;
	AnalyzerSettingInterfaceChannel		mTckChannelInterface;
	AnalyzerSettingInterfaceChannel		mTdiChannelInterface;
	AnalyzerSettingInterfaceChannel		mTdoChannelInterface;
	AnalyzerSettingInterfaceChannel		mTrstChannelInterface;

	AnalyzerSettingInterfaceNumberList	mTAPInitialStateInterface;

	AnalyzerSettingInterfaceNumberList	mInstructRegBitOrderInterface;
	AnalyzerSettingInterfaceNumberList	mDataRegBitOrderInterface;

	AnalyzerSettingInterfaceBool		mShowBitCountInterface;
};

#endif	// BJTAG_ANALYZER_SETTINGS_H
