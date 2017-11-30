#ifndef BJTAG_ANALYZER_SETTINGS
#define BJTAG_ANALYZER_SETTINGS

#include <AnalyzerSettings.h>
#include <AnalyzerTypes.h>

class BJtagAnalyzerSettings : public AnalyzerSettings
{
public:
	BJtagAnalyzerSettings();
	virtual ~BJtagAnalyzerSettings();

	virtual bool SetSettingsFromInterfaces();
	void UpdateInterfacesFromSettings();
	virtual void LoadSettings( const char* settings );
	virtual const char* SaveSettings();

	
	Channel mInputChannel;
	U32 mBitRate;

protected:
	std::auto_ptr< AnalyzerSettingInterfaceChannel >	mInputChannelInterface;
	std::auto_ptr< AnalyzerSettingInterfaceInteger >	mBitRateInterface;
};

#endif //BJTAG_ANALYZER_SETTINGS
