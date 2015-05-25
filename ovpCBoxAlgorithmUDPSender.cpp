#include "ovpCBoxAlgorithmUDPSender.h"
#include <boost/asio.hpp>

using namespace OpenViBE;
using namespace OpenViBE::Kernel;
using namespace OpenViBE::Plugins;

using namespace OpenViBEPlugins;
using namespace OpenViBEPlugins::NetworkIO;


using boost::asio::ip::udp;



boolean CBoxAlgorithmUDPSender::initialize(void)
{
	m_oInput0Decoder.initialize(*this, 0);

    m_sHost = FSettingValueAutoCast(*this->getBoxAlgorithmContext(), 0);
    m_uiPort = FSettingValueAutoCast(*this->getBoxAlgorithmContext(), 1);

	return true;
}

boolean CBoxAlgorithmUDPSender::uninitialize(void)
{
	m_oInput0Decoder.uninitialize();

	return true;
}

boolean CBoxAlgorithmUDPSender::processInput(uint32 ui32InputIndex)
{
	// some pre-processing code if needed...

	// ready to process !
	getBoxAlgorithmContext()->markAlgorithmAsReadyToProcess();

	return true;
}

boolean CBoxAlgorithmUDPSender::process(void)
{
	
	IBoxIO& l_rDynamicBoxContext=this->getDynamicBoxContext();

	//iterate over all chunk on input 0
	for(uint32 i=0; i<l_rDynamicBoxContext.getInputChunkCount(0); i++)
	{
		// decode the chunk i
		m_oInput0Decoder.decode(i);
		if(m_oInput0Decoder.isHeaderReceived())
		{
		}
		if(m_oInput0Decoder.isBufferReceived())
		{
			udp::resolver resolver(m_oIOService);
			udp::resolver::query query(udp::v4(), m_sHost.toASCIIString(), std::to_string(m_uiPort));
			udp::endpoint receiver_endpoint = *resolver.resolve(query);
			udp::socket socket(m_oIOService);

			socket.open(udp::v4());


            IStimulationSet* l_pStimulations = m_oInput0Decoder.getOutputStimulationSet();
            for(uint32 j=0; j<l_pStimulations->getStimulationCount(); j++)
            {
                uint64 l_ui64StimulationCode = l_pStimulations->getStimulationIdentifier(j);
                uint64 l_ui64StimulationDate = l_pStimulations->getStimulationDate(j);
                CString l_sStimulationName   = this->getTypeManager().getEnumerationEntryNameFromValue(OV_TypeId_Stimulation, l_ui64StimulationCode);

				this->getLogManager() << LogLevel_Info << "send udp : [" << l_sStimulationName << "]\n";
				socket.send_to(boost::asio::buffer(std::to_string(l_ui64StimulationCode)), receiver_endpoint);
			}
		}
		if(m_oInput0Decoder.isEndReceived())
		{
		}
	}

	return true;
}
