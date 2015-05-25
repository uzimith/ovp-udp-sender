******************************************************
* Thanks for using the OpenViBE Skeleton Generator ! *
******************************************************

File generation completed
[Wed May 20 00:35:48 2015]
-------------------------

The generator produced the following files:

The Box class:
- ovpCBoxAlgorithmUDPSender.h
- ovpCBoxAlgorithmUDPSender.cpp
Please put these files in your local repository, in the project of your choice (e.g. Signal Processing or Classification)
     [openvibe-repository]/contrib/plugins/[plugin-project]/src/[my-box-folder]
 
You may have to change the file ovpCBoxAlgorithmUDPSender.h to make it find the included file ovp_defines.h, whose path is related to the project used.
 
Don't forget to declare your box in ovp_main.cpp, in order to make it available in the Designer.
Look in one of the ovp_main.cpp file, you will find examples of such declarations (#include the header, then OVP_Declare_New macro). 
This look something like this:

#include "[my-box-folder]/ovpCBoxAlgorithmUDPSender.h"

...

OVP_Declare_Begin();

...

OVP_Declare_New(OpenViBEPlugins::AcquisitionAndNetworkIO::CBoxAlgorithmUDPSenderDesc);
...

OVP_Declare_End();


If your box doesn't appear in the designer, maybe it's because you cannot see Unstable Boxes.
Try to set your configuration file (openvibe.conf on windows / .openviberc on Linux) with the following token :
>>>>>
Designer_ShowUnstable = true
>>>>>

For more information about implementing algorithms and boxes to fill your skeleton, please read the official tutorial:
http://openvibe.inria.fr/tutorial-1-implementing-a-signal-processing-box/

Feel free to propose your contribution on the forum ! 
http://openvibe.inria.fr/forum/

Enjoy OpenViBE !

- The development team -

## Dependency

I use boost::asio, so you need to add the following code to `CMakeLists.txt`.

---
INCLUDE("FindThirdPartyBoost")
INCLUDE("FindThirdPartyBoost_System")

#so that boost won't need to link against DateTime when using the interprocess communication library
#shared memory writer box
ADD_DEFINITIONS(-DBOOST_DATE_TIME_NO_LIB)
---

---
IF(WIN32)
	ADD_DEFINITIONS(-D_WIN32_WINNT=0x0501) # for boost::asio
ENDIF(WIN32)
---