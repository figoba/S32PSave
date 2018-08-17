

//
//  Values are 32 bit values laid out as follows:
//
//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +---+-+-+-----------------------+-------------------------------+
//  |Sev|C|R|     Facility          |               Code            |
//  +---+-+-+-----------------------+-------------------------------+
//
//  where
//
//      Sev - is the severity code
//
//          00 - Success
//          01 - Informational
//          10 - Warning
//          11 - Error
//
//      C - is the Customer code flag
//
//      R - is a reserved bit
//
//      Facility - is the facility code
//
//      Code - is the facility's status code
//
//
// Define the facility codes
//
#define FACILITY_SYSTEM                  0x0
#define FACILITY_RPC_STUBS               0x3
#define FACILITY_RPC_RUNTIME             0x2
#define PNA_USER                         0x801
#define PNA_PARSER                       0x805
#define PNA_MEASURE                      0x804
#define PNA_LMGR                         0x1
#define PNA_HW                           0x803
#define PNA_GENERAL                      0x808
#define PNA_DISPLAY                      0x806
#define PNA_CHANNEL                      0x807
#define PNA_CAL                          0x802
#define PNA_AME                          0x901
#define FACILITY_IO_ERROR_CODE           0x4


//
// Define the severity codes
//
#define STATUS_SEVERITY_WARNING          0x2
#define STATUS_SEVERITY_SUCCESS          0x0
#define STATUS_SEVERITY_INFORMATIONAL    0x1
#define STATUS_SEVERITY_ERROR            0x3


//
// MessageId: MSG_CAL_QUESTIONABLE
//
// MessageText:
//
// Note: A secondary parameter (power, IFBW, sweeptime, step mode)
// of the calibrated state has changed.
//
#define MSG_CAL_QUESTIONABLE             ((HRESULT)0x68020200L)

//
// MessageId: MSG_CAL_STD_NEEDED
//
// MessageText:
//
// Calibration cannot be completed until you have measured
// all the necessary standards for your selected Cal Type.
//
#define MSG_CAL_STD_NEEDED               ((HRESULT)0x68020201L)

//
// MessageId: MSG_CAL_STATE_NOT_HW_COMPATIBLE
//
// MessageText:
//
// Failed to recall a cal set from an analyzer with a different hardware
// configuration.
//
#define MSG_CAL_STATE_NOT_HW_COMPATIBLE  ((HRESULT)0x68020202L)

//
// MessageId: MSG_CAL_REQUIRED
//
// MessageText:
//
// Calibration is required before correction can be turned on.
// Channel number is %1, Measurement is %2.
//
#define MSG_CAL_REQUIRED                 ((HRESULT)0x68020203L)

//
// MessageId: MSG_CAL_CORRECTION_TURNED_OFF
//
// MessageText:
//
// Critical parameters in your current instrument state do not match the
// parameters for the calibration set, therefore correction has been turned
// off. The critical instrument state parameters are sweep type, start frequency.
// frequency span, and number of points.
//
#define MSG_CAL_CORRECTION_TURNED_OFF    ((HRESULT)0x68020204L)

//
// MessageId: MSG_CAL_CORRECTION_TURNED_OFF_INTERPOLATION_OFF
//
// MessageText:
//
// Interpolation is turned off and you have changed the
// stimulus settings of the original calibration, so
// correction has been turned off.
//
#define MSG_CAL_CORRECTION_TURNED_OFF_INTERPOLATION_OFF ((HRESULT)0x68020205L)

//
// MessageId: MSG_CAL_CORRECTION_RESTORED
//
// MessageText:
//
// Interpolation is turned off and you have selected correction ON.
// Correction has been restored with the previous stimulus settings.
//
#define MSG_CAL_CORRECTION_RESTORED      ((HRESULT)0x68020206L)

//
// MessageId: MSG_CAL_CORRECTION_TURNED_OFF_FREQRANGE_EXCEEDED
//
// MessageText:
//
// Stimulus settings for your current instrument state exceeded the
// parameters of the original calibration, so correction has been turned
// off.
//
#define MSG_CAL_CORRECTION_TURNED_OFF_FREQRANGE_EXCEEDED ((HRESULT)0x68020207L)

//
// MessageId: MSG_CAL_CALTYPE_SET_TO_NONE
//
// MessageText:
//
// Cal Type is set to NONE for Channel %1, Measurement %2; 
// please select Calibration menu or press Cal hard key.
//
#define MSG_CAL_CALTYPE_SET_TO_NONE      ((HRESULT)0x68020208L)

//
// MessageId: MSG_CAL_CORRECTION_TURNED_OFF_NOT_AN_SPARAM
//
// MessageText:
//
// The measurement you set up does not have a corresponding
// calibration type, so correction has been turned off or is not permitted.
//
#define MSG_CAL_CORRECTION_TURNED_OFF_NOT_AN_SPARAM ((HRESULT)0x68020209L)

//
// MessageId: MSG_CAL_TYPE_COULD_NOT_BE_SET
//
// MessageText:
//
// The calibration type you selected cannot be set up.  Please check the
// settings of Channel %1, or select a different calibration type to try again.
//
#define MSG_CAL_TYPE_COULD_NOT_BE_SET    ((HRESULT)0x6802020AL)

//
// MessageId: MSG_CAL_INVALID_PATH
//
// MessageText:
//
// The calibration path you selected cannot be set up because it is
// not valid for the current measurement.  Please use the
// SCPI command ROUTe:PATH:DEFine:PORT <num>,<num> for full 2 port type
// port assignment related to your current measurement.
//
#define MSG_CAL_INVALID_PATH             ((HRESULT)0x6802020BL)

//
// MessageId: MSG_SOURCE_POWER_CAL_COMPLETED
//
// MessageText:
//
// The source power calibration is complete.
//
#define MSG_SOURCE_POWER_CAL_COMPLETED   ((HRESULT)0x6802020CL)

//
// MessageId: MSG_EXCEEDED_MAXNUM_STDS_PER_CLASS
//
// MessageText:
//
// You have specified more than 7 standards for one or more calibration
// classes.  These have been truncated to 7 selections.
//
#define MSG_EXCEEDED_MAXNUM_STDS_PER_CLASS ((HRESULT)0x6802020DL)

//
// MessageId: MSG_PROPERTIES_NO_USER_CAL
//
// MessageText:
//
// No user calibration found for this channel.
//
#define MSG_PROPERTIES_NO_USER_CAL       ((HRESULT)0x6802020EL)

//
// MessageId: MSG_CAL_DOES_NOT_NEED_STD
//
// MessageText:
//
// You do not need to acquire this standard for this calibration type.
//
#define MSG_CAL_DOES_NOT_NEED_STD        ((HRESULT)0x6802020FL)

//
// MessageId: MSG_ECAL_COULD_NOT_CONFIGURE
//
// MessageText:
//
// Could not configure the Electronic Calibration system.  Check to see 
// if the module is plugged into the proper connector.
//
#define MSG_ECAL_COULD_NOT_CONFIGURE     ((HRESULT)0x68020210L)

//
// MessageId: MSG_TOUCHSCREEN_NOT_AVAILABLE
//
// MessageText:
//
// Touchscreen is not available
//
#define MSG_TOUCHSCREEN_NOT_AVAILABLE    ((HRESULT)0x68020211L)

//
// MessageId: MSG_ECAL_ERROR_1
//
// MessageText:
//
// DATA OUT OF RANGE: Design Limits Exceeded
//
#define MSG_ECAL_ERROR_1                 ((HRESULT)0xE8020211L)

//
// MessageId: MSG_ECAL_ERROR_2
//
// MessageText:
//
// EXECUTION ERROR: Could not open ECal module memory backup file
//
#define MSG_ECAL_ERROR_2                 ((HRESULT)0xE8020212L)

//
// MessageId: MSG_ECAL_ERROR_3
//
// MessageText:
//
// EXECUTION ERROR: Access to ECal module memory backup file was denied
//
#define MSG_ECAL_ERROR_3                 ((HRESULT)0xE8020213L)

//
// MessageId: MSG_ECAL_ERROR_4
//
// MessageText:
//
// EXECUTION ERROR: Failure in writing to ECal module memory backup file
//
#define MSG_ECAL_ERROR_4                 ((HRESULT)0xE8020214L)

//
// MessageId: MSG_ECAL_ERROR_5
//
// MessageText:
//
// EXECUTION ERROR: Failure in reading from ECal module memory backup file
//
#define MSG_ECAL_ERROR_5                 ((HRESULT)0xE8020215L)

//
// MessageId: MSG_ECAL_ERROR_6
//
// MessageText:
//
// EXECUTION ERROR: Array index out of range
//
#define MSG_ECAL_ERROR_6                 ((HRESULT)0xE8020216L)

//
// MessageId: MSG_ECAL_ERROR_7
//
// MessageText:
//
// EXECUTION ERROR: Arrays wrong rank
//
#define MSG_ECAL_ERROR_7                 ((HRESULT)0xE8020217L)

//
// MessageId: MSG_ECAL_ERROR_8
//
// MessageText:
//
// EXECUTION ERROR: CPU
//
#define MSG_ECAL_ERROR_8                 ((HRESULT)0xE8020218L)

//
// MessageId: MSG_ECAL_ERROR_9
//
// MessageText:
//
// Error occurred in communicating with the ECal module while writing a new user characterization to its memory.  
// The operation was cancelled and the ECal module's previous memory state may be recovered from the backup file.
//
#define MSG_ECAL_ERROR_9                 ((HRESULT)0xE8020219L)

//
// MessageId: MSG_ECAL_ERROR_10
//
// MessageText:
//
// Attempt to restore the ECal module's memory from backup file failed.  Could not properly communicate with the module.
//
#define MSG_ECAL_ERROR_10                ((HRESULT)0xE802021AL)

//
// MessageId: MSG_ECAL_ERROR_11
//
// MessageText:
//
// EXECUTION ERROR: Entry Not Found
//
#define MSG_ECAL_ERROR_11                ((HRESULT)0xE802021BL)

//
// MessageId: MSG_ECAL_ERROR_12
//
// MessageText:
//
// EXECUTION ERROR: Invalid command while system is busy
//
#define MSG_ECAL_ERROR_12                ((HRESULT)0xE802021CL)

//
// MessageId: MSG_ECAL_ERROR_13
//
// MessageText:
//
// Electronic Cal:  Unable to orient ECal module. Please ensure the module is connected to the necessary measurement ports.
//
#define MSG_ECAL_ERROR_13                ((HRESULT)0xE802021DL)

//
// MessageId: MSG_ECAL_ERROR_14
//
// MessageText:
//
// EXECUTION ERROR: NO SPACE for NEW PNA_CAL, DELETE A PNA_CAL
//
#define MSG_ECAL_ERROR_14                ((HRESULT)0xE802021EL)

//
// MessageId: MSG_ECAL_ERROR_15
//
// MessageText:
//
// EXECUTION ERROR: No More Room
//
#define MSG_ECAL_ERROR_15                ((HRESULT)0xE802021FL)

//
// MessageId: MSG_ECAL_ERROR_16
//
// MessageText:
//
// EXECUTION ERROR: Other array error
//
#define MSG_ECAL_ERROR_16                ((HRESULT)0xE8020220L)

//
// MessageId: MSG_ECAL_ERROR_17
//
// MessageText:
//
// EXECUTION ERROR: Ranks not equal
//
#define MSG_ECAL_ERROR_17                ((HRESULT)0xE8020221L)

//
// MessageId: MSG_ECAL_ERROR_18
//
// MessageText:
//
// EXECUTION ERROR: Too few CONSTANT ranks
//
#define MSG_ECAL_ERROR_18                ((HRESULT)0xE8020222L)

//
// MessageId: MSG_ECAL_ERROR_19
//
// MessageText:
//
// EXECUTION ERROR: Too few VARYing ranks
//
#define MSG_ECAL_ERROR_19                ((HRESULT)0xE8020223L)

//
// MessageId: MSG_ECAL_ERROR_20
//
// MessageText:
//
// EXECUTION ERROR: Unknown error
//
#define MSG_ECAL_ERROR_20                ((HRESULT)0xE8020224L)

//
// MessageId: MSG_ECAL_ERROR_21
//
// MessageText:
//
// EXECUTION ERROR: ecaldrvr.dll bug or invalid module #
//
#define MSG_ECAL_ERROR_21                ((HRESULT)0xE8020225L)

//
// MessageId: MSG_ECAL_ERROR_22
//
// MessageText:
//
// EXECUTION ERROR: unexpected error code from ecal driver
//
#define MSG_ECAL_ERROR_22                ((HRESULT)0xE8020226L)

//
// MessageId: MSG_ECAL_ERROR_23
//
// MessageText:
//
// EXECUTION ERROR: unexpected internal driver error
//
#define MSG_ECAL_ERROR_23                ((HRESULT)0xE8020227L)

//
// MessageId: MSG_ECAL_ERROR_24
//
// MessageText:
//
// HARDWARE ERROR: Can't access ECal Interface Module
//
#define MSG_ECAL_ERROR_24                ((HRESULT)0xE8020228L)

//
// MessageId: MSG_ECAL_ERROR_25
//
// MessageText:
//
// HARDWARE ERROR: Can't release LPT port, reboot
//
#define MSG_ECAL_ERROR_25                ((HRESULT)0xE8020229L)

//
// MessageId: MSG_ECAL_ERROR_26
//
// MessageText:
//
// HARDWARE ERROR: VNA Error
//
#define MSG_ECAL_ERROR_26                ((HRESULT)0xE802022AL)

//
// MessageId: MSG_ECAL_ERROR_27
//
// MessageText:
//
// The selected ECal characterization appears to be corrupt.  Perform a new characterization to overwrite this one.
//
#define MSG_ECAL_ERROR_27                ((HRESULT)0xE802022BL)

//
// MessageId: MSG_ECAL_ERROR_28
//
// MessageText:
//
// OPERATION ABORTED BY HOST COMPUTER
//
#define MSG_ECAL_ERROR_28                ((HRESULT)0xE802022CL)

//
// MessageId: MSG_ECAL_ERROR_29
//
// MessageText:
//
// OPERATION ABORTED BY USER
//
#define MSG_ECAL_ERROR_29                ((HRESULT)0xE802022DL)

//
// MessageId: MSG_ECAL_ERROR_30
//
// MessageText:
//
// OUT OF MEMORY
//
#define MSG_ECAL_ERROR_30                ((HRESULT)0xE802022EL)

//
// MessageId: MSG_ECAL_ERROR_31
//
// MessageText:
//
// QUERY INTERRUPTED: Message(s) Abandoned
//
#define MSG_ECAL_ERROR_31                ((HRESULT)0xE802022FL)

//
// MessageId: MSG_ECAL_ERROR_32
//
// MessageText:
//
// QUERY UNTERMINATED: INCOMPLETE PROGRAM MESSAGE
//
#define MSG_ECAL_ERROR_32                ((HRESULT)0xE8020230L)

//
// MessageId: MSG_ECAL_ERROR_33
//
// MessageText:
//
// QUERY UNTERMINATED: NOTHING TO SAY
//
#define MSG_ECAL_ERROR_33                ((HRESULT)0xE8020231L)

//
// MessageId: MSG_ECAL_ERROR_34
//
// MessageText:
//
// QUEUE OVERFLOW
//
#define MSG_ECAL_ERROR_34                ((HRESULT)0xE8020232L)

//
// MessageId: MSG_ECAL_ERROR_35
//
// MessageText:
//
// Selected cal kit does not have sufficient standards defined for the current frequency range.  Additional standards are needed.
//
#define MSG_ECAL_ERROR_35                ((HRESULT)0xE8020233L)

//
// MessageId: MSG_ECAL_ERROR_36
//
// MessageText:
//
// SETTINGS CONFLICT: Adapter Cal is NOT possible
//
#define MSG_ECAL_ERROR_36                ((HRESULT)0xE8020234L)

//
// MessageId: MSG_ECAL_ERROR_37
//
// MessageText:
//
// SETTINGS CONFLICT: COMMAND OUT OF SEQUENCE
//
#define MSG_ECAL_ERROR_37                ((HRESULT)0xE8020235L)

//
// MessageId: MSG_ECAL_ERROR_38
//
// MessageText:
//
// SETTINGS CONFLICT: Cal STOPPED - VNA SETUP CHANGED
//
#define MSG_ECAL_ERROR_38                ((HRESULT)0xE8020236L)

//
// MessageId: MSG_ECAL_ERROR_39
//
// MessageText:
//
// SETTINGS CONFLICT: Calibration is NOT in progress
//
#define MSG_ECAL_ERROR_39                ((HRESULT)0xE8020237L)

//
// MessageId: MSG_ECAL_ERROR_40
//
// MessageText:
//
// SETTINGS CONFLICT: Can't find specified GPIB board
//
#define MSG_ECAL_ERROR_40                ((HRESULT)0xE8020238L)

//
// MessageId: MSG_ECAL_ERROR_41
//
// MessageText:
//
// SETTINGS CONFLICT: Can't find/load gpib32.dll
//
#define MSG_ECAL_ERROR_41                ((HRESULT)0xE8020239L)

//
// MessageId: MSG_ECAL_ERROR_42
//
// MessageText:
//
// SETTINGS CONFLICT: Can't find/load sicl32.dll
//
#define MSG_ECAL_ERROR_42                ((HRESULT)0xE802023AL)

//
// MessageId: MSG_ECAL_ERROR_43
//
// MessageText:
//
// SETTINGS CONFLICT: Can't initialize VNA (bad address?)
//
#define MSG_ECAL_ERROR_43                ((HRESULT)0xE802023BL)

//
// MessageId: MSG_ECAL_ERROR_44
//
// MessageText:
//
// SETTINGS CONFLICT: Can't load LPT port driver or USB driver DLL
//
#define MSG_ECAL_ERROR_44                ((HRESULT)0xE802023CL)

//
// MessageId: MSG_ECAL_ERROR_45
//
// MessageText:
//
// SETTINGS CONFLICT: Invalid Calibration Sweep Mode.
//
#define MSG_ECAL_ERROR_45                ((HRESULT)0xE802023DL)

//
// MessageId: MSG_ECAL_ERROR_46
//
// MessageText:
//
// SETTINGS CONFLICT: Invalid Calibration Type
//
#define MSG_ECAL_ERROR_46                ((HRESULT)0xE802023EL)

//
// MessageId: MSG_ECAL_ERROR_47
//
// MessageText:
//
// SETTINGS CONFLICT: Invalid Calibration
//
#define MSG_ECAL_ERROR_47                ((HRESULT)0xE802023FL)

//
// MessageId: MSG_ECAL_ERROR_48
//
// MessageText:
//
// SETTINGS CONFLICT: Invalid GPIB board number specified
//
#define MSG_ECAL_ERROR_48                ((HRESULT)0xE8020240L)

//
// MessageId: MSG_ECAL_ERROR_49
//
// MessageText:
//
// SETTINGS CONFLICT: Invalid GPIB board type specified
//
#define MSG_ECAL_ERROR_49                ((HRESULT)0xE8020241L)

//
// MessageId: MSG_ECAL_ERROR_50
//
// MessageText:
//
// SETTINGS CONFLICT: Invalid Module Status
//
#define MSG_ECAL_ERROR_50                ((HRESULT)0xE8020242L)

//
// MessageId: MSG_ECAL_ERROR_51
//
// MessageText:
//
// SETTINGS CONFLICT: Invalid States
//
#define MSG_ECAL_ERROR_51                ((HRESULT)0xE8020243L)

//
// MessageId: MSG_ECAL_ERROR_52
//
// MessageText:
//
// SETTINGS CONFLICT: LPT port must be between 1 and 4
//
#define MSG_ECAL_ERROR_52                ((HRESULT)0xE8020244L)

//
// MessageId: MSG_ECAL_ERROR_53
//
// MessageText:
//
// Could not configure the Electronic Calibration system.  Check to see if the module is properly connected.
//
#define MSG_ECAL_ERROR_53                ((HRESULT)0xE8020245L)

//
// MessageId: MSG_ECAL_ERROR_54
//
// MessageText:
//
// SETTINGS CONFLICT: Specified LPT port does not exist
//
#define MSG_ECAL_ERROR_54                ((HRESULT)0xE8020246L)

//
// MessageId: MSG_ECAL_ERROR_55
//
// MessageText:
//
// SETTINGS CONFLICT: Use frequency domain for cal
//
#define MSG_ECAL_ERROR_55                ((HRESULT)0xE8020247L)

//
// MessageId: MSG_ECAL_ERROR_56
//
// MessageText:
//
// SETTINGS CONFLICT: Use step sweep type for cal.
//
#define MSG_ECAL_ERROR_56                ((HRESULT)0xE8020248L)

//
// MessageId: MSG_ECAL_ERROR_57
//
// MessageText:
//
// SETTINGS CONFLICT: VNA address must be between 0 and 30
//
#define MSG_ECAL_ERROR_57                ((HRESULT)0xE8020249L)

//
// MessageId: MSG_ECAL_ERROR_58
//
// MessageText:
//
// SETTINGS CONFLICT: Wrong LPT port driver or USB driver DLL
//
#define MSG_ECAL_ERROR_58                ((HRESULT)0xE802024AL)

//
// MessageId: MSG_ECAL_ERROR_59
//
// MessageText:
//
// SYNTAX ERROR: ECAL:DELAY command must have 2 numbers
//
#define MSG_ECAL_ERROR_59                ((HRESULT)0xE802024BL)

//
// MessageId: MSG_ECAL_ERROR_60
//
// MessageText:
//
// SYNTAX ERROR: INCORRECT SYNTAX
//
#define MSG_ECAL_ERROR_60                ((HRESULT)0xE802024CL)

//
// MessageId: MSG_ECAL_ERROR_61
//
// MessageText:
//
// SYNTAX ERROR: UNKNOWN COMMAND
//
#define MSG_ECAL_ERROR_61                ((HRESULT)0xE802024DL)

//
// MessageId: MSG_ECAL_ERROR_62
//
// MessageText:
//
// EXECUTION ERROR: Wrong port of module in RF path
//
#define MSG_ECAL_ERROR_62                ((HRESULT)0xE802024EL)

//
// MessageId: MSG_ECAL_ERROR_63
//
// MessageText:
//
// EXECUTION ERROR: User characterization not found in module
//
#define MSG_ECAL_ERROR_63                ((HRESULT)0xE802024FL)

//
// MessageId: MSG_SOURCE_POWER_CAL_NOT_PRESENT
//
// MessageText:
//
// No source power calibration found for the channel and source port 
// of the current measurement.
//
#define MSG_SOURCE_POWER_CAL_NOT_PRESENT ((HRESULT)0x68020250L)

//
// MessageId: MSG_SOURCE_POWER_CAL_NOT_COMPLETE
//
// MessageText:
//
// A source power calibration sweep was not performed, so there is no 
// correction for the channel and source port of the current measurement.
//
#define MSG_SOURCE_POWER_CAL_NOT_COMPLETE ((HRESULT)0x68020251L)

//
// MessageId: MSG_SOURCE_POWER_CAL_REMOVE_TRACE
//
// MessageText:
//
// A new trace could not be added to the active window for viewing the source 
// power cal sweep, because it would have exceeded the limit on number of 
// traces/window. Please remove a trace from the window before proceeding 
// with source power cal.
//
#define MSG_SOURCE_POWER_CAL_REMOVE_TRACE ((HRESULT)0x68020252L)

//
// MessageId: MSG_SOURCE_POWER_CAL_REMOVE_MEAS
//
// MessageText:
//
// A new measurement could not be added for performing the source power cal 
// sweep, because the limit on number of measurements has been reached. 
// Please remove a measurement before proceeding with source power cal.
//
#define MSG_SOURCE_POWER_CAL_REMOVE_MEAS ((HRESULT)0x68020253L)

//
// MessageId: MSG_SOURCE_POWER_CAL_POWER_CHANGED
//
// MessageText:
//
// The calibration power value associated with the source power calibration 
// of Port %1 on Channel %2 was changed with the calibration on. 
// The calibration was not turned off, but the power value might no longer 
// represent the calibration.
//
#define MSG_SOURCE_POWER_CAL_POWER_CHANGED ((HRESULT)0x68020254L)

//
// MessageId: MSG_SOURCE_POWER_CAL_ACQUISITION_ERROR
//
// MessageText:
//
// %1
//
#define MSG_SOURCE_POWER_CAL_ACQUISITION_ERROR ((HRESULT)0x68020255L)

//
// MessageId: MSG_INSUFFICIENT_SLIDE_MOVEMENT
//
// MessageText:
//
// During the acquisition of the sliding load standard,
// the slide was not properly moved to perform a circle fit.  The
// standard's raw impedance was used to determine the directivity
// for one or more points.
//
#define MSG_INSUFFICIENT_SLIDE_MOVEMENT  ((HRESULT)0x68020256L)

//
// MessageId: MSG_NO_FREE_CHANNEL
//
// MessageText:
//
// This feature requires an unused channel, but could not find one.
// Please free up a channel and try again.
//
#define MSG_NO_FREE_CHANNEL              ((HRESULT)0x68020257L)

//
// MessageId: MSG_CAL_CORRECTION_TURNED_OFF_SEGMENT_SWEEP
//
// MessageText:
//
// Interpolation of the original calibration is not allowed since it was
// performed using Segment Sweep.  Correction has been turned off.
//
#define MSG_CAL_CORRECTION_TURNED_OFF_SEGMENT_SWEEP ((HRESULT)0x68020258L)

//
// MessageId: MSG_CAL_WIZARD_PREFERENCES_SAVED
//
// MessageText:
//
// Cal preferences saved.
// 
// Cal preference settings can be changed from the
// 'Cal Preferences' drop down Cal menu.
//
#define MSG_CAL_WIZARD_PREFERENCES_SAVED ((HRESULT)0x68020259L)

//
// MessageId: MSG_CAL_SEQUENCE_RECOMPUTED
//
// MessageText:
//
// The recalled calibration sequence was recomputed because the 
// channel's stimulus now differs from the saved stimulus, or 
// because of hardware difference between this PNA and the PNA 
// the cal sequence was saved on.
//
#define MSG_CAL_SEQUENCE_RECOMPUTED      ((HRESULT)0x6802025AL)

//
// MessageId: MSG_MUST_MEASURE_ADDITIONAL_STDS
//
// MessageText:
//
// Additional Calibration Standards need to be acquired in order to calibrate
// over the entire frequency range currently being measured.
//
#define MSG_MUST_MEASURE_ADDITIONAL_STDS ((HRESULT)0x6802025BL)

//
// MessageId: MSG_TESTSET_PORT_CHANGE_TURNED_SOURCE_POWER_CAL_OFF
//
// MessageText:
//
// Source power correction was turned off in the channel because of a change
// in logical testset or testset port mapping.
//
#define MSG_TESTSET_PORT_CHANGE_TURNED_SOURCE_POWER_CAL_OFF ((HRESULT)0x6802025CL)

//
// MessageId: MSG_FREQ_OUTSIDE_FACTORY_CHARACTERIZATION_RANGE
//
// MessageText:
//
// Frequencies of the channel are outside the range of
// the ECal module factory characterization (%1).  If the frequencies
// exceed the nominal range for the module's internal states or
// connectors, the user characterization quality is likely to be degraded.
//
#define MSG_FREQ_OUTSIDE_FACTORY_CHARACTERIZATION_RANGE ((HRESULT)0x6802025DL)

//
// MessageId: E_NA_CALTYPE_NONE
//
// MessageText:
//
// CalType not set.
//
#define E_NA_CALTYPE_NONE                ((HRESULT)0xE8020260L)

//
// MessageId: E_NA_CAL_NOTIMPL
//
// MessageText:
//
// The Calibration feature requested is not implemented.
//
#define E_NA_CAL_NOTIMPL                 ((HRESULT)0xE8020261L)

//
// MessageId: E_NA_CAL_CLASS_NOT_VALID_FOR_CALTYPE
//
// MessageText:
//
// The Calibration Class Acquisition requested is not valid for the selected Calibration Type.
// Please select a different acquisition or a different Calibration Type.
//
#define E_NA_CAL_CLASS_NOT_VALID_FOR_CALTYPE ((HRESULT)0xE8020262L)

//
// MessageId: E_NA_STANDARD_NOT_FOUND
//
// MessageText:
//
// The Calibration Standard data required for the selected caltype was not found.
//
#define E_NA_STANDARD_NOT_FOUND          ((HRESULT)0xE8020263L)

//
// MessageId: E_NA_ETERM_NOT_FOUND
//
// MessageText:
//
// The Error Term data required for the selected caltype was not found.
//
#define E_NA_ETERM_NOT_FOUND             ((HRESULT)0xE8020264L)

//
// MessageId: E_NA_CALSET_NOT_FOUND
//
// MessageText:
//
// The Calibration data set was not found.
//
#define E_NA_CALSET_NOT_FOUND            ((HRESULT)0xE8020265L)

//
// MessageId: E_NA_CALTYPE_NOT_VALID_FOR_CONFIDENCE_CHECK
//
// MessageText:
//
// The specified measurement does not have a calibration valid for Confidence Check.
// Please select a different measurement, or recall or perform a different Calibration Type.
//
#define E_NA_CALTYPE_NOT_VALID_FOR_CONFIDENCE_CHECK ((HRESULT)0xE8020266L)

//
// MessageId: S_NA_CALSET_CREATED
//
// MessageText:
//
// New calset created.
//
#define S_NA_CALSET_CREATED              ((HRESULT)0x68020267L)

//
// MessageId: E_NA_AUTOPORTEXT_SWEEPTYPE
//
// MessageText:
//
// Automatic Port Extension cannot be performed with Power Sweep or CW Time Sweep Types.
//
#define E_NA_AUTOPORTEXT_SWEEPTYPE       ((HRESULT)0xE8020268L)

//
// MessageId: E_NA_CALSET_FILE_NOT_VALID
//
// MessageText:
//
// The calset file: %1 appears to be corrupted and cannot be removed.
// Exit the application, remove the file, and restart. 
//
#define E_NA_CALSET_FILE_NOT_VALID       ((HRESULT)0xE8020269L)

//
// MessageId: E_NA_GUIDED_POWER_CAL_NOT_ENABLED
//
// MessageText:
//
// Power calibration must be enabled for the guided calibration before the power calibration settings can be modified.
//
#define E_NA_GUIDED_POWER_CAL_NOT_ENABLED ((HRESULT)0xE802026AL)

//
// MessageId: E_NA_CALSET_LOAD_FAILED
//
// MessageText:
//
// The calset file: %1 load failed.
//
#define E_NA_CALSET_LOAD_FAILED          ((HRESULT)0xE802027AL)

//
// MessageId: E_NA_CALSET_SAVE_FAILED
//
// MessageText:
//
// Failed to save calset data:  %1
//
#define E_NA_CALSET_SAVE_FAILED          ((HRESULT)0xE802027BL)

//
// MessageId: S_NA_CALSET_DELETED
//
// MessageText:
//
// A calset was deleted.
//
#define S_NA_CALSET_DELETED              ((HRESULT)0x6802027CL)

//
// MessageId: E_NA_CALSET_FILE_NOT_COMPATIBLE
//
// MessageText:
//
// The version of the calset file: %1 is not compatible with the 
// current instrument.  
//
#define E_NA_CALSET_FILE_NOT_COMPATIBLE  ((HRESULT)0xE802027DL)

//
// MessageId: S_NA_PARTIAL_CALSET_LOAD
//
// MessageText:
//
// Incompatible CalSets found: %1 of %2 stored calsets have been loaded.
//
#define S_NA_PARTIAL_CALSET_LOAD         ((HRESULT)0x6802027EL)

//
// MessageId: S_NA_NEW_CALSET_FILE_CREATED
//
// MessageText:
//
// The Calset file: %1 was not found.  A new file has been created.
//
#define S_NA_NEW_CALSET_FILE_CREATED     ((HRESULT)0x6802027FL)

//
// MessageId: E_NA_CAL_SET_IN_USE
//
// MessageText:
//
// The Calset specified is currently in use.
//
#define E_NA_CAL_SET_IN_USE              ((HRESULT)0xE8020280L)

//
// MessageId: E_NA_CALSET_ACCESS_DENIED
//
// MessageText:
//
// The calset specified has not been opened.
//
#define E_NA_CALSET_ACCESS_DENIED        ((HRESULT)0xE8020281L)

//
// MessageId: E_NA_MAX_CALSETS
//
// MessageText:
//
// The maximum number of cal sets has been reached.  
// Delete old or unused cal sets before attempting to create new ones.
//
#define E_NA_MAX_CALSETS                 ((HRESULT)0xE8020282L)

//
// MessageId: E_NA_POWER_LOSS_SEGMENT_NOT_FOUND
//
// MessageText:
//
// The requested power loss table segment was not found.
//
#define E_NA_POWER_LOSS_SEGMENT_NOT_FOUND ((HRESULT)0xE8020283L)

//
// MessageId: E_NA_CAL_COULD_NOT_TURN_ON
//
// MessageText:
//
// A valid calibration is required before correction can be turned on.
//
#define E_NA_CAL_COULD_NOT_TURN_ON       ((HRESULT)0xE8020284L)

//
// MessageId: S_NA_OLD_VERSION_CAL_DATA_NOT_RESTORED
//
// MessageText:
//
// The cal data for %1 is incompatible and was not restored. Please recalibrate.
//
#define S_NA_OLD_VERSION_CAL_DATA_NOT_RESTORED ((HRESULT)0xA8020285L)

//
// MessageId: E_NA_CALSET_VERSION
//
// MessageText:
//
// CalSet not loaded, version is too new.
//
#define E_NA_CALSET_VERSION              ((HRESULT)0xE8020286L)

//
// MessageId: E_NA_NO_CUSTOM_CAL
//
// MessageText:
//
// Custom cal type not found.
//
#define E_NA_NO_CUSTOM_CAL               ((HRESULT)0xE8020287L)

//
// MessageId: S_NA_DEFER_INTERPOLATION
//
// MessageText:
//
// Custom correction algorithm defers to the client for interpolation.
//
#define S_NA_DEFER_INTERPOLATION         ((HRESULT)0x68020288L)

//
// MessageId: E_NA_CUSTOM_CAL_EXCEPTION
//
// MessageText:
//
// Custom cal dll threw an exception.
//
#define E_NA_CUSTOM_CAL_EXCEPTION        ((HRESULT)0xE8020289L)

//
// MessageId: E_NA_COULD_NOT_LOAD_ECAL_DLL
//
// MessageText:
//
// Could not load the ecal.dll library
//
#define E_NA_COULD_NOT_LOAD_ECAL_DLL     ((HRESULT)0xE802028AL)

//
// MessageId: E_NA_INVALID_CAL_TYPE
//
// MessageText:
//
// The argument specified is not a valid cal type.
//
#define E_NA_INVALID_CAL_TYPE            ((HRESULT)0xE8020290L)

//
// MessageId: S_NA_INTERPOLATED
//
// MessageText:
//
// The function found existing interpolated data.
//
#define S_NA_INTERPOLATED                ((HRESULT)0x68020291L)    

//
// MessageId: S_NA_NEW_INTERPOLATION
//
// MessageText:
//
// The function computed new interpolation values.
//
#define S_NA_NEW_INTERPOLATION           ((HRESULT)0x68020292L)    

//
// MessageId: E_NA_SOURCE_POWER_MEASUREMENT_ERROR
//
// MessageText:
//
// The source power measurement failed.
// Please check power meter remote interface connections and settings, and sensor connections.
//
#define E_NA_SOURCE_POWER_MEASUREMENT_ERROR ((HRESULT)0xE8020293L)

//
// MessageId: E_NA_DUPLICATE_SESSION
//
// MessageText:
//
// Duplicate session found.  Close session and retry.
//
#define E_NA_DUPLICATE_SESSION           ((HRESULT)0xE8020294L)

//
// MessageId: E_NA_NO_SESSION
//
// MessageText:
//
// The session does not exist.  Open the session and try again.
//
#define E_NA_NO_SESSION                  ((HRESULT)0xE8020295L)

//
// MessageId: E_NA_FAILED_TO_LAUNCH_CUSTOM_CAL
//
// MessageText:
//
// Attempt to launch a custom calibration failed.
//
#define E_NA_FAILED_TO_LAUNCH_CUSTOM_CAL ((HRESULT)0xE8020296L)

//
// MessageId: E_NA_CAL_STANDARD_ACQUISITION_FAILED
//
// MessageText:
//
// Request to measure a cal standard failed.
// Please ensure you are requesting to measure standards 
// which are defined for this calibration.
//
#define E_NA_CAL_STANDARD_ACQUISITION_FAILED ((HRESULT)0xE8020297L)

//
// MessageId: E_NA_ECAL_ALREADY_SELECTED
//
// MessageText:
//
// Since Electronic Calibration Kit is selected, Mechanical Cal Kit parameter cannot be changed.
//
#define E_NA_ECAL_ALREADY_SELECTED       ((HRESULT)0xE8020298L)

//
// MessageId: E_NA_INVALID_CHARACTERIZATION_FREQ_RANGE
//
// MessageText:
//
// Frequencies of the active channel are below minimum or above maximum
// frequencies of the ECal module factory characterization.
// Change the channel frequencies, or select another ECal module.
//
#define E_NA_INVALID_CHARACTERIZATION_FREQ_RANGE ((HRESULT)0xE8020299L)

//
// MessageId: E_NA_INVALID_CHARACTERIZATION_CALTYPE
//
// MessageText:
//
// Calset chosen for characterizing the ECal Module 
// Ports %1 does not contain a calibration for PNA Ports %2. Go
// Back to select another calset or to perform another cal.
//
#define E_NA_INVALID_CHARACTERIZATION_CALTYPE ((HRESULT)0xE802029AL)

//
// MessageId: E_NA_TOO_MANY_CHARACTERIZATION_POINTS
//
// MessageText:
//
// ECal module only has sufficient memory remaining to store a
// maximum of %1 points in User Characterization %2.
// Decrease your number of points, or choose to overwrite 
// another user characterization.
//
#define E_NA_TOO_MANY_CHARACTERIZATION_POINTS ((HRESULT)0xE802029BL)

//
// MessageId: E_NA_NON_MONOTONIC
//
// MessageText:
//
// Input values are non-monotonic. Cannot interpolate.
//
#define E_NA_NON_MONOTONIC               ((HRESULT)0xE802029CL)

//
// MessageId: E_NA_INTERPOLATION_OUT_OF_RANGE
//
// MessageText:
//
// Interpolation target is out of range. Cannot interpolate.
//
#define E_NA_INTERPOLATION_OUT_OF_RANGE  ((HRESULT)0xE802029DL)

//
// MessageId: E_NA_REMOTE_GUIDED_CALIBRATION_ERROR
//
// MessageText:
//
// Guided Calibration Error:  %1.
//
#define E_NA_REMOTE_GUIDED_CALIBRATION_ERROR ((HRESULT)0xE802029EL)

//
// MessageId: E_NA_FIRST_CALL_INITIALIZE
//
// MessageText:
//
// The first call to the guided calibration interface must be Initialize.
//
#define E_NA_FIRST_CALL_INITIALIZE       ((HRESULT)0xE802029FL)

//
// MessageId: E_NA_INVALID_CAL_METHOD
//
// MessageText:
//
// The selected thru cal method was not recognized.
//
#define E_NA_INVALID_CAL_METHOD          ((HRESULT)0xE80202A0L)

//
// MessageId: E_NA_COULD_NOT_GENERATE_ERROR_TERMS
//
// MessageText:
//
// Could not generate the error terms.
//
#define E_NA_COULD_NOT_GENERATE_ERROR_TERMS ((HRESULT)0xE80202A1L)

//
// MessageId: E_NA_MUST_USE_ACTIVE_CHANNEL
//
// MessageText:
//
// Guided calibration must be performed on the active channel
//
#define E_NA_MUST_USE_ACTIVE_CHANNEL     ((HRESULT)0xE80202A2L)

//
// MessageId: E_NA_FIRST_CALL_GENERATE_STEPS
//
// MessageText:
//
// You can not start using calibration steps until you have successfully called generate steps
//
#define E_NA_FIRST_CALL_GENERATE_STEPS   ((HRESULT)0xE80202A3L)

//
// MessageId: E_NA_STEP_NUMBER_OUT_OF_RANGE
//
// MessageText:
//
// The step number given is out of range. Step numbers should be between 1 and the number of steps. 
// 0 is not a valid step number.
//
#define E_NA_STEP_NUMBER_OUT_OF_RANGE    ((HRESULT)0xE80202A4L)

//
// MessageId: S_NA_CALSET_SELECTED_NO_RESTORE
//
// MessageText:
//
// A calset was selected for channel:  %1, without restoring stimulus.
//
#define S_NA_CALSET_SELECTED_NO_RESTORE  ((HRESULT)0x680202A5L)

//
// MessageId: S_NA_CALSET_RESTORED
//
// MessageText:
//
// A calset was selected for channel:  %1, restoring stimulus.
//
#define S_NA_CALSET_RESTORED             ((HRESULT)0x680202A6L)

//
// MessageId: E_NA_CALSET_NOT_APPLICABLE
//
// MessageText:
//
// The selected calset stimulus could not be applied to the channel. 
//
#define E_NA_CALSET_NOT_APPLICABLE       ((HRESULT)0x680202A7L)

//
// MessageId: E_NA_FREQ_OUTSIDE_THIS_SENSOR_RANGE
//
// MessageText:
//
// You attempted to measure power at a frequency outside the frequency 
// range defined for the specified power sensor.
// Select another sensor or adjust the range for this sensor.
//
#define E_NA_FREQ_OUTSIDE_THIS_SENSOR_RANGE ((HRESULT)0xE80202A8L)

//
// MessageId: E_NA_FREQ_OUTSIDE_ALL_SENSOR_RANGES
//
// MessageText:
//
// Specified frequency is outside the frequency ranges
// currently defined for the power meter's sensors.
//
#define E_NA_FREQ_OUTSIDE_ALL_SENSOR_RANGES ((HRESULT)0xE80202A9L)

//
// MessageId: E_NA_ADDITIONAL_STDS_REQUIRED
//
// MessageText:
//
// Additional Calibration Standards need to be acquired in order to calibrate
// over the entire frequency range currently being measured.
//
#define E_NA_ADDITIONAL_STDS_REQUIRED    ((HRESULT)0xE80202AAL)

//
// MessageId: E_NA_FAILED_CONVERSION_TO_UNGUIDED_CALKIT
//
// MessageText:
//
// The PNA failed to convert cal kits for use by unguided calibrations.  The recommended action is to
// restore Cal Kit defaults.
//
#define E_NA_FAILED_CONVERSION_TO_UNGUIDED_CALKIT ((HRESULT)0xE80202ABL)

//
// MessageId: E_NA_FAILED_CONVERSION_TO_UNGUIDED_CALKIT_DEFAULTS_RESTORED
//
// MessageText:
//
// The PNA failed to convert cal kits for use by unguided calibrations.  CalKit defaults have been restored.
//
#define E_NA_FAILED_CONVERSION_TO_UNGUIDED_CALKIT_DEFAULTS_RESTORED ((HRESULT)0xE80202ACL)

//
// MessageId: E_NA_SOURCE_POWER_CAL_IN_PROGRESS
//
// MessageText:
//
// Power meter is reserved by a source power cal acquisition already in progress.
//
#define E_NA_SOURCE_POWER_CAL_IN_PROGRESS ((HRESULT)0xE80202ADL)

//
// MessageId: E_NA_SOURCE_POWER_CAL_NOT_FOUND
//
// MessageText:
//
// Source power calibration has not been performed or uploaded for the specified 
// channel and source port.
//
#define E_NA_SOURCE_POWER_CAL_NOT_FOUND  ((HRESULT)0xE80202AEL)

//
// MessageId: E_NA_SOURCE_POWER_CAL_SIZE_MISMATCH
//
// MessageText:
//
// Source power calibration data array size for the specified channel and 
// source port does not match it's associated stimulus number of points.
//
#define E_NA_SOURCE_POWER_CAL_SIZE_MISMATCH ((HRESULT)0xE80202AFL)

//
// MessageId: MSG_SOURCE_POWER_CAL_TURNED_OFF_BY_SIZE_CHANGE
//
// MessageText:
//
// Source power calibration of Port %1 on Channel %2 was turned off because the 
// correction array no longer exists.
//
#define MSG_SOURCE_POWER_CAL_TURNED_OFF_BY_SIZE_CHANGE ((HRESULT)0xE80202B0L)

//
// MessageId: E_NA_DEPRECATED_COMMAND
//
// MessageText:
//
// This command can only be used on a measurement created with a specified calibration loadport.
//
#define E_NA_DEPRECATED_COMMAND          ((HRESULT)0xE80202B1L)

//
// MessageId: E_NA_ERROR_CAL_CORRECTION_TURNED_OFF_INTERPOLATION_OFF
//
// MessageText:
//
// Interpolation is turned off and you have changed the
// stimulus settings of the original calibration, so
// correction has been turned off.
//
#define E_NA_ERROR_CAL_CORRECTION_TURNED_OFF_INTERPOLATION_OFF ((HRESULT)0xE80202B2L)

//
// MessageId: E_NA_ERROR_CAL_CORRECTION_TURNED_OFF_FREQRANGE_EXCEEDED
//
// MessageText:
//
// Stimulus settings for your current instrument state exceeded the
// parameters of the original calibration, so correction has been turned
// off.
//
#define E_NA_ERROR_CAL_CORRECTION_TURNED_OFF_FREQRANGE_EXCEEDED ((HRESULT)0xE80202B3L)

//
// MessageId: E_NA_ERROR_FIXTURING_S2PFILE_FORMAT
//
// MessageText:
//
// Fixturing: the requested S2P file cannot be read.  Possible formatting problem.
//
#define E_NA_ERROR_FIXTURING_S2PFILE_FORMAT ((HRESULT)0xE80202B4L)

//
// MessageId: E_NA_ERROR_FIXTURING_S2PFILE_CANNOT_OPEN
//
// MessageText:
//
// Fixturing: the requested S2P file cannot be opened.
//
#define E_NA_ERROR_FIXTURING_S2PFILE_CANNOT_OPEN ((HRESULT)0xE80202B5L)

//
// MessageId: E_NA_ERROR_FIXTURING_S2PFILE_CANNOT_INTERPOL
//
// MessageText:
//
// Fixturing: the requested S2P file cannot be interpolated.  This is usually because
// the frequency range in the file is a subset of the current channel frequency range.
//
#define E_NA_ERROR_FIXTURING_S2PFILE_CANNOT_INTERPOL ((HRESULT)0xE80202B6L)

//
// MessageId: E_NA_PRIVATE_CALREGISTER
//
// MessageText:
//
// Cal Registers can only be used by one channel: the channel conveyed in the name of the cal register.  The name cannot be changed.
//
#define E_NA_PRIVATE_CALREGISTER         ((HRESULT)0xE80202B7L)

//
// MessageId: E_NA_ERROR_FIXTURING_TURNED_OFF
//
// MessageText:
//
// Fixturing: cannot be enabled with Response Calibrations and has been turned off.
//
#define E_NA_ERROR_FIXTURING_TURNED_OFF  ((HRESULT)0xE80202B8L)

//
// MessageId: E_NA_CANNOT_CALIBRATE_MEASUREMENT
//
// MessageText:
//
// The selected calibration cannot be performed for this measurement.
//
#define E_NA_CANNOT_CALIBRATE_MEASUREMENT ((HRESULT)0xE80202B9L)

//
// MessageId: E_NA_FITTING_ERROR_CONNECTOR_ELEMENT_IMPROPERLY_ADDED
//
// MessageText:
//
// Fitting: RemoveAllConnectors() should be called prior to calling 
// AddConnector after a fit has been attempted.
//
#define E_NA_FITTING_ERROR_CONNECTOR_ELEMENT_IMPROPERLY_ADDED ((HRESULT)0xE80202BAL)

//
// MessageId: E_NA_CAL_ACQUIRE_NOT_INITIALIZED
//
// MessageText:
//
// An attempt was made to acquire calibration data before the system was properly initialized.
//
#define E_NA_CAL_ACQUIRE_NOT_INITIALIZED ((HRESULT)0xE80202BBL)

//
// MessageId: E_NA_USE_GUIDED_CAL_FOR_MULTIPORT
//
// MessageText:
//
// Use IGuidedCalibration for multiport calibration types.
//
#define E_NA_USE_GUIDED_CAL_FOR_MULTIPORT ((HRESULT)0xE80202BCL)

//
// MessageId: E_NA_MORE_THRU_PATHS_NEEDED
//
// MessageText:
//
// Guided calibration requires the set thrus must be chosen such that each port has a direct or indirect linkage to every other port.
// The testset architecture may also require measurement of additional thru paths for a valid calibration.
//
#define E_NA_MORE_THRU_PATHS_NEEDED      ((HRESULT)0xE80202BDL)

//
// MessageId: E_NA_INVALID_THRU_PATH_FOR_CAL
//
// MessageText:
//
// A port pair was specified that includes a port which the calibration was not specified to include.
//
#define E_NA_INVALID_THRU_PATH_FOR_CAL   ((HRESULT)0xE80202BEL)

//
// MessageId: E_NA_THRU_PATHS_OMITTED_PORT
//
// MessageText:
//
// One or more of the ports to be calibrated was not found in the set of specified thru paths.
//
#define E_NA_THRU_PATHS_OMITTED_PORT     ((HRESULT)0xE80202BFL)

//
// MessageId: E_NA_NOT_THRU_PATH
//
// MessageText:
//
// An invalid pair of ports was specified (only one port number, or same port number for starting port and ending port).
//
#define E_NA_NOT_THRU_PATH               ((HRESULT)0xE80202C0L)

//
// MessageId: E_NA_MISSING_CALSET_ON_RECALL
//
// MessageText:
//
// "The following calset(s):
//  %1 failed to be recalled by channel(s) %2".
//
#define E_NA_MISSING_CALSET_ON_RECALL    ((HRESULT)0xE80202C1L)

//
// MessageId: E_NA_CAL_KIT_CLASS_MISSING_NEEDED_STDS
//
// MessageText:
//
// Selected cal kit has a class that has no standards with the specified
// connectors, which is required for the cal.  Modify the kit definition
// or cal type, or select a different kit.
//
#define E_NA_CAL_KIT_CLASS_MISSING_NEEDED_STDS ((HRESULT)0xE80202C2L)

//
// MessageId: E_NA_GUIDED_CAL_INIT_FAILED
//
// MessageText:
//
// Initialization of guided calibration failed
//
#define E_NA_GUIDED_CAL_INIT_FAILED      ((HRESULT)0xE80202C3L)

//
// MessageId: E_NA_CALSET_OBSOLETE
//
// MessageText:
//
// CalSet not loaded, version is obsolete.
//
#define E_NA_CALSET_OBSOLETE             ((HRESULT)0xE80202C4L)

//
// MessageId: E_NA_CAL_SEQUENCE_SAVE_FAILED
//
// MessageText:
//
// Could not save calibration sequence because it does not exist.
//
#define E_NA_CAL_SEQUENCE_SAVE_FAILED    ((HRESULT)0xE80202C5L)

//
// MessageId: E_NA_CAL_SEQUENCE_RECALL_FAILED
//
// MessageText:
//
// Recall of calibration sequence failed because apparently there was not one stored with the channel.
//
#define E_NA_CAL_SEQUENCE_RECALL_FAILED  ((HRESULT)0xE80202C6L)

//
// MessageId: E_NA_CAL_SEQUENCE_RECALL_INVALID_PORT_NUMBER
//
// MessageText:
//
// Recall of calibration sequence failed because the cal involves ports this PNA does not have.
//
#define E_NA_CAL_SEQUENCE_RECALL_INVALID_PORT_NUMBER ((HRESULT)0xE80202C7L)

//
// MessageId: E_NA_DELTA_MATCH_KIT_NOT_FOUND
//
// MessageText:
//
// Suitable calibration kit was not found for DeltaMatch calibration. 
// Specify an ECal module or calibration kit that covers the entire 
// frequency range.
//
#define E_NA_DELTA_MATCH_KIT_NOT_FOUND   ((HRESULT)0xE80202C8L)

//
// MessageId: E_NA_KIT_STANDARDS_NOT_DEFINED
//
// MessageText:
//
// Specified calibration kit does not have any standards defined. 
// Select a kit with defined standards.  
//
#define E_NA_KIT_STANDARDS_NOT_DEFINED   ((HRESULT)0xE80202C9L)

//
// MessageId: E_NA_DELTA_MATCH_CALSET_NOT_FOUND
//
// MessageText:
//
// Will not use TRL, QSOLT or Unknown Thru on some port pairs. They require a valid delta match calibration. 
// The global delta match calset is missing or was insufficient, 
// or the user-supplied calset for delta match was not found or was insufficient.
//
#define E_NA_DELTA_MATCH_CALSET_NOT_FOUND ((HRESULT)0xE80202CAL)

//
// MessageId: E_NA_INSUFFICIENT_STANDARDS_IN_ONE_PORT_CAL
//
// MessageText:
//
// Not enough standards measured that are within their frequency range to compute one port error terms.
//
#define E_NA_INSUFFICIENT_STANDARDS_IN_ONE_PORT_CAL ((HRESULT)0xE80202CBL)

//
// MessageId: E_NA_STD_ARRAY_ELEMENT_DONT_MATE
//
// MessageText:
//
// The cascading standards don't mate. May be related to improper offset load definition %1. 
//
#define E_NA_STD_ARRAY_ELEMENT_DONT_MATE ((HRESULT)0xE80202CCL)

//
// MessageId: E_NA_FREQUENCY_NOT_SET
//
// MessageText:
//
// The frequency must be set before this operation can complete.
//
#define E_NA_FREQUENCY_NOT_SET           ((HRESULT)0xE80202CDL)

//
// MessageId: E_NA_FREQUENCY_OUT_OF_MODEL_DEVIATION_RANGE
//
// MessageText:
//
// The frequency is outside of the calibration standard model deviation range. This will not be an error unless expanded calibration is used. The connector frequency range may be misdefined.
//
#define E_NA_FREQUENCY_OUT_OF_MODEL_DEVIATION_RANGE ((HRESULT)0xE80202CEL)

//
// MessageId: E_NA_CALIBRATION_STANDARDS_NOT_FOUND
//
// MessageText:
//
// The necessary calibration standards were not found.
//
#define E_NA_CALIBRATION_STANDARDS_NOT_FOUND ((HRESULT)0xE80202CFL)

//
// MessageId: E_NA_CALSET_STIMULUS_NOT_VALID_FOR_CHANNEL
//
// MessageText:
//
// The selected calset is not recognized by the channel.  It may have
// been created by another measurement type with incompatible stimulus properties. 
//
#define E_NA_CALSET_STIMULUS_NOT_VALID_FOR_CHANNEL ((HRESULT)0xE80202D0L)

//
// MessageId: E_NA_CALSET_TEST_PORT_PATHS
//
// MessageText:
//
// The testset and/or port configuration has changed.  The selected calset 
// is not valid for the current configuration.
//
#define E_NA_CALSET_TEST_PORT_PATHS      ((HRESULT)0xE80202D1L)

//
// MessageId: E_NA_CAL_INVALID_PORT
//
// MessageText:
//
// Invalid port number specified.
//
#define E_NA_CAL_INVALID_PORT            ((HRESULT)0xE80202D2L)

//
// MessageId: E_NA_CAL_ACQ_DATA
//
// MessageText:
//
// Error while acquiring calibration data.
//
#define E_NA_CAL_ACQ_DATA                ((HRESULT)0xE80202D3L)

//
// MessageId: E_NA_CAL_INVALID_CONN
//
// MessageText:
//
// The connector specified is invalid.
//
#define E_NA_CAL_INVALID_CONN            ((HRESULT)0xE80202D4L)

//
// MessageId: E_NA_CAL_INVALID_KIT
//
// MessageText:
//
// The Calibration Kit specified is invalid.
//
#define E_NA_CAL_INVALID_KIT             ((HRESULT)0xE80202D5L)

//
// MessageId: E_NA_CAL_SRC_DATA_NOT_FOUND
//
// MessageText:
//
// Could not find Source Power Calibration Data.
//
#define E_NA_CAL_SRC_DATA_NOT_FOUND      ((HRESULT)0xE80202D6L)

//
// MessageId: E_NA_CALSET_HAS_NO_SPARAMETER_CHANNEL_DATA
//
// MessageText:
//
// The calset was not created by a standard SParameter channel.  
// The operation cannot be performed. 
//
#define E_NA_CALSET_HAS_NO_SPARAMETER_CHANNEL_DATA ((HRESULT)0xE80202D7L)    

//
// MessageId: E_NA_ADDITIONAL_CAL_STD_NEEDED
//
// MessageText:
//
// Calibration cannot be completed until you have measured
// all the necessary standards for your selected Cal Type.
//
#define E_NA_ADDITIONAL_CAL_STD_NEEDED   ((HRESULT)0xE80202D8L)

//
// MessageId: E_NA_GUIDED_CAL_NOT_INITIALIZED
//
// MessageText:
//
// Must call InitGuidedCal on the NPortGuidedCal object before calling this method.
//
#define E_NA_GUIDED_CAL_NOT_INITIALIZED  ((HRESULT)0xE80202D9L)

//
// MessageId: E_NA_TRL_METHOD_NOT_AVAILABLE
//
// MessageText:
//
// The current hardware configuration cannot be calibrated using the TRL method.
//
#define E_NA_TRL_METHOD_NOT_AVAILABLE    ((HRESULT)0xE80202DAL)

//
// MessageId: E_NA_GUIDED_CAL_ADAPTER_NOT_DEFINED
//
// MessageText:
//
// p_characterized_device not defined in CTwoPortGuidedCal::SetAdapterRemovalType.
//
#define E_NA_GUIDED_CAL_ADAPTER_NOT_DEFINED ((HRESULT)0xE80202DBL)

//
// MessageId: E_NA_CALSET_DUPLICATE_NAME
//
// MessageText:
//
// A user calset with this name already exists.
//
#define E_NA_CALSET_DUPLICATE_NAME       ((HRESULT)0xE80202DCL)

//
// MessageId: E_NA_CALSET_INVALID_CHARACTERS_FOR_NAME
//
// MessageText:
//
// The calset name contains invalid characters.
//
#define E_NA_CALSET_INVALID_CHARACTERS_FOR_NAME ((HRESULT)0xE80202DDL)

//
// MessageId: E_NA_CALSET_RESERVEDNAME
//
// MessageText:
//
// The calset name is reserved for internal use.
//
#define E_NA_CALSET_RESERVEDNAME         ((HRESULT)0xE80202DEL)

//
// MessageId: E_NA_INSUFFICIENT_STANDARDS_IN_ONE_PORT_CAL_WITH_EXPANDED_CAL
//
// MessageText:
//
// Not enough standards measured that are within their frequency range, or within the defined frequency range of the connector to compute one port error terms.
//
#define E_NA_INSUFFICIENT_STANDARDS_IN_ONE_PORT_CAL_WITH_EXPANDED_CAL ((HRESULT)0xE80202DFL)

//
// MessageId: E_NA_INVALID_PORT_FOR_LOADING_ETERMS_TO_CAL_SEQUENCE
//
// MessageText:
//
// Cannot load error terms into the calibration sequence for the requested port, because the cal sequence does not involve that port.
//
#define E_NA_INVALID_PORT_FOR_LOADING_ETERMS_TO_CAL_SEQUENCE ((HRESULT)0xE80202E0L)

//
// MessageId: E_NA_CALSET_UNSUITABLE_FOR_PORT_ETERM_EXTRACTION
//
// MessageText:
//
// The calset does not contain a cal for the specified port, or the stimulus points of the channel do not match those of the calset.
//
#define E_NA_CALSET_UNSUITABLE_FOR_PORT_ETERM_EXTRACTION ((HRESULT)0xE80202E1L)

//
// MessageId: E_NA_ADAPTER_DOESNT_MATCH_DUT_CONNECTORS
//
// MessageText:
//
// An adapter was selected to be used for specific port pairs in calibration, but the adapter doesn't have the same pair of 
// connectors as the DUT for each of those port pairs.
//
#define E_NA_ADAPTER_DOESNT_MATCH_DUT_CONNECTORS ((HRESULT)0xE80202E2L)

//
// MessageId: E_NA_CALSET_MISSING_PHYSICAL_PORT_MAP
//
// MessageText:
//
// The calset doesn't contain the logical to physical port map.
//
#define E_NA_CALSET_MISSING_PHYSICAL_PORT_MAP ((HRESULT)0xE80202E3L)

//
// MessageId: E_NA_PORT_PAIR_NOT_IN_THRU_PATH_LIST
//
// MessageText:
//
// To have a cal method or thru method property, the specified port pair must first be added to the current set of thru paths for the calibration.
//
#define E_NA_PORT_PAIR_NOT_IN_THRU_PATH_LIST ((HRESULT)0xE80202E4L)

//
// MessageId: E_NA_PATH_CAL_METHOD_UNSUPPORTED_BY_CAL_KIT
//
// MessageText:
//
// Calibration method specified for the port pair is not supported by the calibration kit 
// assigned to that port pair or one port of the pair.
//
#define E_NA_PATH_CAL_METHOD_UNSUPPORTED_BY_CAL_KIT ((HRESULT)0xE80202E5L)

//
// MessageId: E_NA_THRU_METHOD_UNSUPPORTED_BY_CAL_METHOD
//
// MessageText:
//
// Thru method specified for the port pair is not supported by the calibration method 
// currently assigned to that port pair or one port of the pair.
//
#define E_NA_THRU_METHOD_UNSUPPORTED_BY_CAL_METHOD ((HRESULT)0xE80202E6L)

//
// MessageId: E_NA_THRU_METHOD_UNSUPPORTED_BY_CAL_KIT
//
// MessageText:
//
// Did not find one or more thru standards defined that would satisfy the thru method 
// specified for the port pair and for the frequency span to be calibrated.
//
#define E_NA_THRU_METHOD_UNSUPPORTED_BY_CAL_KIT ((HRESULT)0xE80202E7L)

//
// MessageId: E_NA_MISSING_USB_POWER_METER_ID
//
// MessageText:
//
// More than one power measurement device was found on the USB bus.  Please indicate 
// the specific device to be used.
//
#define E_NA_MISSING_USB_POWER_METER_ID  ((HRESULT)0xE80202E8L)

//
// MessageId: E_NA_SPECIFIED_USB_POWER_METER_NOT_FOUND
//
// MessageText:
//
// The specified power measurement device was not found on the USB bus.
//
#define E_NA_SPECIFIED_USB_POWER_METER_NOT_FOUND ((HRESULT)0xE80202E9L)

//
// MessageId: E_NA_MISSING_LAN_POWER_METER_ADDRESS
//
// MessageText:
//
// LAN is selected as the communication path for the power meter, but neither a LAN 
// hostname nor IP address has been specified.
//
#define E_NA_MISSING_LAN_POWER_METER_ADDRESS ((HRESULT)0xE80202EAL)

//
// MessageId: E_NA_FULL_TWO_PORT_METHOD_REQUIRED
//
// MessageText:
//
// This calibration requires full two port error terms. Enhanced Response, for example, is not a valid cal method.
//
#define E_NA_FULL_TWO_PORT_METHOD_REQUIRED ((HRESULT)0xE80202EBL)

//
// MessageId: E_NA_INVALID_ECAL_STATE_NUMBER
//
// MessageText:
//
// The requested ECal state number is not valid.
//
#define E_NA_INVALID_ECAL_STATE_NUMBER   ((HRESULT)0xE80202ECL)

//
// MessageId: E_NA_REQUESTED_ECAL_NOT_FOUND
//
// MessageText:
//
// Could not detect the specified ECal module.  Please ensure that it is connected and 
// that you are specifying its ID properly.
//
#define E_NA_REQUESTED_ECAL_NOT_FOUND    ((HRESULT)0xE80202EDL)

//
// MessageId: E_NA_ECAL_STRING_LENGTH_LIMIT
//
// MessageText:
//
// ECal module memory limits the lengths of user characterization information fields.  The specified string has been truncated accordingly.
//
#define E_NA_ECAL_STRING_LENGTH_LIMIT    ((HRESULT)0xE80202EEL)

//
// MessageId: E_NA_REMOTE_ECAL_USER_CHARACTERIZATION_STEP_LIMIT
//
// MessageText:
//
// Remote ECal user characterization does not yet support characterizing an ECal that has more ports than the PNA system.
//
#define E_NA_REMOTE_ECAL_USER_CHARACTERIZATION_STEP_LIMIT ((HRESULT)0xE80202EFL)

//
// MessageId: E_NA_ECAL_USER_CHARACTERIZATION_INIT_FIRST
//
// MessageText:
//
// Before generating steps for remote ECal user characterization, must call Initialize first.
//
#define E_NA_ECAL_USER_CHARACTERIZATION_INIT_FIRST ((HRESULT)0xE80202F0L)

//
// MessageId: E_NA_NOT_ALL_STEPS_COMPLETED
//
// MessageText:
//
// Not all measurement steps have been completed.
//
#define E_NA_NOT_ALL_STEPS_COMPLETED     ((HRESULT)0xE80202F1L)

//
// MessageId: E_NA_POWER_METER_VISA_RSRC_STRING_MISSING
//
// MessageText:
//
// The communication path for the power measurement device is selected to be a specific VISA resource, 
// but the resource string has not been specified.
//
#define E_NA_POWER_METER_VISA_RSRC_STRING_MISSING ((HRESULT)0xE80202F2L)

//
// MessageId: E_NA_INVALID_FACTORY_CAL_KIT_NAME
//
// MessageText:
//
// The specified calibration kit name is not recognized as a kit that has a definition 
// factory-installed on the PNA.
//
#define E_NA_INVALID_FACTORY_CAL_KIT_NAME ((HRESULT)0xE80202F3L)

//
// MessageId: E_AME_INVALID_DATA_SET
//
// MessageText:
//
// ERROR: Invalid dataset name. See help documentation for valid data sets.
//
#define E_AME_INVALID_DATA_SET           ((HRESULT)0xE90102F4L)

//
// MessageId: E_AME_ERROR_TERM_NOT_FOUND
//
// MessageText:
//
// ERROR: Could not import dataset. The error term/standard data was not found.
//
#define E_AME_ERROR_TERM_NOT_FOUND       ((HRESULT)0xE90102F5L)

//
// MessageId: E_NA_CHANGING_CHAN_CAL_SWEEP_STATE_NEEDS_MEAS
//
// MessageText:
//
// A channel must have at least one measurement parameter before you can change 
// whether the channel is allowed to sweep during a calibration acquisition.
//
#define E_NA_CHANGING_CHAN_CAL_SWEEP_STATE_NEEDS_MEAS ((HRESULT)0xE80202F6L)

//
// MessageId: E_NA_CANT_USE_POWER_METER_ONLY
//
// MessageText:
//
// This power calibration cannot use only a power meter (or power sensor).
// Select to use power meter with PNA reference receiver, or use PNA receiver only.
//
#define E_NA_CANT_USE_POWER_METER_ONLY   ((HRESULT)0xE80202F7L)

//
// MessageId: E_NA_SOURCE_POWER_CAL_OUT_OF_TOLERANCE
//
// MessageText:
//
// The source power cal result was out of tolerance.
//
#define E_NA_SOURCE_POWER_CAL_OUT_OF_TOLERANCE ((HRESULT)0xE80202F8L)

//
// MessageId: E_NA_WARNING_SOURCE_POWER_CAL_OUT_OF_TOLERANCE
//
// MessageText:
//
// The source power cal result was out of tolerance.
//
#define E_NA_WARNING_SOURCE_POWER_CAL_OUT_OF_TOLERANCE ((HRESULT)0x680202F9L)

//
// MessageId: E_NA_MISSING_CALSET_DATA_REQUIRED_FOR_OPERATION
//
// MessageText:
//
// The calset has insufficient data for the requested operation.
//
#define E_NA_MISSING_CALSET_DATA_REQUIRED_FOR_OPERATION ((HRESULT)0xE80202FAL)

//
// MessageId: E_NA_FIXTURING_OPERATION_FAILED
//
// MessageText:
//
// The fixturing operation failed.
//
#define E_NA_FIXTURING_OPERATION_FAILED  ((HRESULT)0xE80202FBL)

//
// MessageId: E_NA_CALSTIM_RESTORED_BUT_STILL_NO_JOY
//
// MessageText:
//
// The calibration stimulus was recalled, but the minimum width of the channel acquisition is still outside the range of the correction.  Correction has been turned off.
//
#define E_NA_CALSTIM_RESTORED_BUT_STILL_NO_JOY ((HRESULT)0xE80202FCL)

//
// MessageId: E_NA_NULL_MATRIX
//
// MessageText:
//
// Null Matrix.
//
#define E_NA_NULL_MATRIX                 ((HRESULT)0xE80202FDL)    

//
// MessageId: E_NA_PORT_HAS_NO_CALDATA
//
// MessageText:
//
// The calset has no data for the requested port.
//
#define E_NA_PORT_HAS_NO_CALDATA         ((HRESULT)0xE80202FEL)

//
// MessageId: E_NA_GUIDED_POWER_CAL_DOES_NOT_SUPPORT_REVERSE_ENHANCED_RESPONSE
//
// MessageText:
//
// The enhanced response cal must be calibrated with the same source port as the power calibration.
// Change the selected port for the power calibration.
//
#define E_NA_GUIDED_POWER_CAL_DOES_NOT_SUPPORT_REVERSE_ENHANCED_RESPONSE ((HRESULT)0xE8020200L)

//
// MessageId: E_NA_BANDED_FREQUENCIES_REQUIRE_MULTIPLE_POWER_SENSOR_SETTING
//
// MessageText:
//
// You must select "multiple power sensors" when measuring frequencies above the native frequencies of the PNA.
//
#define E_NA_BANDED_FREQUENCIES_REQUIRE_MULTIPLE_POWER_SENSOR_SETTING ((HRESULT)0xE8020201L)

//
// MessageId: E_NA_BANDED_POWER_TOO_HIGH_FOR_CALIBRATION
//
// MessageText:
//
// The default power level of 11dBm is unachievable after calibration. Lower the power before starting calibration.
//
#define E_NA_BANDED_POWER_TOO_HIGH_FOR_CALIBRATION ((HRESULT)0xE8020202L)

//
// MessageId: E_NA_FIXTURING_DISABLED
//
// MessageText:
//
// Fixturing process encountered an error and has been disabled.
//
#define E_NA_FIXTURING_DISABLED          ((HRESULT)0xE8020203L)

//
// MessageId: E_NA_POWER_TABLE_NOT_AVAILABLE
//
// MessageText:
//
// The power table feature is only available for Scalar Mixer/Converter that has been configured using the millimeter module configuration.
//
#define E_NA_POWER_TABLE_NOT_AVAILABLE   ((HRESULT)0xE8020204L)

//
// MessageId: E_NA_PHASE_REFERENCE_NOT_CONNECTED_PROPERLY
//
// MessageText:
//
// The phase reference was not connected properly to the port. Check that you have connected your 10 MHz reference signal properly.
//
#define E_NA_PHASE_REFERENCE_NOT_CONNECTED_PROPERLY ((HRESULT)0xE8020205L)

//
// MessageId: E_NA_CAL_LIMIT_TEST_FAIL
//
// MessageText:
//
// Error: Limit test failed during calibration.
//
#define E_NA_CAL_LIMIT_TEST_FAIL         ((HRESULT)0xE8020206L)

//
// MessageId: E_NA_CHANNEL_LACKS_REQUISITE_GUIDED_CAL_INTERFACE
//
// MessageText:
//
// The selected channel does not support the guided calibration interface for this capability in the present context.
//
#define E_NA_CHANNEL_LACKS_REQUISITE_GUIDED_CAL_INTERFACE ((HRESULT)0xE8020207L)

//
// MessageId: E_NA_INVALID_CAL_PROPERTY_NAME
//
// MessageText:
//
// The property name %1 is not valid.
//
#define E_NA_INVALID_CAL_PROPERTY_NAME   ((HRESULT)0xE8020208L)

//
// MessageId: E_NA_INVALID_CAL_PROPERTY_VALUE
//
// MessageText:
//
// The property value %1 is not valid.
//
#define E_NA_INVALID_CAL_PROPERTY_VALUE  ((HRESULT)0xE8020209L)

//
// MessageId: E_NA_CAL_NO_IMPORT_RESPONSE_AT_PORT
//
// MessageText:
//
// The selected calset does not have a response cal for Port %1
//
#define E_NA_CAL_NO_IMPORT_RESPONSE_AT_PORT ((HRESULT)0xE802020AL)

//
// MessageId: E_NA_CAL_IMPORT_RESPONSE_CAL_DOES_NOT_HAVE_FREQUENCIES
//
// MessageText:
//
// The selected calset does not include frequencies to cover Port %1. Port %1 is at %2. The selected calset is at %3.
//
#define E_NA_CAL_IMPORT_RESPONSE_CAL_DOES_NOT_HAVE_FREQUENCIES ((HRESULT)0xE802020BL)

//
// MessageId: E_NA_CAL_IMPORT_DOES_NOT_MATCH_ATTENUATORS
//
// MessageText:
//
// The selected calset has the wrong attenuator setting for Port %1. The current channel is at %2. The selected calset is at %3.
//
#define E_NA_CAL_IMPORT_DOES_NOT_MATCH_ATTENUATORS ((HRESULT)0xE802020CL)

//
// MessageId: E_NA_CAL_ALL_CHANNEL_NOT_SELECTED
//
// MessageText:
//
// The specified channel was not selected for Calibration.
//
#define E_NA_CAL_ALL_CHANNEL_NOT_SELECTED ((HRESULT)0xE802020DL)

//
// MessageId: E_NA_CAL_ALL_PORT_NOT_SELECTED
//
// MessageText:
//
// The specified port was not selected for Calibration.
//
#define E_NA_CAL_ALL_PORT_NOT_SELECTED   ((HRESULT)0xE802020EL)

//
// MessageId: E_NA_PHASE_REFERENCE_NOT_RECOGNIZED
//
// MessageText:
//
// The specific phase reference was not recognized. Check to see that it is connected to the system.
//
#define E_NA_PHASE_REFERENCE_NOT_RECOGNIZED ((HRESULT)0xE802020FL)

//
// MessageId: E_NA_PHASE_REFERENCE_PORT_MUST_STAY_ON
//
// MessageText:
//
// Port 1 and Port 2 must be included the phase reference calibration. They cannot be excluded.
//
#define E_NA_PHASE_REFERENCE_PORT_MUST_STAY_ON ((HRESULT)0xE8020210L)

//
// MessageId: E_NA_PHASE_REFERENCE_CALSET_NAME_MUST_BE_DEFINED
//
// MessageText:
//
// The calset name is undefined. It must be defined to finish the phase reference cal.
//
#define E_NA_PHASE_REFERENCE_CALSET_NAME_MUST_BE_DEFINED ((HRESULT)0xE8020300L)

//
// MessageId: E_NA_ADAPTER_REMOVAL_NOT_ALLOWED
//
// MessageText:
//
// Adapter removal is not supported for LO power calibrations.
//
#define E_NA_ADAPTER_REMOVAL_NOT_ALLOWED ((HRESULT)0xE8020301L)

//
// MessageId: E_NA_MINIMUM_TWO_PORTS
//
// MessageText:
//
// This calibration process requires a minimum of two ports.
//
#define E_NA_MINIMUM_TWO_PORTS           ((HRESULT)0xE8020302L)

//
// MessageId: E_NA_NO_SOURCE_CAL_CHANNEL_SET
//
// MessageText:
//
// The target NA stimulus channel has not been set. With the SourcePowerCalibrator object, you must first  call SetCalInfoEx with the channel number. SetCalInfoEx must not be made against a temporary copy of the SourcePowerCalibrator object.
//
#define E_NA_NO_SOURCE_CAL_CHANNEL_SET   ((HRESULT)0xE8020303L)

//
// MessageId: E_NA_CAL_REQUIRES_DELTA_MATCH_CALSET
//
// MessageText:
//
// Unguided TRL calibration on this instrument requires a global delta match calset. 
// A global delta match calibration must be performed to establish that calset 
// before an unguided TRL cal can be performed.
//
#define E_NA_CAL_REQUIRES_DELTA_MATCH_CALSET ((HRESULT)0xE8020304L)

//
// MessageId: E_NA_CANT_IN_SITU_CHARACTERIZE_SPECIFIED_ECAL
//
// MessageText:
//
// In situ user characterization is not supported for the specified ECal device.
//
#define E_NA_CANT_IN_SITU_CHARACTERIZE_SPECIFIED_ECAL ((HRESULT)0xE8020305L)

//
// MessageId: E_NA_UNKNOWN_MIXER_NOT_CONNECTED
//
// MessageText:
//
// ERROR: The mixer has not been connected to the ports.
//
#define E_NA_UNKNOWN_MIXER_NOT_CONNECTED ((HRESULT)0xE8020306L)

//
// MessageId: E_NA_CALMETHOD_NOT_SUPPORTED
//
// MessageText:
//
// The requested cal method is not supported.
//
#define E_NA_CALMETHOD_NOT_SUPPORTED     ((HRESULT)0xE8020307L)

//
// MessageId: E_NA_PHASE_REFERENCE_COULD_NOT_SET_THRU_PATH
//
// MessageText:
//
// The phase reference calibration engine was unable to set the thru path
//
#define E_NA_PHASE_REFERENCE_COULD_NOT_SET_THRU_PATH ((HRESULT)0xE8020308L)

//
// MessageId: E_NA_PHASE_REFERENCE_COULD_NOT_SET_THRU_METHOD
//
// MessageText:
//
// The phase reference calibration engine was unable to set the thru method
//
#define E_NA_PHASE_REFERENCE_COULD_NOT_SET_THRU_METHOD ((HRESULT)0xE8020309L)

//
// MessageId: E_NA_PHASE_REFERENCE_COULD_NOT_GET_THRU_PATH
//
// MessageText:
//
// The phase reference calibration engine was unable to get the thru path
//
#define E_NA_PHASE_REFERENCE_COULD_NOT_GET_THRU_PATH ((HRESULT)0xE802030AL)

//
// MessageId: E_NA_PHASE_REFERENCE_COULD_NOT_GET_THRU_METHOD
//
// MessageText:
//
// The phase reference calibration engine was unable to get the thru method
//
#define E_NA_PHASE_REFERENCE_COULD_NOT_GET_THRU_METHOD ((HRESULT)0xE802030BL)

//
// MessageId: E_NA_ECAL_IO_ERROR
//
// MessageText:
//
// An I/O error occurred while attempting to control the specified Electronic Calibration device.
//
#define E_NA_ECAL_IO_ERROR               ((HRESULT)0xE802030CL)

//
// MessageId: E_CALSET_MISMATCH
//
// MessageText:
//
// Two calsets have no common frequency range.
//
#define E_CALSET_MISMATCH                ((HRESULT)0xE802030DL)

//
// MessageId: E_NA_INVALID_KIT_FILE
//
// MessageText:
//
// The specified cal kit file does not exist or the file format is not recognized.
//
#define E_NA_INVALID_KIT_FILE            ((HRESULT)0xE802030EL)

//
// MessageId: E_NA_BAD_ERROR_TERM_DEFINITION
//
// MessageText:
//
// The command arguments provided construct an invalid error term.
//
#define E_NA_BAD_ERROR_TERM_DEFINITION   ((HRESULT)0xE802030FL)

//
// MessageId: E_NA_SENS_CORR_CCH_MEAS_PARAM_SELECTION_NONE
//
// MessageText:
//
// SENS:CORR:CCH measurement selection set to none.
//
#define E_NA_SENS_CORR_CCH_MEAS_PARAM_SELECTION_NONE ((HRESULT)0xE8020310L)

//
// MessageId: E_NA_PHASE_REF_CAL_DOES_NOT_SUPPORT_COMMAND
//
// MessageText:
//
// SENS:CORR:COLL:GUID:SAVE:IMM is not supported by the phase reference calibration. Use SENS:CORR:COLL:GUID:SAVE:CSET.
//
#define E_NA_PHASE_REF_CAL_DOES_NOT_SUPPORT_COMMAND ((HRESULT)0xE8020311L)

//
// MessageId: E_NA_NO_CAL_SET_SELECTED
//
// MessageText:
//
// There is no Cal Set currently selected for the specified channel.
//
#define E_NA_NO_CAL_SET_SELECTED         ((HRESULT)0xE8020312L)

//
// MessageId: E_NO_FREQUENCY_OVERLAP
//
// MessageText:
//
// No overlapped frequency range.
//
#define E_NO_FREQUENCY_OVERLAP           ((HRESULT)0xE8020313L)

//
// MessageId: MSG_GUIDED_CAL_INIT_COMPLETE
//
// MessageText:
//
// Initialization of guided calibration completed
//
#define MSG_GUIDED_CAL_INIT_COMPLETE     ((HRESULT)0x68020314L)

//
// MessageId: MSG_GUIDED_CAL_ACQUIRESTEP_COMPLETE
//
// MessageText:
//
// Guided calibration step acquisition completed
//
#define MSG_GUIDED_CAL_ACQUIRESTEP_COMPLETE ((HRESULT)0x68020315L)

//
// MessageId: E_NA_WRONG_TOPOLOGY
//
// MessageText:
//
// The current topology does not match the command being issued.
//
#define E_NA_WRONG_TOPOLOGY              ((HRESULT)0xE8020316L)

//
// MessageId: E_NA_CORRECTIONTYPE_NOT_RECOGNIZED
//
// MessageText:
//
// The specified correction type is not recognized by the channel.
//
#define E_NA_CORRECTIONTYPE_NOT_RECOGNIZED ((HRESULT)0xE8020317L)

//
// MessageId: E_NA_NO_AVAILABLE_CAL_METHOD
//
// MessageText:
//
// The cal kit selection cannot produce a valid calibration.
//
#define E_NA_NO_AVAILABLE_CAL_METHOD     ((HRESULT)0xE8020318L)

//
// MessageId: MSG_SOURCE_CAL_SWEEP_COMPLETE
//
// MessageText:
//
// Source power calibration sweep complete.
//
#define MSG_SOURCE_CAL_SWEEP_COMPLETE    ((HRESULT)0x68020319L)

//
// MessageId: MSG_ECAL_CHAR_INIT_COMPLETE
//
// MessageText:
//
// ECal Characterization initialization operation is complete.
//
#define MSG_ECAL_CHAR_INIT_COMPLETE      ((HRESULT)0x6802031AL)

//
// MessageId: MSG_ECAL_CHAR_ACQUIRE_COMPLETE
//
// MessageText:
//
// ECal Characterization acquisition operation is complete.
//
#define MSG_ECAL_CHAR_ACQUIRE_COMPLETE   ((HRESULT)0x6802031BL)

//
// MessageId: MSG_ECAL_CHAR_SAVE_COMPLETE
//
// MessageText:
//
// ECal Characterization save operation is complete.
//
#define MSG_ECAL_CHAR_SAVE_COMPLETE      ((HRESULT)0x6802031CL)

//
// MessageId: MSG_UNGUIDED_CAL_ACQUIRESTEP_COMPLETE
//
// MessageText:
//
// Unguided calibration step acquisition completed.
//
#define MSG_UNGUIDED_CAL_ACQUIRESTEP_COMPLETE ((HRESULT)0x6802031DL)

//
// MessageId: E_CALIBRATION_PORTS_NOT_CONFIGURED
//
// MessageText:
//
// The ports selected for calibration were not properly configured.  Check connector and kit settings.
//
#define E_CALIBRATION_PORTS_NOT_CONFIGURED ((HRESULT)0xE802031EL)

//
// MessageId: E_ONE_PORT_CAL_NOT_CONFIGURED
//
// MessageText:
//
// The selected channels do not have the same mechanical settings at Port %1 to perform a 1-port calibration.
//
#define E_ONE_PORT_CAL_NOT_CONFIGURED    ((HRESULT)0xE802031FL)

//
// MessageId: E_DATA_ACCESS_REQUIRES_CAL
//
// MessageText:
//
// Apply a calibration to the selected measurement before accessing the measurement's calibration data.
//
#define E_DATA_ACCESS_REQUIRES_CAL       ((HRESULT)0xE8020320L)

//
// MessageId: MSG_GUIDED_ECAL_ACQUIRE_COMPLETE
//
// MessageText:
//
// Guided ECal acquisition completed.
//
#define MSG_GUIDED_ECAL_ACQUIRE_COMPLETE ((HRESULT)0x68020321L)

//
// MessageId: E_NA_MINIMUM_ONE_PORT
//
// MessageText:
//
// This calibration process requires a minimum of one port.
//
#define E_NA_MINIMUM_ONE_PORT            ((HRESULT)0xE8020322L)

//
// MessageId: E_NA_CHANNEL_REJECTS_CALSET
//
// MessageText:
//
// The selected calset cannot be applied to the channel.
//
#define E_NA_CHANNEL_REJECTS_CALSET      ((HRESULT)0xE8020323L)

//
// MessageId: E_NA_ECAL_ENHANCED_CORRECTION_DATA_NOT_FOUND
//
// MessageText:
//
// An enhanced correction file for use with specific ECal modules could not be found or could not be read.
//
#define E_NA_ECAL_ENHANCED_CORRECTION_DATA_NOT_FOUND ((HRESULT)0xE8020325L)

//
// MessageId: E_NA_UNABLE_TO_READ_ECAL_ENVIRONMENTAL_SENSORS
//
// MessageText:
//
// A problem occurred trying to read environmental sensor data from an ECal module.
//
#define E_NA_UNABLE_TO_READ_ECAL_ENVIRONMENTAL_SENSORS ((HRESULT)0xE8020326L)

//
// MessageId: E_NA_UNABLE_TO_APPLY_ECAL_ENHANCED_CORRECTION
//
// MessageText:
//
// A problem occurred trying to apply enhanced correction data for an ECal module.
//
#define E_NA_UNABLE_TO_APPLY_ECAL_ENHANCED_CORRECTION ((HRESULT)0xE8020327L)

//
// MessageId: E_NA_CAL_KIT_NOT_ECAL_ENHANCED_CORRECTION_COMPLIANT
//
// MessageText:
//
// Cannot do ECal enhanced correction for the specified ECal kit because that kit name is not recognized by that feature.
//
#define E_NA_CAL_KIT_NOT_ECAL_ENHANCED_CORRECTION_COMPLIANT ((HRESULT)0xE8020328L)

//
// MessageId: E_NA_CAL_KIT_NOT_INITIALIZED_FOR_ECAL_ENHANCED_CORRECTION
//
// MessageText:
//
// The specified ECal kit cannot apply ECal enhanced correction until environmental sensor data has been initialized for it.
//
#define E_NA_CAL_KIT_NOT_INITIALIZED_FOR_ECAL_ENHANCED_CORRECTION ((HRESULT)0xE8020329L)

//
// MessageId: E_NA_CORRTYPE_NOT_VALID_DEVOLVE_IS_ON
//
// MessageText:
//
// The correction type specified cannot be applied because correction method subsetting is on. 
//
#define E_NA_CORRTYPE_NOT_VALID_DEVOLVE_IS_ON ((HRESULT)0xE8020324L)

//
// MessageId: E_NA_ECAL_MODULE_MEMORY_SECTOR_UNWRITABLE
//
// MessageText:
//
// Problem writing an ECal module memory sector.  If this recurs when you try to restore the module memory, the module may need service or repair.
//
#define E_NA_ECAL_MODULE_MEMORY_SECTOR_UNWRITABLE ((HRESULT)0xE802032AL)

//
// MessageId: E_NA_ECAL_DATA_INVALID_FOR_AUTO_ORIENT
//
// MessageText:
//
// ECal auto-orient failed because data for different states in the selected ECal characterization are too similar at the frequencies being used.
//
#define E_NA_ECAL_DATA_INVALID_FOR_AUTO_ORIENT ((HRESULT)0xE802032BL)

//
// MessageId: E_NA_NO_REMOTE_EDIT_CAL_KIT_WITH_COVARIANT_UNCERTAINTIES
//
// MessageText:
//
// Cannot remotely modify a calibration kit that has any standards with covariant uncertainty data.
//
#define E_NA_NO_REMOTE_EDIT_CAL_KIT_WITH_COVARIANT_UNCERTAINTIES ((HRESULT)0xE802032CL)

//
// MessageId: E_NA_CAL_STD_NOT_FOUND
//
// MessageText:
//
// The selected Calibration Standard appears to have been removed from the Kit.  To create a new standard with that number, re-select the number.
//
#define E_NA_CAL_STD_NOT_FOUND           ((HRESULT)0xE802032DL)

//
// MessageId: E_NA_NO_VALID_CAL_ALL_CHANNELS
//
// MessageText:
//
// No valid channels available for Cal All.
//
#define E_NA_NO_VALID_CAL_ALL_CHANNELS   ((HRESULT)0xE802032EL)

//
// MessageId: E_NA_FEATURE_UNSUPPORTED_ON_SELECTED_ECAL
//
// MessageText:
//
// The requested feature is not supported on the specified ECal module.
//
#define E_NA_FEATURE_UNSUPPORTED_ON_SELECTED_ECAL ((HRESULT)0xE802032FL)

//
// MessageId: E_NA_INVALID_DSP_DRIVER
//
// MessageText:
//
// A noncompatible DSP driver version is installed. Reinstall the firmware.
//
#define E_NA_INVALID_DSP_DRIVER          ((HRESULT)0xE8030300L)

//
// MessageId: E_NA_TRIGGER_TOO_FAST
//
// MessageText:
//
// Triggered too fast: PNA received hardware trigger before trigger was armed.
//
#define E_NA_TRIGGER_TOO_FAST            ((HRESULT)0xE8030301L)

//
// MessageId: MSG_POWER_TRIPPED
//
// MessageText:
//
// Input power too high. Source power is off.
//
#define MSG_POWER_TRIPPED                ((HRESULT)0xA8030302L)

//
// MessageId: MSG_POWER_TRIP_CORRECTED
//
// MessageText:
//
// Source power restored.
//
#define MSG_POWER_TRIP_CORRECTED         ((HRESULT)0x68030303L)

//
// MessageId: MSG_DSP_BOARD_NOT_FOUND
//
// MessageText:
//
// Spampnp.sys driver not working. Check system hardware.
// Data simulated.
//
#define MSG_DSP_BOARD_NOT_FOUND          ((HRESULT)0xE8030304L)

//
// MessageId: MSG_INSTRUMENT_SERIAL_BUS_BAD
//
// MessageText:
//
// Instrument serial bus not working.
//
#define MSG_INSTRUMENT_SERIAL_BUS_BAD    ((HRESULT)0xE8030305L)

//
// MessageId: E_NA_UNLEVELED_SRC1_OUT1
//
// MessageText:
//
// Unleveled, source 1, out 1
//
#define E_NA_UNLEVELED_SRC1_OUT1         ((HRESULT)0xE8030310L)

//
// MessageId: E_NA_UNLEVELED_SRC1_OUT2
//
// MessageText:
//
// Unleveled, source 1, out 2
//
#define E_NA_UNLEVELED_SRC1_OUT2         ((HRESULT)0xE8030311L)

//
// MessageId: E_NA_UNLEVELED_SRC1_SYNTH
//
// MessageText:
//
// Unleveled, source 1 synthesizer
//
#define E_NA_UNLEVELED_SRC1_SYNTH        ((HRESULT)0xE8030312L)

//
// MessageId: E_NA_UNLEVELED_SRC2_OUT1
//
// MessageText:
//
// Unleveled, source 2, out 1
//
#define E_NA_UNLEVELED_SRC2_OUT1         ((HRESULT)0xE8030313L)

//
// MessageId: E_NA_UNLEVELED_SRC2_OUT2
//
// MessageText:
//
// Unleveled, source 2, out 2
//
#define E_NA_UNLEVELED_SRC2_OUT2         ((HRESULT)0xE8030314L)

//
// MessageId: E_NA_UNLEVELED_SRC2_SYNTH
//
// MessageText:
//
// Unleveled, source 2 synthesizer
//
#define E_NA_UNLEVELED_SRC2_SYNTH        ((HRESULT)0xE8030315L)

//
// MessageId: E_NA_UNLEVELED_LO
//
// MessageText:
//
// Unleveled, LO drive
//
#define E_NA_UNLEVELED_LO                ((HRESULT)0xE8030316L)

//
// MessageId: E_NA_UNLEVELED_LO_SYNTH
//
// MessageText:
//
// Unleveled, LO synthesizer
//
#define E_NA_UNLEVELED_LO_SYNTH          ((HRESULT)0xE8030317L)

//
// MessageId: E_NA_UNLOCK_SRC1_LOW
//
// MessageText:
//
// Phaselock lost, source 1 synthesizer MAIN, integrator low
//
#define E_NA_UNLOCK_SRC1_LOW             ((HRESULT)0xE8030318L)

//
// MessageId: E_NA_UNLOCK_SRC1_HI
//
// MessageText:
//
// Phaselock lost, source 1 synthesizer MAIN, integrator high
//
#define E_NA_UNLOCK_SRC1_HI              ((HRESULT)0xE8030319L)

//
// MessageId: E_NA_UNLOCK_SRC1_HET
//
// MessageText:
//
// Phaselock lost, source 1 synthesizer HET
//
#define E_NA_UNLOCK_SRC1_HET             ((HRESULT)0xE803031AL)

//
// MessageId: E_NA_UNLOCK_SRC2_LOW
//
// MessageText:
//
// Phaselock lost, source 2 synthesizer MAIN, integrator low
//
#define E_NA_UNLOCK_SRC2_LOW             ((HRESULT)0xE803031BL)

//
// MessageId: E_NA_UNLOCK_SRC2_HI
//
// MessageText:
//
// Phaselock lost, source 2 synthesizer MAIN, integrator high
//
#define E_NA_UNLOCK_SRC2_HI              ((HRESULT)0xE803031CL)

//
// MessageId: E_NA_UNLOCK_SRC2_HET
//
// MessageText:
//
// Phaselock lost, source 2 synthesizer HET
//
#define E_NA_UNLOCK_SRC2_HET             ((HRESULT)0xE803031DL)

//
// MessageId: E_NA_UNLOCK_LO_LOW
//
// MessageText:
//
// Phaselock lost, LO synthesizer MAIN, integrator low
//
#define E_NA_UNLOCK_LO_LOW               ((HRESULT)0xE803031EL)

//
// MessageId: E_NA_UNLOCK_LO_HI
//
// MessageText:
//
// Phaselock lost, LO synthesizer MAIN, integrator high
//
#define E_NA_UNLOCK_LO_HI                ((HRESULT)0xE803031FL)

//
// MessageId: E_NA_UNLOCK_LO_HET
//
// MessageText:
//
// Phaselock lost, LO synthesizer HET
//
#define E_NA_UNLOCK_LO_HET               ((HRESULT)0xE8030320L)

//
// MessageId: E_NA_SET_UNLEVEL_SRC1_OUT1
//
// MessageText:
//
//  E_NA_SET_UNLEVEL_SRC1_OUT1
//
#define E_NA_SET_UNLEVEL_SRC1_OUT1       ((HRESULT)0xE8030321L)

//
// MessageId: E_NA_CLR_UNLEVEL_SRC1_OUT1
//
// MessageText:
//
//  E_NA_CLR_UNLEVEL_SRC1_OUT1
//
#define E_NA_CLR_UNLEVEL_SRC1_OUT1       ((HRESULT)0xE8030322L)

//
// MessageId: E_NA_SET_UNLEVEL_SRC1_OUT2
//
// MessageText:
//
//  E_NA_SET_UNLEVEL_SRC1_OUT2
//
#define E_NA_SET_UNLEVEL_SRC1_OUT2       ((HRESULT)0xE8030323L)

//
// MessageId: E_NA_CLR_UNLEVEL_SRC1_OUT2
//
// MessageText:
//
//  E_NA_CLR_UNLEVEL_SRC1_OUT2
//
#define E_NA_CLR_UNLEVEL_SRC1_OUT2       ((HRESULT)0xE8030324L)

//
// MessageId: E_NA_SET_UNLEVEL_SRC1_SYNTH
//
// MessageText:
//
//  E_NA_SET_UNLEVEL_SRC1_SYNTH
//
#define E_NA_SET_UNLEVEL_SRC1_SYNTH      ((HRESULT)0xE8030325L)

//
// MessageId: E_NA_CLR_UNLEVEL_SRC1_SYNTH
//
// MessageText:
//
//  E_NA_CLR_UNLEVEL_SRC1_SYNTH
//
#define E_NA_CLR_UNLEVEL_SRC1_SYNTH      ((HRESULT)0xE8030326L)

//
// MessageId: E_NA_SET_UNLEVEL_SRC2_OUT1
//
// MessageText:
//
//  E_NA_SET_UNLEVEL_SRC2_OUT1
//
#define E_NA_SET_UNLEVEL_SRC2_OUT1       ((HRESULT)0xE8030327L)

//
// MessageId: E_NA_CLR_UNLEVEL_SRC2_OUT1
//
// MessageText:
//
//  E_NA_CLR_UNLEVEL_SRC2_OUT1
//
#define E_NA_CLR_UNLEVEL_SRC2_OUT1       ((HRESULT)0xE8030328L)

//
// MessageId: E_NA_SET_UNLEVEL_SRC2_OUT2
//
// MessageText:
//
//  E_NA_SET_UNLEVEL_SRC2_OUT2
//
#define E_NA_SET_UNLEVEL_SRC2_OUT2       ((HRESULT)0xE8030329L)

//
// MessageId: E_NA_CLR_UNLEVEL_SRC2_OUT2
//
// MessageText:
//
//  E_NA_CLR_UNLEVEL_SRC2_OUT2
//
#define E_NA_CLR_UNLEVEL_SRC2_OUT2       ((HRESULT)0xE803032AL)

//
// MessageId: E_NA_SET_UNLEVEL_SRC2_SYNTH
//
// MessageText:
//
//  E_NA_SET_UNLEVEL_SRC2_SYNTH
//
#define E_NA_SET_UNLEVEL_SRC2_SYNTH      ((HRESULT)0xE803032BL)

//
// MessageId: E_NA_CLR_UNLEVEL_SRC2_SYNTH
//
// MessageText:
//
//  E_NA_CLR_UNLEVEL_SRC2_SYNTH
//
#define E_NA_CLR_UNLEVEL_SRC2_SYNTH      ((HRESULT)0xE803032CL)

//
// MessageId: E_NA_SET_UNLEVEL_LO_SYNTH
//
// MessageText:
//
//  E_NA_SET_UNLEVEL_LO_SYNTH
//
#define E_NA_SET_UNLEVEL_LO_SYNTH        ((HRESULT)0xE803032DL)

//
// MessageId: E_NA_CLR_UNLEVEL_LO_SYNTH
//
// MessageText:
//
//  E_NA_CLR_UNLEVEL_LO_SYNTH
//
#define E_NA_CLR_UNLEVEL_LO_SYNTH        ((HRESULT)0xE803032EL)

//
// MessageId: E_NA_SET_UNLOCK_SRC1_LOW
//
// MessageText:
//
//  E_NA_SET_UNLOCK_SRC1_LOW
//
#define E_NA_SET_UNLOCK_SRC1_LOW         ((HRESULT)0xE803032FL)

//
// MessageId: E_NA_CLR_UNLOCK_SRC1_LOW
//
// MessageText:
//
//  E_NA_CLR_UNLOCK_SRC1_LOW
//
#define E_NA_CLR_UNLOCK_SRC1_LOW         ((HRESULT)0xE8030330L)

//
// MessageId: E_NA_SET_UNLOCK_SRC1_HI
//
// MessageText:
//
//  E_NA_SET_UNLOCK_SRC1_HI
//
#define E_NA_SET_UNLOCK_SRC1_HI          ((HRESULT)0xE8030331L)

//
// MessageId: E_NA_CLR_UNLOCK_SRC1_HI
//
// MessageText:
//
//  E_NA_CLR_UNLOCK_SRC1_HI
//
#define E_NA_CLR_UNLOCK_SRC1_HI          ((HRESULT)0xE8030332L)

//
// MessageId: E_NA_SET_UNLOCK_SRC1_HET
//
// MessageText:
//
//  E_NA_SET_UNLOCK_SRC1_HET
//
#define E_NA_SET_UNLOCK_SRC1_HET         ((HRESULT)0xE8030333L)

//
// MessageId: E_NA_CLR_UNLOCK_SRC1_HET
//
// MessageText:
//
//  E_NA_CLR_UNLOCK_SRC1_HET
//
#define E_NA_CLR_UNLOCK_SRC1_HET         ((HRESULT)0xE8030334L)

//
// MessageId: E_NA_SET_UNLOCK_SRC2_LOW
//
// MessageText:
//
//  E_NA_SET_UNLOCK_SRC2_LOW
//
#define E_NA_SET_UNLOCK_SRC2_LOW         ((HRESULT)0xE8030335L)

//
// MessageId: E_NA_CLR_UNLOCK_SRC2_LOW
//
// MessageText:
//
//  E_NA_CLR_UNLOCK_SRC2_LOW
//
#define E_NA_CLR_UNLOCK_SRC2_LOW         ((HRESULT)0xE8030336L)

//
// MessageId: E_NA_SET_UNLOCK_SRC2_HI
//
// MessageText:
//
//  E_NA_SET_UNLOCK_SRC2_HI
//
#define E_NA_SET_UNLOCK_SRC2_HI          ((HRESULT)0xE8030337L)

//
// MessageId: E_NA_CLR_UNLOCK_SRC2_HI
//
// MessageText:
//
//  E_NA_CLR_UNLOCK_SRC2_HI
//
#define E_NA_CLR_UNLOCK_SRC2_HI          ((HRESULT)0xE8030338L)

//
// MessageId: E_NA_SET_UNLOCK_SRC2_HET
//
// MessageText:
//
//  E_NA_SET_UNLOCK_SRC2_HET
//
#define E_NA_SET_UNLOCK_SRC2_HET         ((HRESULT)0xE8030339L)

//
// MessageId: E_NA_CLR_UNLOCK_SRC2_HET
//
// MessageText:
//
//  E_NA_CLR_UNLOCK_SRC2_HET
//
#define E_NA_CLR_UNLOCK_SRC2_HET         ((HRESULT)0xE803033AL)

//
// MessageId: E_NA_SET_UNLOCK_LO_LOW
//
// MessageText:
//
//  E_NA_SET_UNLOCK_LO_LOW
//
#define E_NA_SET_UNLOCK_LO_LOW           ((HRESULT)0xE803033BL)

//
// MessageId: E_NA_CLR_UNLOCK_LO_LOW
//
// MessageText:
//
//  E_NA_CLR_UNLOCK_LO_LOW
//
#define E_NA_CLR_UNLOCK_LO_LOW           ((HRESULT)0xE803033CL)

//
// MessageId: E_NA_SET_UNLOCK_LO_HI
//
// MessageText:
//
//  E_NA_SET_UNLOCK_LO_HI
//
#define E_NA_SET_UNLOCK_LO_HI            ((HRESULT)0xE803033DL)

//
// MessageId: E_NA_CLR_UNLOCK_LO_HI
//
// MessageText:
//
//  E_NA_CLR_UNLOCK_LO_HI
//
#define E_NA_CLR_UNLOCK_LO_HI            ((HRESULT)0xE803033EL)

//
// MessageId: E_NA_SET_UNLOCK_LO_HET
//
// MessageText:
//
//  E_NA_SET_UNLOCK_LO_HET
//
#define E_NA_SET_UNLOCK_LO_HET           ((HRESULT)0xE803033FL)

//
// MessageId: E_NA_CLR_UNLOCK_LO_HET
//
// MessageText:
//
//  E_NA_CLR_UNLOCK_LO_HET
//
#define E_NA_CLR_UNLOCK_LO_HET           ((HRESULT)0xE8030340L)

//
// MessageId: E_NA_NOISE_COMPRESS_MSG
//
// MessageText:
//
// Compression in noise receiver: excess signal.
//
#define E_NA_NOISE_COMPRESS_MSG          ((HRESULT)0xE8030341L)

//
// MessageId: E_NA_NOISE_DAMAGE_MSG
//
// MessageText:
//
// Compression in noise receiver: gain has been limited.
//
#define E_NA_NOISE_DAMAGE_MSG            ((HRESULT)0xE8030342L)

//
// MessageId: E_NA_NOISE_OVERRANGE_MSG
//
// MessageText:
//
// ADC over-range in noise receiver: excess signal.
//
#define E_NA_NOISE_OVERRANGE_MSG         ((HRESULT)0xE8030343L)

//
// MessageId: E_NA_NOISE_COMPRESS_EVENT
//
// MessageText:
//
//  E_NA_NOISE_COMPRESS_EVENT
//
#define E_NA_NOISE_COMPRESS_EVENT        ((HRESULT)0xE8030344L)

//
// MessageId: E_NA_NOISE_DAMAGE_EVENT
//
// MessageText:
//
//  E_NA_NOISE_DAMAGE_EVENT
//
#define E_NA_NOISE_DAMAGE_EVENT          ((HRESULT)0xE8030345L)

//
// MessageId: E_NA_NOISE_OVERRANGE_EVENT
//
// MessageText:
//
//  E_NA_NOISE_OVERRANGE_EVENT
//
#define E_NA_NOISE_OVERRANGE_EVENT       ((HRESULT)0xE8030346L)

//
// MessageId: E_NA_PXI_HW_ERROR
//
// MessageText:
//
// HARDWARE ERROR%1
//
#define E_NA_PXI_HW_ERROR                ((HRESULT)0xE8030347L)

//
// MessageId: E_NA_SET_PXI_HW_ERROR
//
// MessageText:
//
//  E_NA_SET_PXI_HW_ERROR
//
#define E_NA_SET_PXI_HW_ERROR            ((HRESULT)0xE8030348L)

//
// MessageId: E_NA_CLR_PXI_HW_ERROR
//
// MessageText:
//
//  E_NA_CLR_PXI_HW_ERROR
//
#define E_NA_CLR_PXI_HW_ERROR            ((HRESULT)0xE8030349L)

//
// MessageId: E_NA_HW_PXI_TIMEOUT_ERROR
//
// MessageText:
//
// Hardware Error: Time out while waiting for hardware to respond.
//
#define E_NA_HW_PXI_TIMEOUT_ERROR        ((HRESULT)0xE803034AL)

//
// MessageId: E_NA_PHASELOCK
//
// MessageText:
//
// Phaselock lost.
//
#define E_NA_PHASELOCK                   ((HRESULT)0xE8030350L)

//
// MessageId: S_NA_PHASELOCK_OK
//
// MessageText:
//
// Phaselock restored.
//
#define S_NA_PHASELOCK_OK                ((HRESULT)0x28030351L)

//
// MessageId: E_NA_HARDWARE
//
// MessageText:
//
// Unknown hardware error.
//
#define E_NA_HARDWARE                    ((HRESULT)0xE8030352L)

//
// MessageId: E_NA_DSPCOMM
//
// MessageText:
//
// DSP communication lost.
//
#define E_NA_DSPCOMM                     ((HRESULT)0xE8030353L)

//
// MessageId: E_NA_RFPOWEROFF
//
// MessageText:
//
// RF power off.
//
#define E_NA_RFPOWEROFF                  ((HRESULT)0xE8030354L)

//
// MessageId: S_NA_RFPOWERON
//
// MessageText:
//
// RF power on.
//
#define S_NA_RFPOWERON                   ((HRESULT)0x28030355L)

//
// MessageId: S_NA_HARDWAREOK
//
// MessageText:
//
// Hardware OK.
//
#define S_NA_HARDWAREOK                  ((HRESULT)0x28030356L)

//
// MessageId: E_NA_UNLEVELED
//
// MessageText:
//
// Source unleveled.
//
#define E_NA_UNLEVELED                   ((HRESULT)0xE8030357L)

//
// MessageId: S_NA_UNLEVELED_OK
//
// MessageText:
//
// Source leveled.
//
#define S_NA_UNLEVELED_OK                ((HRESULT)0x28030358L)

//
// MessageId: E_NA_OVERLOAD
//
// MessageText:
//
// Noise ADC overloaded.
//
#define E_NA_OVERLOAD                    ((HRESULT)0xE8030359L)

//
// MessageId: S_NA_OVERLOAD_OK
//
// MessageText:
//
// Input no longer overloaded.
//
#define S_NA_OVERLOAD_OK                 ((HRESULT)0x2803035AL)

//
// MessageId: E_NA_YIG_CAL_FAILED
//
// MessageText:
//
// Yig calibration failed.
//
#define E_NA_YIG_CAL_FAILED              ((HRESULT)0xE803035BL)

//
// MessageId: S_NA_YIG_CAL_FAILED_OK
//
// MessageText:
//
// Yig calibrated.
//
#define S_NA_YIG_CAL_FAILED_OK           ((HRESULT)0x2803035CL)

//
// MessageId: E_NA_RAMP_CAL_FAILED
//
// MessageText:
//
// Analog ramp calibration failed.
//
#define E_NA_RAMP_CAL_FAILED             ((HRESULT)0xE803035DL)

//
// MessageId: S_NA_RAMP_CAL_FAILED_OK
//
// MessageText:
//
// Analog ramp calibrated.
//
#define S_NA_RAMP_CAL_FAILED_OK          ((HRESULT)0x2803035EL)

//
// MessageId: E_NA_OVERTEMP
//
// MessageText:
//
// Source temperature high.
//
#define E_NA_OVERTEMP                    ((HRESULT)0xE803035FL)

//
// MessageId: S_NA_OVERTEMP_OK
//
// MessageText:
//
// Source temperature OK.
//
#define S_NA_OVERTEMP_OK                 ((HRESULT)0x28030360L)

//
// MessageId: E_NA_EE_WRT_ERR
//
// MessageText:
//
// EEPROM write failed.
//
#define E_NA_EE_WRT_ERR                  ((HRESULT)0xE8030361L)

//
// MessageId: S_NA_EE_WRT_ERR_OK
//
// MessageText:
//
// EEPROM write succeeded.
//
#define S_NA_EE_WRT_ERR_OK               ((HRESULT)0x28030362L)

//
// MessageId: E_NA_IO_INVALID_WRITE
//
// MessageText:
//
// Attempted I/O write while port set to read only.
//
#define E_NA_IO_INVALID_WRITE            ((HRESULT)0xE8030363L)

//
// MessageId: E_NA_IO_INVALID_READ
//
// MessageText:
//
// Attempted I/O read from write only port.
//
#define E_NA_IO_INVALID_READ             ((HRESULT)0xE8030364L)

//
// MessageId: E_NA_INVALID_HW_ID
//
// MessageText:
//
// Invalid hardware element identifier.
//
#define E_NA_INVALID_HW_ID               ((HRESULT)0xE8030365L)

//
// MessageId: E_NA_INVALID_HW_GAIN_LEVEL
//
// MessageText:
//
// Invalid gain level setting.
//
#define E_NA_INVALID_HW_GAIN_LEVEL       ((HRESULT)0xE8030366L)

//
// MessageId: E_NA_DMA_BUFFER_TOO_SMALL
//
// MessageText:
//
// Device driver was unable to allocate enough memory. Please try rebooting.
//
#define E_NA_DMA_BUFFER_TOO_SMALL        ((HRESULT)0xE8030367L)

//
// MessageId: E_NA_HW_SPECIAL_ERROR_SPAM_TYPE_1
//
// MessageText:
//
// DSP Type 1 Error: DSP MAN_TRIG_READY message with no current meas spec.  Please Contact Keysight Support.
//
#define E_NA_HW_SPECIAL_ERROR_SPAM_TYPE_1 ((HRESULT)0xE8030368L)

//
// MessageId: E_NA_HW_SPECIAL_ERROR_SPAM_TYPE_2
//
// MessageText:
//
// DSP Type 2 Error: DSP timeout in response to Abort message. Please Contact Keysight Support.
//
#define E_NA_HW_SPECIAL_ERROR_SPAM_TYPE_2 ((HRESULT)0xE8030369L)

//
// MessageId: E_NA_HW_SPECIAL_ERROR_SPAM_TYPE_3
//
// MessageText:
//
// DSP Type 3 Error: DSP timeout in response to Run message. Please Contact Keysight Support.
//
#define E_NA_HW_SPECIAL_ERROR_SPAM_TYPE_3 ((HRESULT)0xE803036AL)

//
// MessageId: E_NA_HW_SPECIAL_ERROR_SPAM_TYPE_4
//
// MessageText:
//
// DSP Type 4 Error: Host received unexpected DATA_READY or DATA_DONE message. Please Contact Keysight Support.
//
#define E_NA_HW_SPECIAL_ERROR_SPAM_TYPE_4 ((HRESULT)0xE803036BL)

//
// MessageId: E_NA_HW_SPECIAL_ERROR_SPAM_TYPE_5
//
// MessageText:
//
// Memory overflow. Trigger state set to Hold. Lower the IF bandwidth, or increase dwell or sweep time.
//
#define E_NA_HW_SPECIAL_ERROR_SPAM_TYPE_5 ((HRESULT)0xE803036CL)

//
// MessageId: E_NA_TESTSET_NOT_FOUND
//
// MessageText:
//
// A request was made for control of a testset which does not appear to be connected.
//
#define E_NA_TESTSET_NOT_FOUND           ((HRESULT)0xE803036DL)

//
// MessageId: E_NA_DSP_CPLD_REVISION
//
// MessageText:
//
// DSP CPLD Revision does not match installed firmware.
//
#define E_NA_DSP_CPLD_REVISION           ((HRESULT)0xE803036EL)

//
// MessageId: E_NA_HW_ADC_BUFFER_OVERRUN
//
// MessageText:
//
// ADC memory overflow. Trigger state set to Hold.
//
#define E_NA_HW_ADC_BUFFER_OVERRUN       ((HRESULT)0xE8030370L)

//
// MessageId: E_NA_HW_SPECIAL_ERROR_SPAM_TYPE_6
//
// MessageText:
//
// DSP Type 6 Error: DSP timeout for end of sweep event message. Please Contact Keysight Support.
//
#define E_NA_HW_SPECIAL_ERROR_SPAM_TYPE_6 ((HRESULT)0xE8030371L)

//
// MessageId: E_NA_NOT_A_VALID_PXI_ADDRESS
//
// MessageText:
//
// The specific PXI address is invalid.
//
#define E_NA_NOT_A_VALID_PXI_ADDRESS     ((HRESULT)0xE8030400L)

//
// MessageId: E_NA_PXI_ADDRESS_CONFLICT
//
// MessageText:
//
// PXI Module already in use
//
#define E_NA_PXI_ADDRESS_CONFLICT        ((HRESULT)0xE8030401L)

//
// MessageId: E_NA_POWER_RANGE_NO_DATA_AVAILABLE
//
// MessageText:
//
// No power range data available for selected path, frequency or power range type.
//
#define E_NA_POWER_RANGE_NO_DATA_AVAILABLE ((HRESULT)0xE8030402L)

//
// MessageId: E_NA_POWER_RANGE_FREQ_ARRAY_DIMENSION
//
// MessageText:
//
// Power range frequency array must have at least one element in discrete mode and at least two elements in swept mode.
//
#define E_NA_POWER_RANGE_FREQ_ARRAY_DIMENSION ((HRESULT)0xE8030403L)

//
// MessageId: E_NA_POWER_RANGE_INVALID_PATH_NAME
//
// MessageText:
//
// Given path configuration is not a valid power range path.
//
#define E_NA_POWER_RANGE_INVALID_PATH_NAME ((HRESULT)0xE8030404L)

//
// MessageId: E_NA_POWER_RANGE_INVALID_FREQUENCY_RANGE
//
// MessageText:
//
// Power range requested inludes frequencies with no specification.
//
#define E_NA_POWER_RANGE_INVALID_FREQUENCY_RANGE ((HRESULT)0xE8030405L)

//
// MessageId: E_NA_POWER_RANGE_PARSER
//
// MessageText:
//
// Parser could not read power range data from specification file.
//
#define E_NA_POWER_RANGE_PARSER          ((HRESULT)0xE8030406L)

//
// MessageId: E_NA_POWER_RANGE_PARSER_FILE_NOT_FOUND
//
// MessageText:
//
// Parser could not open power range specification file.  This may because the file does not exist or because it is open in another program.
//
#define E_NA_POWER_RANGE_PARSER_FILE_NOT_FOUND ((HRESULT)0xE8030407L)

//
// MessageId: E_NA_POWER_RANGE_PARSER_INVALID_POWER_RANGE_TYPE
//
// MessageText:
//
// Parser encountered an invalid power range type while parsing power range specification file.
//
#define E_NA_POWER_RANGE_PARSER_INVALID_POWER_RANGE_TYPE ((HRESULT)0xE8030408L)    

//
// MessageId: E_NA_POWER_RANGE_PARSER_INVALID_OPTION
//
// MessageText:
//
// Power range parser encountered an invalid option while parsing power range specification file.
//
#define E_NA_POWER_RANGE_PARSER_INVALID_OPTION ((HRESULT)0xE8030409L)    

//
// MessageId: E_NA_POWER_RANGE_FREQ_BAND_OUT_OF_ORDER
//
// MessageText:
//
// Power range data must be specified in increasing order.  Band start frequencies must not be greater than corresponding band stop frequencies.
//
#define E_NA_POWER_RANGE_FREQ_BAND_OUT_OF_ORDER ((HRESULT)0xE803040AL)    

//
// MessageId: E_NA_POWER_RANGE_ALC_MODE
//
// MessageText:
//
// Power range data is not available for the current ALC leveling mode.
//
#define E_NA_POWER_RANGE_ALC_MODE        ((HRESULT)0xE803040BL)    

//
// MessageId: E_NA_POWER_RANGE_BANDED_MODE
//
// MessageText:
//
// Power range data is not available for banded mode.
//
#define E_NA_POWER_RANGE_BANDED_MODE     ((HRESULT)0xE803040CL)    

//
// MessageId: E_NA_POWER_RANGE_LFE
//
// MessageText:
//
// Power range data is not available with LFE.
//
#define E_NA_POWER_RANGE_LFE             ((HRESULT)0xE803040DL)    

//
// MessageId: E_NA_HW_UNSUPPORTED_HARDWARE
//
// MessageText:
//
// This software does not support this instrument model number.
//
#define E_NA_HW_UNSUPPORTED_HARDWARE     ((HRESULT)0xE803040EL)

//
// MessageId: E_NA_UNLEVELED_SRC2_Q
//
// MessageText:
//
// Unleveled, source 2
//
#define E_NA_UNLEVELED_SRC2_Q            ((HRESULT)0xE803036FL)

//
// MessageId: E_NA_UNLEVELED_SRC1_Q
//
// MessageText:
//
// Unleveled, source 1
//
#define E_NA_UNLEVELED_SRC1_Q            ((HRESULT)0xE803037CL)

//
// MessageId: E_NA_INCONSISTENT_TIMING
//
// MessageText:
//
// Caution:  Sweep time jitter.  Try reducing the number of segments.
//
#define E_NA_INCONSISTENT_TIMING         ((HRESULT)0xE803037DL)

//
// MessageId: E_NA_SOURCE_PULSE_WIDTH_LIMITED
//
// MessageText:
//
// Caution:  Source pulse width limited to 116nS.
//
#define E_NA_SOURCE_PULSE_WIDTH_LIMITED  ((HRESULT)0xE803037EL)

//
// MessageId: E_NA_FREQUENCY_REFERENCE_MISSING
//
// MessageText:
//
// Warning:  Missing frequency reference.
//
#define E_NA_FREQUENCY_REFERENCE_MISSING ((HRESULT)0xE803037FL)

//
// MessageId: E_NA_SET_EE_WRT_ERR
//
// MessageText:
//
//  E_NA_SET_EE_WRT_ERR
//
#define E_NA_SET_EE_WRT_ERR              ((HRESULT)0xE8030380L)

//
// MessageId: E_NA_CLR_EE_WRT_ERR
//
// MessageText:
//
//  E_NA_CLR_EE_WRT_ERR
//
#define E_NA_CLR_EE_WRT_ERR              ((HRESULT)0xE8030381L)

//
// MessageId: E_NA_SET_RAMP_CAL_FAILED
//
// MessageText:
//
//  E_NA_SET_RAMP_CAL_FAILED
//
#define E_NA_SET_RAMP_CAL_FAILED         ((HRESULT)0xE8030382L)

//
// MessageId: E_NA_CLR_RAMP_CAL_FAILED
//
// MessageText:
//
//  E_NA_CLR_RAMP_CAL_FAILED
//
#define E_NA_CLR_RAMP_CAL_FAILED         ((HRESULT)0xE8030383L)

//
// MessageId: E_NA_CLR_YIG_CAL_FAILED
//
// MessageText:
//
//  E_NA_CLR_YIG_CAL_FAILED
//
#define E_NA_CLR_YIG_CAL_FAILED          ((HRESULT)0xE8030384L)

//
// MessageId: E_NA_SET_YIG_CAL_FAILED
//
// MessageText:
//
//  E_NA_SET_YIG_CAL_FAILED
//
#define E_NA_SET_YIG_CAL_FAILED          ((HRESULT)0xE8030385L)

//
// MessageId: E_NA_SET_OVER_TEMP
//
// MessageText:
//
//  E_NA_SET_OVER_TEMP
//
#define E_NA_SET_OVER_TEMP               ((HRESULT)0xE8030386L)

//
// MessageId: E_NA_CLR_OVER_TEMP
//
// MessageText:
//
//  E_NA_CLR_OVER_TEMP
//
#define E_NA_CLR_OVER_TEMP               ((HRESULT)0xE8030387L)

//
// MessageId: E_NA_SET_UNLEVEL
//
// MessageText:
//
//  E_NA_SET_UNLEVEL
//
#define E_NA_SET_UNLEVEL                 ((HRESULT)0xE8030388L)

//
// MessageId: E_NA_CLR_UNLEVEL
//
// MessageText:
//
//  E_NA_CLR_UNLEVEL
//
#define E_NA_CLR_UNLEVEL                 ((HRESULT)0xE8030389L)

//
// MessageId: E_NA_SET_OVERLOAD
//
// MessageText:
//
//  E_NA_SET_OVERLOAD
//
#define E_NA_SET_OVERLOAD                ((HRESULT)0xE803038AL)

//
// MessageId: E_NA_CLR_OVERLOAD
//
// MessageText:
//
//  E_NA_CLR_OVERLOAD
//
#define E_NA_CLR_OVERLOAD                ((HRESULT)0xE803038BL)

//
// MessageId: E_NA_SET_UNLOCK
//
// MessageText:
//
//  E_NA_SET_UNLOCK
//
#define E_NA_SET_UNLOCK                  ((HRESULT)0xE803038CL)

//
// MessageId: E_NA_CLR_UNLOCK
//
// MessageText:
//
//  E_NA_CLR_UNLOCK
//
#define E_NA_CLR_UNLOCK                  ((HRESULT)0xE803038DL)

//
// MessageId: E_NA_INVALID_TRIGGER_CONNECTION_ARGUMENT
//
// MessageText:
//
// The trigger connection argument was not recognized as valid by the firmware.
//
#define E_NA_INVALID_TRIGGER_CONNECTION_ARGUMENT ((HRESULT)0xE803038EL)

//
// MessageId: E_NA_INVALID_TRIGGER_CONNECTION_TYPE
//
// MessageText:
//
// The trigger connection specified does not support this trigger behavior
//
#define E_NA_INVALID_TRIGGER_CONNECTION_TYPE ((HRESULT)0xE803038FL)

//
// MessageId: E_NA_INVALID_TRIGGER_CONNECTION_BEHAVIOR
//
// MessageText:
//
// The trigger behavior specified was not recognized as valid by the firmware.
//
#define E_NA_INVALID_TRIGGER_CONNECTION_BEHAVIOR ((HRESULT)0xE8030390L)

//
// MessageId: E_NA_TRIGGER_CONNECTION_DOES_NOT_EXIST
//
// MessageText:
//
// The trigger connection specified does not physically exist on this network analyzer
//
#define E_NA_TRIGGER_CONNECTION_DOES_NOT_EXIST ((HRESULT)0xE8030391L)

//
// MessageId: E_NA_TRIGGER_REQUIRES_EDGE_LEVEL_TRIGGER
//
// MessageText:
//
// Cannot set "Accept Trigger Before Armed", since this hardware configuration does not support edge triggering.
//
#define E_NA_TRIGGER_REQUIRES_EDGE_LEVEL_TRIGGER ((HRESULT)0xE8030392L)

//
// MessageId: E_NA_TRIGGER_REQUIRES_TRIGGER_OUT
//
// MessageText:
//
// Cannot set "Trigger Output Enabled", since this hardware configuration does not support BNC2.
//
#define E_NA_TRIGGER_REQUIRES_TRIGGER_OUT ((HRESULT)0xE8030393L)

//
// MessageId: E_HW_MAX_TRIGGER_DELAY
//
// MessageText:
//
// Exceeded maximum trigger delay.
//
#define E_HW_MAX_TRIGGER_DELAY           ((HRESULT)0xE8030394L)

//
// MessageId: E_HW_MIN_TRIGGER_DELAY
//
// MessageText:
//
// Exceeded minimum trigger delay.
//
#define E_HW_MIN_TRIGGER_DELAY           ((HRESULT)0xE8030395L)

//
// MessageId: E_NA_SET_UNLEVEL_SRC2
//
// MessageText:
//
//  E_NA_SET_UNLEVEL_SRC2
//
#define E_NA_SET_UNLEVEL_SRC2            ((HRESULT)0xE8030396L)

//
// MessageId: E_NA_CLR_UNLEVEL_SRC2
//
// MessageText:
//
//  E_NA_CLR_UNLEVEL_SRC2
//
#define E_NA_CLR_UNLEVEL_SRC2            ((HRESULT)0xE8030397L)

//
// MessageId: E_NA_SET_UNLEVEL_LO
//
// MessageText:
//
//  E_NA_SET_UNLEVEL_LO
//
#define E_NA_SET_UNLEVEL_LO              ((HRESULT)0xE8030398L)

//
// MessageId: E_NA_CLR_UNLEVEL_LO
//
// MessageText:
//
//  E_NA_CLR_UNLEVEL_LO
//
#define E_NA_CLR_UNLEVEL_LO              ((HRESULT)0xE8030399L)

//
// MessageId: E_NA_SET_UNLEVEL_SRC1
//
// MessageText:
//
//  E_NA_SET_UNLEVEL_SRC1
//
#define E_NA_SET_UNLEVEL_SRC1            ((HRESULT)0xE803039AL)

//
// MessageId: E_NA_CLR_UNLEVEL_SRC1
//
// MessageText:
//
//  E_NA_CLR_UNLEVEL_SRC1
//
#define E_NA_CLR_UNLEVEL_SRC1            ((HRESULT)0xE803039BL)

//
// MessageId: E_NA_FIFO_RAM_BUFFER_OVERFLOW
//
// MessageText:
//
// ERROR: The FIFO RAM buffer has entered an overflow condition. Some data has been lost and has not been recorded in the FIFO.
//
#define E_NA_FIFO_RAM_BUFFER_OVERFLOW    ((HRESULT)0xE803039CL)

//
// MessageId: E_NA_FIFO_OVERFLOW
//
// MessageText:
//
// ERROR: The FIFO has been overflowed. The maximum capacity of the FIFO is 500,000,000 (500 million) buckets.
//
#define E_NA_FIFO_OVERFLOW               ((HRESULT)0xE803039DL)

//
// MessageId: MSG_RXLEVELING_UNLEVELED_MIN
//
// MessageText:
//
// Rx Leveling failed: power set to min power limit.
//
#define MSG_RXLEVELING_UNLEVELED_MIN     ((HRESULT)0xA803039EL)

//
// MessageId: MSG_RXLEVELING_UNLEVELED_MAX
//
// MessageText:
//
// Rx Leveling failed: power set to max power limit.
//
#define MSG_RXLEVELING_UNLEVELED_MAX     ((HRESULT)0xA803039FL)

//
// MessageId: MSG_RXLEVELING_UNLEVELED_NOISY
//
// MessageText:
//
// Rx Leveling warning: not settled, noisy trace.
//
#define MSG_RXLEVELING_UNLEVELED_NOISY   ((HRESULT)0xA80303A0L)

//
// MessageId: MSG_RXLEVELING_UNLEVELED_SETTING
//
// MessageText:
//
// Rx Leveling failed: power set to user power limit.
//
#define MSG_RXLEVELING_UNLEVELED_SETTING ((HRESULT)0xA80303A1L)

//
// MessageId: E_NA_UNLEVELED_SRC1_OUT1_PRELEVEL
//
// MessageText:
//
// Unleveled, doubler 1 prelevel
//
#define E_NA_UNLEVELED_SRC1_OUT1_PRELEVEL ((HRESULT)0xE80303A2L)

//
// MessageId: E_NA_SET_UNLEVEL_SRC1_OUT1_PRELEVEL
//
// MessageText:
//
//  E_NA_SET_UNLEVEL_SRC1_OUT1_PRELEVEL
//
#define E_NA_SET_UNLEVEL_SRC1_OUT1_PRELEVEL ((HRESULT)0xE80303A3L)

//
// MessageId: E_NA_CLR_UNLEVEL_SRC1_OUT1_PRELEVEL
//
// MessageText:
//
//  E_NA_CLR_UNLEVEL_SRC1_OUT1_PRELEVEL
//
#define E_NA_CLR_UNLEVEL_SRC1_OUT1_PRELEVEL ((HRESULT)0xE80303A4L)

//
// MessageId: E_NA_UNLEVELED_SRC1_OUT2_PRELEVEL
//
// MessageText:
//
// Unleveled, doubler 2 prelevel
//
#define E_NA_UNLEVELED_SRC1_OUT2_PRELEVEL ((HRESULT)0xE80303A5L)

//
// MessageId: E_NA_SET_UNLEVEL_SRC1_OUT2_PRELEVEL
//
// MessageText:
//
//  E_NA_SET_UNLEVEL_SRC1_OUT2_PRELEVEL
//
#define E_NA_SET_UNLEVEL_SRC1_OUT2_PRELEVEL ((HRESULT)0xE80303A6L)

//
// MessageId: E_NA_CLR_UNLEVEL_SRC1_OUT2_PRELEVEL
//
// MessageText:
//
//  E_NA_CLR_UNLEVEL_SRC1_OUT2_PRELEVEL
//
#define E_NA_CLR_UNLEVEL_SRC1_OUT2_PRELEVEL ((HRESULT)0xE80303A7L)

//
// MessageId: E_NA_UNLEVELED_SRC2_OUT1_PRELEVEL
//
// MessageText:
//
// Unleveled, doubler 3 prelevel
//
#define E_NA_UNLEVELED_SRC2_OUT1_PRELEVEL ((HRESULT)0xE80303A8L)

//
// MessageId: E_NA_SET_UNLEVEL_SRC2_OUT1_PRELEVEL
//
// MessageText:
//
//  E_NA_SET_UNLEVEL_SRC2_OUT1_PRELEVEL
//
#define E_NA_SET_UNLEVEL_SRC2_OUT1_PRELEVEL ((HRESULT)0xE80303A9L)

//
// MessageId: E_NA_CLR_UNLEVEL_SRC2_OUT1_PRELEVEL
//
// MessageText:
//
//  E_NA_CLR_UNLEVEL_SRC2_OUT1_PRELEVEL
//
#define E_NA_CLR_UNLEVEL_SRC2_OUT1_PRELEVEL ((HRESULT)0xE80303AAL)

//
// MessageId: E_NA_UNLEVELED_SRC2_OUT2_PRELEVEL
//
// MessageText:
//
// Unleveled, doubler 4 prelevel
//
#define E_NA_UNLEVELED_SRC2_OUT2_PRELEVEL ((HRESULT)0xE80303ABL)

//
// MessageId: E_NA_SET_UNLEVEL_SRC2_OUT2_PRELEVEL
//
// MessageText:
//
//  E_NA_SET_UNLEVEL_SRC2_OUT2_PRELEVEL
//
#define E_NA_SET_UNLEVEL_SRC2_OUT2_PRELEVEL ((HRESULT)0xE80303ACL)

//
// MessageId: E_NA_CLR_UNLEVEL_SRC2_OUT2_PRELEVEL
//
// MessageText:
//
//  E_NA_CLR_UNLEVEL_SRC2_OUT2_PRELEVEL
//
#define E_NA_CLR_UNLEVEL_SRC2_OUT2_PRELEVEL ((HRESULT)0xE80303ADL)

//
// MessageId: E_NA_UNLEVELED_SRC1_20_H11
//
// MessageText:
//
// Unleveled, source 1 P4
//
#define E_NA_UNLEVELED_SRC1_20_H11       ((HRESULT)0xE80303AEL)

//
// MessageId: E_NA_SET_UNLEVEL_SRC1_20_H11
//
// MessageText:
//
//  E_NA_SET_UNLEVEL_SRC1_20_H11
//
#define E_NA_SET_UNLEVEL_SRC1_20_H11     ((HRESULT)0xE80303AFL)

//
// MessageId: E_NA_CLR_UNLEVEL_SRC1_20_H11
//
// MessageText:
//
//  E_NA_CLR_UNLEVEL_SRC1_20_H11
//
#define E_NA_CLR_UNLEVEL_SRC1_20_H11     ((HRESULT)0xE80303B0L)

//
// MessageId: E_NA_UNLEVELED_SRC2_20_H11
//
// MessageText:
//
// Unleveled, source 2 P4
//
#define E_NA_UNLEVELED_SRC2_20_H11       ((HRESULT)0xE80303B1L)

//
// MessageId: E_NA_SET_UNLEVEL_SRC2_20_H11
//
// MessageText:
//
//  E_NA_SET_UNLEVEL_SRC2_20_H11
//
#define E_NA_SET_UNLEVEL_SRC2_20_H11     ((HRESULT)0xE80303B2L)

//
// MessageId: E_NA_CLR_UNLEVEL_SRC2_20_H11
//
// MessageText:
//
//  E_NA_CLR_UNLEVEL_SRC2_20_H11
//
#define E_NA_CLR_UNLEVEL_SRC2_20_H11     ((HRESULT)0xE80303B3L)

//
// MessageId: MSG_EXCEED_FREQ
//
// MessageText:
//
// Read Power Failed: Frequency exceeds the range.
//
#define MSG_EXCEED_FREQ                  ((HRESULT)0xA80303B4L)

//
// MessageId: E_NA_NO_SENSOR_CONNECTED
//
// MessageText:
//
// Read Power Failed: No such sensor connected.
//
#define E_NA_NO_SENSOR_CONNECTED         ((HRESULT)0xE80303B5L)

//
// MessageId: E_NA_EXTERNAL_METER_LOST
//
// MessageText:
//
// Read Power Failed: External Power Meter lost.
//
#define E_NA_EXTERNAL_METER_LOST         ((HRESULT)0xE80303B6L)

//
// MessageId: MSG_RS_EXCEED_FREQ
//
// MessageText:
//
// Read Power Failed: Frequency exceeds the range.
//
#define MSG_RS_EXCEED_FREQ               ((HRESULT)0xA80303B7L)

//
// MessageId: E_NA_RECEIVER_OVER_LOAD
//
// MessageText:
//
// WARNING: Receiver %1 overload
//
#define E_NA_RECEIVER_OVER_LOAD          ((HRESULT)0xE80803B8L)

//
// MessageId: MSG_RF_POWER_OFF
//
// MessageText:
//
// The RF source power has been turned off due to overload condition.
//
#define MSG_RF_POWER_OFF                 ((HRESULT)0xA80403BAL)

//
// MessageId: MSG_REPEAT_LAST_POINT
//
// MessageText:
//
// Repeat last point.
//
#define MSG_REPEAT_LAST_POINT            ((HRESULT)0x680303BBL)

//
// MessageId: E_NA_UNLEVELED_NOISE50
//
// MessageText:
//
// Unleveled, noise LO
//
#define E_NA_UNLEVELED_NOISE50           ((HRESULT)0xE80303BCL)

//
// MessageId: E_NA_CLR_UNLEVEL_NOISE50
//
// MessageText:
//
//  E_NA_CLR_UNLEVEL_NOISE50
//
#define E_NA_CLR_UNLEVEL_NOISE50         ((HRESULT)0xE80303BDL)

//
// MessageId: E_NA_SET_UNLEVEL_NOISE50
//
// MessageText:
//
//  E_NA_SET_UNLEVEL_NOISE50
//
#define E_NA_SET_UNLEVEL_NOISE50         ((HRESULT)0xE80303BEL)

//
// MessageId: MSG_REPEAT_LAST_VALUE
//
// MessageText:
//
// Repeat last point.
//
#define MSG_REPEAT_LAST_VALUE            ((HRESULT)0x680303BFL)

//
// MessageId: E_NA_IF_CALIBRATION_MISSING
//
// MessageText:
//
// Warning:  Missing IF Response Adjustment
//
#define E_NA_IF_CALIBRATION_MISSING      ((HRESULT)0xE80303C0L)

//
// MessageId: E_NA_SERNO_FORMAT_BAD
//
// MessageText:
//
// The serial number format is bad.
//
#define E_NA_SERNO_FORMAT_BAD            ((HRESULT)0xE80303C1L)

//
// MessageId: E_NA_HW_WRITE_FAILED
//
// MessageText:
//
// Hardware write failed.
//
#define E_NA_HW_WRITE_FAILED             ((HRESULT)0xE80303C2L)

//
// MessageId: E_NA_HW_SECURE_MEMORY_ACCESS
//
// MessageText:
//
// Attempt to access secure memory region.
//
#define E_NA_HW_SECURE_MEMORY_ACCESS     ((HRESULT)0xE80303C3L)

//
// MessageId: E_NA_HW_CANNOT_READ_WRITE_FLASH
//
// MessageText:
//
// Cannot read/write flash value. Bad spelling or band number, or not linked.
//
#define E_NA_HW_CANNOT_READ_WRITE_FLASH  ((HRESULT)0xE80303C4L)

//
// MessageId: E_NA_HW_NO_FLASH
//
// MessageText:
//
// No flash present on this instrument.
//
#define E_NA_HW_NO_FLASH                 ((HRESULT)0xE80303C5L)

//
// MessageId: E_NA_HW_CANNOT_FIND_FLASH_FILE
//
// MessageText:
//
// Bad flash file number.
//
#define E_NA_HW_CANNOT_FIND_FLASH_FILE   ((HRESULT)0xE80303C6L)

//
// MessageId: E_NA_HW_CANNOT_ERASE_FLASH
//
// MessageText:
//
// Error erasing flash. Possible bad part or firmware problem.
//
#define E_NA_HW_CANNOT_ERASE_FLASH       ((HRESULT)0xE80303C7L)

//
// MessageId: E_NA_HW_CANNOT_WRITE_FLASH
//
// MessageText:
//
// Error writing flashfile.
//
#define E_NA_HW_CANNOT_WRITE_FLASH       ((HRESULT)0xE80303C8L)

//
// MessageId: E_NA_HW_READ_FAILED
//
// MessageText:
//
// Hardware read failed.
//
#define E_NA_HW_READ_FAILED              ((HRESULT)0xE80303C9L)

//
// MessageId: E_NA_HW_CAL_ACCESS_FAILED
//
// MessageText:
//
// Calibration data access failed.
//
#define E_NA_HW_CAL_ACCESS_FAILED        ((HRESULT)0xE80303CAL)

//
// MessageId: E_NA_HW_MEM_RANGE_EXCEEDED
//
// MessageText:
//
// Command exceeds usable memory range.
//
#define E_NA_HW_MEM_RANGE_EXCEEDED       ((HRESULT)0xE80303CBL)

//
// MessageId: E_NA_HW_SNUM_PROTECTED
//
// MessageText:
//
// The serial number is protected.
//
#define E_NA_HW_SNUM_PROTECTED           ((HRESULT)0xE80303CCL)

//
// MessageId: E_NA_HW_DSP_ACTIVE
//
// MessageText:
//
// Failed because DSP was not halted.
//
#define E_NA_HW_DSP_ACTIVE               ((HRESULT)0xE80303CDL)

//
// MessageId: E_NA_SERNO_ALREADY_SET
//
// MessageText:
//
// The serial number is already set.
//
#define E_NA_SERNO_ALREADY_SET           ((HRESULT)0xE80303CEL)

//
// MessageId: E_SA_GATE_MANY_TOO_SHORT
//
// MessageText:
//
// Measurement has stopped because External Trigger input length is too short. Increase the Trigger length or reduce the ADC record size.
//
#define E_SA_GATE_MANY_TOO_SHORT         ((HRESULT)0xA80403CFL)

//
// MessageId: E_NA_MIXER_CALIBRATION_MISSING
//
// MessageText:
//
// Missing Factory Mixer Calibration
//
#define E_NA_MIXER_CALIBRATION_MISSING   ((HRESULT)0xE80303D0L)

//
// MessageId: E_NA_N5291A_FLASH_WRITE_FAILED_HARD
//
// MessageText:
//
// Failed to write a flash subsector after 10 attempts.
//
#define E_NA_N5291A_FLASH_WRITE_FAILED_HARD ((HRESULT)0xE80303D1L)

//
// MessageId: E_NA_N5291A_FLASH_WRITE_FAILED_SOFT
//
// MessageText:
//
// Failed to write a flash subsector.
//
#define E_NA_N5291A_FLASH_WRITE_FAILED_SOFT ((HRESULT)0xA80303D2L)

//
// MessageId: E_NA_N5291A_FLASH_READ_FAILED
//
// MessageText:
//
// Data read from flash either corrupt or no data present.
//
#define E_NA_N5291A_FLASH_READ_FAILED    ((HRESULT)0xE80303D3L)

//
// MessageId: E_NA_TESTSET_LOCKED_UP
//
// MessageText:
//
// The test set has become unresponsive and must be power-cycled.
//
#define E_NA_TESTSET_LOCKED_UP           ((HRESULT)0xE80303D4L)

//
// MessageId: E_NA_N5291A_FPGA_PROG_FAILED
//
// MessageText:
//
// Failed to program a N5291A FPGA
//
#define E_NA_N5291A_FPGA_PROG_FAILED     ((HRESULT)0xE80303D5L)

//
// MessageId: MSG_NO_VALID_MEMORY_TRACE
//
// MessageText:
//
// If you are going to display or otherwise use a memory trace, you must
// first store a data trace to memory.
//
#define MSG_NO_VALID_MEMORY_TRACE        ((HRESULT)0xA8040400L)

//
// MessageId: MSG_MEASUREMENT_DELETE_FAIL
//
// MessageText:
//
// The measurement failed to shut down properly.  The application is in a 
// corrupt state and should be shut down and restarted.
//
#define MSG_MEASUREMENT_DELETE_FAIL      ((HRESULT)0xE8040401L)

//
// MessageId: MSG_MEASUREMENT_WAIT_THREAD_FAIL
//
// MessageText:
//
// The measurement failed to shut down properly.  The update thread failed
// to exit properly.
//
#define MSG_MEASUREMENT_WAIT_THREAD_FAIL ((HRESULT)0xA8040402L)

//
// MessageId: MSG_GROUPDELAY_FORMAT_NOT_VALID
//
// MessageText:
//
// Group Delay format with CW Time or Power sweeps produces invalid data.
//
#define MSG_GROUPDELAY_FORMAT_NOT_VALID  ((HRESULT)0xA8040403L)

//
// MessageId: MSG_LIMIT_FAILED
//
// MessageText:
//
//  MSG_LIMIT_FAILED
//
#define MSG_LIMIT_FAILED                 ((HRESULT)0x68040404L)

//
// MessageId: MSG_LIMIT_PASSED
//
// MessageText:
//
//  MSG_LIMIT_PASSED
//
#define MSG_LIMIT_PASSED                 ((HRESULT)0x68040405L)

//
// MessageId: MSG_EXCEED_MAX_MEAS
//
// MessageText:
//
// Exceeded the maximum number of measurements allowed.
//
#define MSG_EXCEED_MAX_MEAS              ((HRESULT)0xA8040406L)

//
// MessageId: MSG_NETANA_ERROR_ADDNEWMEAS
//
// MessageText:
//
// Network Analyzer Internal Error.  
// Unexpected error in AddNewMeasurement.
//
#define MSG_NETANA_ERROR_ADDNEWMEAS      ((HRESULT)0xA8040407L)

//
// MessageId: MSG_NO_MEASUREMENT_FOUND
//
// MessageText:
//
// No measurement was found to perform the selected operation.  
// Operation not completed.
//
#define MSG_NO_MEASUREMENT_FOUND         ((HRESULT)0xA8040408L)

//
// MessageId: MSG_MARKER_ALL_OFF_FAILED
//
// MessageText:
//
// The Markers All Off command failed.  
//
#define MSG_MARKER_ALL_OFF_FAILED        ((HRESULT)0xA8040409L)

//
// MessageId: MSG_MEMORY_NOT_SAVED
//
// MessageText:
//
// A memory trace has not been saved for the selected trace.
// Save a memory trace before attempting trace math operations.
//
#define MSG_MEMORY_NOT_SAVED             ((HRESULT)0xA804040AL)

//
// MessageId: MSG_SET_AVERAGE_COMPLETE
//
// MessageText:
//
//  MSG_SET_AVERAGE_COMPLETE
//
#define MSG_SET_AVERAGE_COMPLETE         ((HRESULT)0x6804040BL)

//
// MessageId: MSG_CLEAR_AVERAGE_COMPLETE
//
// MessageText:
//
//  MSG_CLEAR_AVERAGE_COMPLETE
//
#define MSG_CLEAR_AVERAGE_COMPLETE       ((HRESULT)0x6804040CL)

//
// MessageId: MSG_TIME_DOMAIN_MINIMUM_POINTS
//
// MessageText:
//
// Time Domain transform requires at least %1 input points.  The 
// transform has been deactivated.
//
#define MSG_TIME_DOMAIN_MINIMUM_POINTS   ((HRESULT)0x6804040DL)

//
// MessageId: MSG_SMOOTHING_SCALAR_ONLY
//
// MessageText:
//
// Smoothing requires a scalar format, and has been deactivated.
//
#define MSG_SMOOTHING_SCALAR_ONLY        ((HRESULT)0x6804040EL)

//
// MessageId: MSG_CANNOT_RECALL_RECEIVER_POWER_CAL
//
// MessageText:
//
// A receiver power calibration in this instrument state file cannot
// be recalled into this firmware version.
//
#define MSG_CANNOT_RECALL_RECEIVER_POWER_CAL ((HRESULT)0xA804040FL)

//
// MessageId: MSG_TIME_DOMAIN_LOWPASS_STIMULUS_INCORRECT
//
// MessageText:
//
// Time Domain transform in low pass mode requires that 
// Stop Frequency = Start Frequency * Number of Points.  The low pass transform 
// has been deactivated.
//
#define MSG_TIME_DOMAIN_LOWPASS_STIMULUS_INCORRECT ((HRESULT)0x68040410L)

//
// MessageId: E_NA_EXCEED_MAX_NUM_MEAS
//
// MessageText:
//
// Exceeded limit on number of measurements.
//
#define E_NA_EXCEED_MAX_NUM_MEAS         ((HRESULT)0xE8040450L)

//
// MessageId: E_NA_BAD_PARAMETER
//
// MessageText:
//
// Parameter not valid.
//
#define E_NA_BAD_PARAMETER               ((HRESULT)0xE8040451L)

//
// MessageId: E_NA_NO_MEAS
//
// MessageText:
//
// Measurement not found.
//
#define E_NA_NO_MEAS                     ((HRESULT)0xE8040452L)

//
// MessageId: E_NA_NO_MEMORY_BUFFER
//
// MessageText:
//
// No valid memory trace.
//
#define E_NA_NO_MEMORY_BUFFER            ((HRESULT)0xE8040453L)

//
// MessageId: E_NA_NO_REFERENCE_MARKER
//
// MessageText:
//
// The reference marker was not found.
//
#define E_NA_NO_REFERENCE_MARKER         ((HRESULT)0xE8040454L)

//
// MessageId: E_NA_TRACE_MATH_RESET
//
// MessageText:
//
// Data and Memory traces are no longer compatible.
// Trace Math has been turned off.
//
#define E_NA_TRACE_MATH_RESET            ((HRESULT)0xA8040455L)

//
// MessageId: E_NA_MEMORY_TRACE_NOT_COMPATIBLE
//
// MessageText:
//
// Data and Memory traces are not compatible.
// For valid trace math operations, memory and data traces must have 
// similar measurement conditions.
//
#define E_NA_MEMORY_TRACE_NOT_COMPATIBLE ((HRESULT)0xE8040456L)

//
// MessageId: E_NA_MARKER_BANDWIDTH_NOT_FOUND
//
// MessageText:
//
// Marker Bandwidth not found.
//
#define E_NA_MARKER_BANDWIDTH_NOT_FOUND  ((HRESULT)0xE8040457L)

//
// MessageId: E_NA_PEAK_NOT_FOUND
//
// MessageText:
//
// The peak was not found.
//
#define E_NA_PEAK_NOT_FOUND              ((HRESULT)0xE8040458L)

//
// MessageId: E_NA_TARGET_VALUE_NOT_FOUND
//
// MessageText:
//
// The target search value was not found.
//
#define E_NA_TARGET_VALUE_NOT_FOUND      ((HRESULT)0xE8040459L)

//
// MessageId: E_NA_AMBIGUOUS_REFLECTION_PARAMETER
//
// MessageText:
//
// Reflection measurement, such as S11, must supply an auxiliary port to
// disambiguate 2-port measurements on multiport instruments.
//
#define E_NA_AMBIGUOUS_REFLECTION_PARAMETER ((HRESULT)0xE804045AL)

//
// MessageId: E_NA_RECEIVER_POWER_CAL_RESET
//
// MessageText:
//
// The receiver power calibration has been turned off because the type of
// measurement or source port has changed, so the calibration is no longer valid.
//
#define E_NA_RECEIVER_POWER_CAL_RESET    ((HRESULT)0xA804045BL)

//
// MessageId: E_NA_INVALID_PARAM_FOR_RECEIVER_POWER_CAL
//
// MessageText:
//
// Receiver power cal requires the active measurement to be of unratioed power.
//
#define E_NA_INVALID_PARAM_FOR_RECEIVER_POWER_CAL ((HRESULT)0xA804045CL)

//
// MessageId: E_NA_RECEIVER_POWER_CAL_NEEDS_SOURCE_POWER_CAL
//
// MessageText:
//
// There is currently no source power calibration associated with the channel and 
// source port of the active measurement.  A source power cal should be performed
// or recalled before performing a receiver power calibration.
//
#define E_NA_RECEIVER_POWER_CAL_NEEDS_SOURCE_POWER_CAL ((HRESULT)0xA804045DL)

//
// MessageId: E_NA_STANDARD_MEASUREMENT_REQUIRED
//
// MessageText:
//
// The attempted operation can only be performed on a standard measurement type.
//
#define E_NA_STANDARD_MEASUREMENT_REQUIRED ((HRESULT)0xE804045EL)

//
// MessageId: E_NA_CUSTOM_LOAD_FAIL_INCOMPATIBLE_HARDWARE
//
// MessageText:
//
// The custom measurement cannot be loaded because it is not compatible with
// the Network Analyzer hardware.
//
#define E_NA_CUSTOM_LOAD_FAIL_INCOMPATIBLE_HARDWARE ((HRESULT)0xE804045FL)

//
// MessageId: E_NA_CUSTOM_LOAD_FAIL_INCOMPATIBLE_SOFTWARE
//
// MessageText:
//
// The custom measurement cannot be loaded because it is not compatible with
// the Network Analyzer software.
//
#define E_NA_CUSTOM_LOAD_FAIL_INCOMPATIBLE_SOFTWARE ((HRESULT)0xE8040460L)

//
// MessageId: E_NA_CUSTOM_LOAD_FAIL_GENERAL
//
// MessageText:
//
// The custom measurement load operation failed for an unspecified reason.
//
#define E_NA_CUSTOM_LOAD_FAIL_GENERAL    ((HRESULT)0xE8040461L)

//
// MessageId: E_NA_CUSTOM_UNHANDLED_EXCPETION
//
// MessageText:
//
// The custom measurement data processing has generated an unhandled exception, and will be 
// terminated.  The PNA software may be in an unstable state and it is recommended
// that the PNA software be shutdown and restarted.
//
#define E_NA_CUSTOM_UNHANDLED_EXCPETION  ((HRESULT)0xE8040462L)

//
// MessageId: E_NA_CUSTOM_MEASUREMENT_REQUIRED
//
// MessageText:
//
// The attempted operation can only be performed on a custom measurement type.
//
#define E_NA_CUSTOM_MEASUREMENT_REQUIRED ((HRESULT)0xE8040463L)

//
// MessageId: E_NA_NO_CUSTOM_MEASUREMENT
//
// MessageText:
//
// The requested custom measurement is not available.
//
#define E_NA_NO_CUSTOM_MEASUREMENT       ((HRESULT)0xE8040464L)

//
// MessageId: E_NA_CUSTOM_ALGORITHM_NOT_FOUND
//
// MessageText:
//
// The requested custom algorithm was not found.
//
#define E_NA_CUSTOM_ALGORITHM_NOT_FOUND  ((HRESULT)0xE8040465L)

//
// MessageId: E_NA_NO_DIVISOR_BUFFER
//
// MessageText:
//
// Normalization cannot be turned on because the measurement does not have 
// a valid divisor buffer.
//
#define E_NA_NO_DIVISOR_BUFFER           ((HRESULT)0xE8040466L)

//
// MessageId: E_NA_BAD_RAW_PARAMETER_REQUEST
//
// MessageText:
//
// The Raw Data requested by the measurement could not be provided. 
//
#define E_NA_BAD_RAW_PARAMETER_REQUEST   ((HRESULT)0xA8040467L)

//
// MessageId: E_NA_TRANSFORM_OR_GATING_DISABLED
//
// MessageText:
//
// The selected Sweep Type does not allow Transform and Gating.  
// Transform and Gating disabled. 
//
#define E_NA_TRANSFORM_OR_GATING_DISABLED ((HRESULT)0xE8040468L)

//
// MessageId: E_NA_MEMORY_NOT_APPLICABLE
//
// MessageText:
//
// Memory trace can not be applied to this measurement
//
#define E_NA_MEMORY_NOT_APPLICABLE       ((HRESULT)0xE8040469L)

//
// MessageId: E_NA_NORMALIZE_NOT_APPLICABLE
//
// MessageText:
//
// Normalization can not be applied to this measurement
//
#define E_NA_NORMALIZE_NOT_APPLICABLE    ((HRESULT)0xE804046AL)

//
// MessageId: E_NA_INVALID_NUMBER_OF_DATA_POINTS
//
// MessageText:
//
// The data provided has an invalid number of points. It could not be stored
//
#define E_NA_INVALID_NUMBER_OF_DATA_POINTS ((HRESULT)0xE804046BL)

//
// MessageId: E_NA_INVALID_MEASUREMENT_VERSION
//
// MessageText:
//
// The measurement stored in the save/recall state has an invalid version. It could not be loaded
//
#define E_NA_INVALID_MEASUREMENT_VERSION ((HRESULT)0xE804046CL)

//
// MessageId: E_NA_POLAR_FORMAT_REQUIRED
//
// MessageText:
//
// This data format argument for this operation must be "naDataFormat_Polar"
//
#define E_NA_POLAR_FORMAT_REQUIRED       ((HRESULT)0xE804046DL)

//
// MessageId: E_NA_SCALAR_FORMAT_REQUIRED
//
// MessageText:
//
// This data format argument for this operation must be a scalar data format
//
#define E_NA_SCALAR_FORMAT_REQUIRED      ((HRESULT)0xE804046EL)

//
// MessageId: E_NA_MEMORY_TRACE_NOT_VALID
//
// MessageText:
//
// The memory trace is not valid for the current measurement setup. 
//
#define E_NA_MEMORY_TRACE_NOT_VALID      ((HRESULT)0xE804046FL)

//
// MessageId: E_NA_THIS_MEASUREMENT_CANT_USE_THIS_CHANNEL
//
// MessageText:
//
// This measurement is incompatible with existing measurements in this channel. Choose another channel.
//
#define E_NA_THIS_MEASUREMENT_CANT_USE_THIS_CHANNEL ((HRESULT)0xE8040470L)

//
// MessageId: E_NA_PORT_EXTENSIONS_DONT_WORK_WITH_OFFSET
//
// MessageText:
//
// Port extension correction is not available for offset frequency measurements. 
// Port extension correction has been disabled.
//
#define E_NA_PORT_EXTENSIONS_DONT_WORK_WITH_OFFSET ((HRESULT)0xE8040471L)

//
// MessageId: E_NA_PHYSICAL_PORTS_MUST_BE_UNIQUE
//
// MessageText:
//
// Physical port number assignments for logical port mappings must be unique.
//
#define E_NA_PHYSICAL_PORTS_MUST_BE_UNIQUE ((HRESULT)0xE8040472L)

//
// MessageId: E_NA_TRACE_ALREADY_FED
//
// MessageText:
//
// Unable to feed the trace since the trace has already been fed to a window.
//
#define E_NA_TRACE_ALREADY_FED           ((HRESULT)0xE8040473L)

//
// MessageId: E_NA_TRACE_NOT_FED
//
// MessageText:
//
// Unable to delete the trace since it has not been fed to a window
//
#define E_NA_TRACE_NOT_FED               ((HRESULT)0xE8040474L)

//
// MessageId: E_NA_SNP_HAS_DUPLICATE_PORT_NUMBERS
//
// MessageText:
//
// Error: The given port numbers include duplicates
//
#define E_NA_SNP_HAS_DUPLICATE_PORT_NUMBERS ((HRESULT)0xE8040475L)

//
// MessageId: E_NA_SNP_OUT_OF_BOUNDS_PORT_NUMBERS
//
// MessageText:
//
// Error: At least one of the port numbers is out of bounds.
//
#define E_NA_SNP_OUT_OF_BOUNDS_PORT_NUMBERS ((HRESULT)0xE8040476L)

//
// MessageId: E_NA_COMPRESSION_POINT_NOT_FOUND
//
// MessageText:
//
// Error: The compression point value was not found.
//
#define E_NA_COMPRESSION_POINT_NOT_FOUND ((HRESULT)0xE8040477L)

//
// MessageId: E_NA_MARKER_PSAT_NOT_FOUND
//
// MessageText:
//
// Error: Power saturation back-off value was not found.
//
#define E_NA_MARKER_PSAT_NOT_FOUND       ((HRESULT)0xE8040478L)

//
// MessageId: E_NA_MARKER_NOP_NOT_FOUND
//
// MessageText:
//
// Error: Power normal operating point was not found.
//
#define E_NA_MARKER_NOP_NOT_FOUND        ((HRESULT)0xE8040479L)

//
// MessageId: E_NA_GDA_FIXED_VALUE_UNACHIEVABLE
//
// MessageText:
//
// Error: Group delay aperture value unachievable, smoothing aperture set to full span.
//
#define E_NA_GDA_FIXED_VALUE_UNACHIEVABLE ((HRESULT)0xE804047AL)

//
// MessageId: E_NA_MARKER_TYPE_NOT_FIXED
//
// MessageText:
//
// Error: Marker type not fixed, cannot change range value.
//
#define E_NA_MARKER_TYPE_NOT_FIXED       ((HRESULT)0xE804047BL)

//
// MessageId: E_NA_PHASE_CONTROL_PHASE_NOT_SETTLED
//
// MessageText:
//
// Phase leveling warning: phase not settled.
//
#define E_NA_PHASE_CONTROL_PHASE_NOT_SETTLED ((HRESULT)0xE804047CL)

//
// MessageId: E_NA_PHASE_CONTROL_POWER_NOT_SETTLED
//
// MessageText:
//
// Phase leveling warning: power not settled.
//
#define E_NA_PHASE_CONTROL_POWER_NOT_SETTLED ((HRESULT)0xE804047DL)

//
// MessageId: E_NA_PHASE_CONTROL_PHASE_AND_POWER_NOT_SETTLED
//
// MessageText:
//
// Phase leveling warning: phase and power not settled.
//
#define E_NA_PHASE_CONTROL_PHASE_AND_POWER_NOT_SETTLED ((HRESULT)0xE804047EL)

//
// MessageId: E_NA_PHASE_AND_RECEIVER_LEVELING_NOT_SETTLED
//
// MessageText:
//
// Leveling warning: phase and receiver leveling not settled.
//
#define E_NA_PHASE_AND_RECEIVER_LEVELING_NOT_SETTLED ((HRESULT)0xE804047FL)

//
// MessageId: E_NA_CHANNEL_DOES_NOT_SUPPORT_MARKER2SA
//
// MessageText:
//
// The selected channel does not support the Marker->SA operation.
//
#define E_NA_CHANNEL_DOES_NOT_SUPPORT_MARKER2SA ((HRESULT)0xE8040480L)

//
// MessageId: E_NA_MEASUREMENT_NOT_SUPPORTED_BY_MARKER2SA
//
// MessageText:
//
// The selected measurement is not supported by the Marker->SA operation.
//
#define E_NA_MEASUREMENT_NOT_SUPPORTED_BY_MARKER2SA ((HRESULT)0xE8040481L)

//
// MessageId: E_NA_MARKER2SA_OPERATION_FAILED
//
// MessageText:
//
// The Marker->SA operation failed.
//
#define E_NA_MARKER2SA_OPERATION_FAILED  ((HRESULT)0xE8040482L)

//
// MessageId: E_NA_GLACIER_LOST
//
// MessageText:
//
// Can not connect to the 89600 VSA application.
//
#define E_NA_GLACIER_LOST                ((HRESULT)0xE8040483L)

//
// MessageId: E_NA_MEAS_NOT_IN_CHANNEL
//
// MessageText:
//
// Measurement does not belong to specified channel.
//
#define E_NA_MEAS_NOT_IN_CHANNEL         ((HRESULT)0xE8040484L)

//
// MessageId: E_NA_BANDNOISE_MEAS_FAILED
//
// MessageText:
//
// The marker is not configured for Band Noise measurements.
//
#define E_NA_BANDNOISE_MEAS_FAILED       ((HRESULT)0xE8040485L)

//
// MessageId: E_NA_EXCEED_MAX_NUM_R_RECEIVERS
//
// MessageText:
//
// Exceeded limit on number of R Receivers.
//
#define E_NA_EXCEED_MAX_NUM_R_RECEIVERS  ((HRESULT)0xE8040486L)

//
// MessageId: E_NA_BANDPOWER_MEAS_FAILED
//
// MessageText:
//
// The marker is not configured for Band Power measurements.
//
#define E_NA_BANDPOWER_MEAS_FAILED       ((HRESULT)0xE8040487L)

//
// MessageId: E_NA_GC_COMPRESSION_ANALYSIS_UNAVAILABLE
//
// MessageText:
//
// Compression analysis not enabled due to invalid parameter(s).
//
#define E_NA_GC_COMPRESSION_ANALYSIS_UNAVAILABLE ((HRESULT)0xE8040488L)

//
// MessageId: E_NA_EXTERNAL_RECEIVER_NOT_SUPPORTED
//
// MessageText:
//
// External receiver configuration not available.
//
#define E_NA_EXTERNAL_RECEIVER_NOT_SUPPORTED ((HRESULT)0xE8040489L)

//
// MessageId: MSG_NOTHING_TO_SAY
//
// MessageText:
//
// You have sent a read command to the analyzer without first requesting
// data with an appropriate output command. The analyzer has no data in
// the output queue to satisfy the request.
//
#define MSG_NOTHING_TO_SAY               ((HRESULT)0x68050501L)

//
// MessageId: MSG_ANOTHER_CTRL
//
// MessageText:
//
// You must remove the active controller from the bus or the controller must
// relinquish the bus before the analyzer can assume the system controller mode.
//
#define MSG_ANOTHER_CTRL                 ((HRESULT)0xE8050502L)

//
// MessageId: MSG_BLOCK_INPUT_ERROR
//
// MessageText:
//
// The analyzer did not receive a complete data transmission.  This is usually
// caused by an interruption of the bus transaction.
//
#define MSG_BLOCK_INPUT_ERROR            ((HRESULT)0xE8050503L)

//
// MessageId: MSG_SCPI_STATUS_BYTE_CHANGE
//
// MessageText:
//
// The instrument status byte has changed.
//
#define MSG_SCPI_STATUS_BYTE_CHANGE      ((HRESULT)0x68050504L)

//
// MessageId: MSG_BAD_SCPI_COMMAND
//
// MessageText:
//
// The SCPI command received has caused error number %1: "%2".
//
#define MSG_BAD_SCPI_COMMAND             ((HRESULT)0x68050505L)

//
// MessageId: MSG_INET_LAN_SERVER_STARTED
//
// MessageText:
//
// The INET LAN server has been started as process number %1.
//
#define MSG_INET_LAN_SERVER_STARTED      ((HRESULT)0x68050506L)

//
// MessageId: MSG_PARSER_COMMAND_LOG
//
// MessageText:
//
// Parser got command: %1
//
#define MSG_PARSER_COMMAND_LOG           ((HRESULT)0x680505FFL)

//
// MessageId: E_NA_BAD_SCPI_EXECUTE
//
// MessageText:
//
// Execution of the SCPI command has failed
//
#define E_NA_BAD_SCPI_EXECUTE            ((HRESULT)0xE8050550L)

//
// MessageId: E_NA_INET_DEVICE_NOT_ACCESSIBLE
//
// MessageText:
//
// The INET/LAN device is not accessible.
//
#define E_NA_INET_DEVICE_NOT_ACCESSIBLE  ((HRESULT)0xE8050551L)

//
// MessageId: E_NA_INET_DRIVER_NOT_FOUND
//
// MessageText:
//
// The INET/LAN driver was not found. 
//
#define E_NA_INET_DRIVER_NOT_FOUND       ((HRESULT)0xE8050552L)

//
// MessageId: E_NA_INET_CHAN_ALREADY_ESTABLISHED
//
// MessageText:
//
// The INET/LAN channel is already in use.
//
#define E_NA_INET_CHAN_ALREADY_ESTABLISHED ((HRESULT)0xE8050553L)

//
// MessageId: E_NA_INET_OUT_OF_RESOURCES
//
// MessageText:
//
// The INET/LAN device is unable to acquire the necessary resources. 
//
#define E_NA_INET_OUT_OF_RESOURCES       ((HRESULT)0xE8050554L)

//
// MessageId: E_NA_INET_SYSTEM_ERROR
//
// MessageText:
//
// The INET/LAN device generated a generic system error.  
//
#define E_NA_INET_SYSTEM_ERROR           ((HRESULT)0xE8050555L)

//
// MessageId: E_NA_INET_INVALID_ADDRESS
//
// MessageText:
//
// Invalid address for the INET/LAN device.  
//
#define E_NA_INET_INVALID_ADDRESS        ((HRESULT)0xE8050556L)

//
// MessageId: E_NA_INET_IO_LIBRARY_NOT_FOUND
//
// MessageText:
//
// The INET I/O library was not found. 
//
#define E_NA_INET_IO_LIBRARY_NOT_FOUND   ((HRESULT)0xE8050557L)

//
// MessageId: E_NA_INET_GENERIC_ERROR
//
// MessageText:
//
// An error occured in the INET system. 
//
#define E_NA_INET_GENERIC_ERROR          ((HRESULT)0xE8050558L)

//
// MessageId: E_NA_INET_DRIVER_ACCESS_DENIED
//
// MessageText:
//
// Access to the INET/LAN driver was denied. 
//
#define E_NA_INET_DRIVER_ACCESS_DENIED   ((HRESULT)0xE8050559L)

//
// MessageId: E_NA_COULD_NOT_LOAD_ERROR_DLL
//
// MessageText:
//
// Could not load error system message dll.
//
#define E_NA_COULD_NOT_LOAD_ERROR_DLL    ((HRESULT)0xE805055AL)

//
// MessageId: E_NA_ERROR_DLL_DOES_NOT_EXPORT_RIGHT_FUNCTION
//
// MessageText:
//
// ErrorSystemMessage.dll does not export the right function
//
#define E_NA_ERROR_DLL_DOES_NOT_EXPORT_RIGHT_FUNCTION ((HRESULT)0xE805055BL)

//
// MessageId: E_NA_COULD_NOT_KNIT_CUSTOM_SCPI_LIB
//
// MessageText:
//
// Custom SCPI library was not able to be knitted
//
#define E_NA_COULD_NOT_KNIT_CUSTOM_SCPI_LIB ((HRESULT)0xE805055CL)

//
// MessageId: E_NA_COULD_NOT_KNIT_SCPI_ERROR_LIB
//
// MessageText:
//
// Could not knit the SCPI error messages from the ErrorSystemMessage lib
//
#define E_NA_COULD_NOT_KNIT_SCPI_ERROR_LIB ((HRESULT)0xE805055DL)

//
// MessageId: E_NA_SCPI_COMMAND_OBSOLETE
//
// MessageText:
//
// Command is obsolete with this software version. 
//
#define E_NA_SCPI_COMMAND_OBSOLETE       ((HRESULT)0xE805055EL)

//
// MessageId: E_NA_CALC_MEASUREMENT_SET_TO_NONE
//
// MessageText:
//
// CALC measurement selection set to none
//
#define E_NA_CALC_MEASUREMENT_SET_TO_NONE ((HRESULT)0xE805055FL)

//
// MessageId: E_NA_INET_DRIVER_COULD_NOT_TERMINATE_PROCESS
//
// MessageText:
//
// Access to the INET/LAN driver was denied. Could not terminate process: "%1"
//
#define E_NA_INET_DRIVER_COULD_NOT_TERMINATE_PROCESS ((HRESULT)0xE8050560L)

//
// MessageId: E_NA_USB_DRIVER_COULD_NOT_BE_STARTED
//
// MessageText:
//
// USB Device side support is unavailable because hardware driver is not loaded.
//
#define E_NA_USB_DRIVER_COULD_NOT_BE_STARTED ((HRESULT)0xE8050561L)

//
// MessageId: E_NA_COULD_NOT_OPEN_82350_CARD
//
// MessageText:
//
// Unable to connect to the AG82350 chip. GPIB control of instrument is disabled. Error code %1
//
#define E_NA_COULD_NOT_OPEN_82350_CARD   ((HRESULT)0xE8050891L)

//
// MessageId: E_NA_MEAS_REQUIRES_CALSET
//
// MessageText:
//
// Measurement requires a CalSet in order to access calibration data.
//
#define E_NA_MEAS_REQUIRES_CALSET        ((HRESULT)0xE8050892L)

//
// MessageId: E_NA_QUERY_GENERAL_ERROR
//
// MessageText:
//
// Query error.
//
#define E_NA_QUERY_GENERAL_ERROR         ((HRESULT)0xE8050893L)

//
// MessageId: E_NA_SYSTEM_ERROR
//
// MessageText:
//
// System error.
//
#define E_NA_SYSTEM_ERROR                ((HRESULT)0xE8050894L)

//
// MessageId: MSG_EXCEED_MAX_TRACES
//
// MessageText:
//
// Exceeded the maximum of %1 traces in each window.  The trace for
// %2 will not be added to window %3.
//
#define MSG_EXCEED_MAX_TRACES            ((HRESULT)0xA8060600L)

//
// MessageId: MSG_EXCEED_MAX_DATA_WINDOWS
//
// MessageText:
//
// Exceeded the maximum of %1 data windows.  New window will not
// be created.
//
#define MSG_EXCEED_MAX_DATA_WINDOWS      ((HRESULT)0xA8060601L)

//
// MessageId: MSG_NO_DATA_WINDOWS
//
// MessageText:
//
// No Data Windows are present.  Unable to compelte operation.
//
#define MSG_NO_DATA_WINDOWS              ((HRESULT)0xA8060602L)

//
// MessageId: MSG_NO_TRACE_FOUND
//
// MessageText:
//
// No data traces are present in the selected window.  
// Operation not completed.
//
#define MSG_NO_TRACE_FOUND               ((HRESULT)0xA8060603L)

//
// MessageId: MSG_ARRANGE_WINDOW_EXCEED_CAPACITY
//
// MessageText:
//
// Cannot complete request to arrange existing measurements in
// %1 windows due to the limit of %2 traces per window.  
//
#define MSG_ARRANGE_WINDOW_EXCEED_CAPACITY ((HRESULT)0x68060604L)

//
// MessageId: MSG_PRINT_SETUP_FAILURE
//
// MessageText:
//
// Unable to establish a connection with the specified printer.
//
#define MSG_PRINT_SETUP_FAILURE          ((HRESULT)0xA8060605L)

//
// MessageId: MSG_PRINT_CANCELED
//
// MessageText:
//
// Printout canceled.
//
#define MSG_PRINT_CANCELED               ((HRESULT)0x68060606L)

//
// MessageId: E_NA_NO_WINDOW
//
// MessageText:
//
// Window not found.
//
#define E_NA_NO_WINDOW                   ((HRESULT)0xE8060650L)

//
// MessageId: E_NA_DUPLICATE_WINDOW
//
// MessageText:
//
// Duplicate window ID specified.
//
#define E_NA_DUPLICATE_WINDOW            ((HRESULT)0xE8060651L)

//
// MessageId: E_NA_EXCEED_MAX_WINDOWS
//
// MessageText:
//
// Exceeded limit on number of windows.
//
#define E_NA_EXCEED_MAX_WINDOWS          ((HRESULT)0xE8060652L)

//
// MessageId: E_NA_EXCEED_MAX_NUM_TRACES
//
// MessageText:
//
// Exceeded limit on number of traces/window.
//
#define E_NA_EXCEED_MAX_NUM_TRACES       ((HRESULT)0xE8060653L)

//
// MessageId: E_NA_NO_TRACE
//
// MessageText:
//
// Trace not found.
//
#define E_NA_NO_TRACE                    ((HRESULT)0xE8060654L)

//
// MessageId: MSG_PRINT_DEVICECONTEXT_FAILURE
//
// MessageText:
//
// The operating system does not recognize this printer.
//
#define MSG_PRINT_DEVICECONTEXT_FAILURE  ((HRESULT)0xA8060655L)

//
// MessageId: E_NA_DUPLICATE_TRACE
//
// MessageText:
//
// Duplicate trace ID specified.
//
#define E_NA_DUPLICATE_TRACE             ((HRESULT)0xE8060656L)

//
// MessageId: E_NA_FAILED_WINDOW_CREATE
//
// MessageText:
//
// Window creation failed.
//
#define E_NA_FAILED_WINDOW_CREATE        ((HRESULT)0xE8060657L)

//
// MessageId: E_NA_TITLE_STRING_TOO_LONG
//
// MessageText:
//
// Title string exceeds 50 characters.
//
#define E_NA_TITLE_STRING_TOO_LONG       ((HRESULT)0xE8060658L)

//
// MessageId: E_NA_DUPLICATE_MEASUREMENT_NAME
//
// MessageText:
//
// Duplicate measurement name.
//
#define E_NA_DUPLICATE_MEASUREMENT_NAME  ((HRESULT)0xE8040659L)

//
// MessageId: E_NA_NO_MARKER
//
// MessageText:
//
// Marker not found.
//
#define E_NA_NO_MARKER                   ((HRESULT)0xE8060660L)

//
// MessageId: MSG_CHANNEL_SWEEP_COMPLETE
//
// MessageText:
//
// Sweep Complete.
//
#define MSG_CHANNEL_SWEEP_COMPLETE       ((HRESULT)0x68070700L)

//
// MessageId: MSG_CHANNEL_TRIGGER_COMPLETE
//
// MessageText:
//
// All triggerable acqusitions have completed.
//
#define MSG_CHANNEL_TRIGGER_COMPLETE     ((HRESULT)0x68070701L)

//
// MessageId: MSG_CHANNEL_TRIGGER_ABORTED
//
// MessageText:
//
// The last trigger produced an aborted sweep.
//
#define MSG_CHANNEL_TRIGGER_ABORTED      ((HRESULT)0x68070702L)

//
// MessageId: MSG_SWEEP_SEGMENT_LIST_NO_ACTIVE_POINTS_
//
// MessageText:
//
// The segment list must be adjusted to have at least one active segment with more
// than 0 points to use segment sweep.
//
#define MSG_SWEEP_SEGMENT_LIST_NO_ACTIVE_POINTS_ ((HRESULT)0x68070703L)

//
// MessageId: MSG_SET_CHANNEL_DIRTY
//
// MessageText:
//
//  MSG_SET_CHANNEL_DIRTY
//
#define MSG_SET_CHANNEL_DIRTY            ((HRESULT)0x68070704L)

//
// MessageId: MSG_CLEAR_CHANNEL_DIRTY
//
// MessageText:
//
//  MSG_CLEAR_CHANNEL_DIRTY
//
#define MSG_CLEAR_CHANNEL_DIRTY          ((HRESULT)0x68070705L)

//
// MessageId: MSG_SWEEP_TIME_TO_MANUAL_MODE
//
// MessageText:
//
// Sweep time has changed from Auto to Manual mode.  If desired to return to Auto mode,
// enter sweep time value of 0.
//
#define MSG_SWEEP_TIME_TO_MANUAL_MODE    ((HRESULT)0x68070706L)

//
// MessageId: MSG_SET_SWEEP_COMPLETED
//
// MessageText:
//
// Sweep Completed bit is set.
//
#define MSG_SET_SWEEP_COMPLETED          ((HRESULT)0x68070707L)

//
// MessageId: MSG_CLR_SWEEP_COMPLETED
//
// MessageText:
//
// Sweep Completed bit is clear.
//
#define MSG_CLR_SWEEP_COMPLETED          ((HRESULT)0x68070708L)

//
// MessageId: MSG_ALL_SWEEPS_COMPLETED_AND_PROCESSED
//
// MessageText:
//
// All sweeps on this channel have been completed, and their data has been processed
//
#define MSG_ALL_SWEEPS_COMPLETED_AND_PROCESSED ((HRESULT)0x68070709L)

//
// MessageId: MSG_LOW_PASS_FREQ_CHANGED
//
// MessageText:
//
// Low Pass : Frequency limits have been changed.
//
#define MSG_LOW_PASS_FREQ_CHANGED        ((HRESULT)0x6807070AL)

//
// MessageId: MSG_LOW_PASS_POINTS_CHANGED
//
// MessageText:
//
// Low Pass : Number of points have been changed.
//
#define MSG_LOW_PASS_POINTS_CHANGED      ((HRESULT)0x6807070BL)

//
// MessageId: MSG_LOW_PASS_FREQ_POINTS_CHANGED
//
// MessageText:
//
// Low Pass : Frequency limits and number of points have been changed.
//
#define MSG_LOW_PASS_FREQ_POINTS_CHANGED ((HRESULT)0x6807070CL)

//
// MessageId: MSG_CHANNEL_CREATED
//
// MessageText:
//
// Channel was created.
//
#define MSG_CHANNEL_CREATED              ((HRESULT)0x6807070DL)

//
// MessageId: MSG_CHANNEL_DELETED
//
// MessageText:
//
// Channel was deleted.
//
#define MSG_CHANNEL_DELETED              ((HRESULT)0x6807070EL)

//
// MessageId: E_NA_NO_CHANNEL
//
// MessageText:
//
// Channel not found.
//
#define E_NA_NO_CHANNEL                  ((HRESULT)0xE8070750L)

//
// MessageId: E_NA_SWEEP_SEGMENT_NOT_FOUND
//
// MessageText:
//
// The requested sweep segment was not found.
//
#define E_NA_SWEEP_SEGMENT_NOT_FOUND     ((HRESULT)0xE8070751L)

//
// MessageId: E_NA_SWEEP_SEGMENT_LIST_EMPTY
//
// MessageText:
//
// The sweep segment list is empty.
//
#define E_NA_SWEEP_SEGMENT_LIST_EMPTY    ((HRESULT)0xE8070752L)

//
// MessageId: E_NA_SWEEP_SEGMENT_LIST_NO_ACTIVE_POINTS
//
// MessageText:
//
// The number of points in active sweep segment list segments is 0.
//
#define E_NA_SWEEP_SEGMENT_LIST_NO_ACTIVE_POINTS ((HRESULT)0xE8070753L)

//
// MessageId: E_NA_NO_SOURCE_ATTEN
//
// MessageText:
//
// The specified source attenuator is not valid.
//
#define E_NA_NO_SOURCE_ATTEN             ((HRESULT)0xE8070754L)

//
// MessageId: E_NA_TOO_MANY_POINTS_FOR_LOG_SWEEP
//
// MessageText:
//
// Log Frequency sweep cannot be selected with the current Number of Points.
// Please reduce Number of Points.
//
#define E_NA_TOO_MANY_POINTS_FOR_LOG_SWEEP ((HRESULT)0xE8070755L)

//
// MessageId: E_NA_EXCEEDED_MAX_POINTS_FOR_LOG_SWEEP
//
// MessageText:
//
// The requested Number of Points is greater than can be selected for Log Frequency sweep.
//
#define E_NA_EXCEEDED_MAX_POINTS_FOR_LOG_SWEEP ((HRESULT)0xE8070756L)

//
// MessageId: E_NA_FREQ_OFFSET_OVERRANGE_SO_TURNED_OFF
//
// MessageText:
//
// Response frequencies exceeded instrument range.
//
#define E_NA_FREQ_OFFSET_OVERRANGE_SO_TURNED_OFF ((HRESULT)0xE8070757L)

//
// MessageId: E_NA_TOO_MANY_POINTS_IN_SET_ALL_SEGMENTS
//
// MessageText:
//
// The total number of points for all the given segments exceeds the maximum number
// of points supported. The segments were not changed.
//
#define E_NA_TOO_MANY_POINTS_IN_SET_ALL_SEGMENTS ((HRESULT)0xE8070758L)

//
// MessageId: E_NA_CHANNELS_NOT_HOLD
//
// MessageText:
//
// This instance of the Channels object was not used to place the channels in Hold, so no
// channels were resumed.
//
#define E_NA_CHANNELS_NOT_HOLD           ((HRESULT)0xE8070759L)

//
// MessageId: E_NA_PORT_NUMBER_OUT_OF_RANGE
//
// MessageText:
//
// The port number was outside the range of allowed port numbers.
//
#define E_NA_PORT_NUMBER_OUT_OF_RANGE    ((HRESULT)0xE807075AL)

//
// MessageId: E_NA_INSUFFICIENT_PORTS
//
// MessageText:
//
// More ports than are present are required for this operation.
//
#define E_NA_INSUFFICIENT_PORTS          ((HRESULT)0xE807075BL)

//
// MessageId: E_NA_OPERATION_NOT_VALID_FOR_SWEEP_TYPE
//
// MessageText:
//
// The requested operation is not valid for the current sweep type.
//
#define E_NA_OPERATION_NOT_VALID_FOR_SWEEP_TYPE ((HRESULT)0xE807075CL)

//
// MessageId: E_NA_FREQ_OFFSET_SOURCE_OVERRANGE_SO_TURNED_OFF
//
// MessageText:
//
// Error: Source frequencies exceeded instrument range.
//
#define E_NA_FREQ_OFFSET_SOURCE_OVERRANGE_SO_TURNED_OFF ((HRESULT)0xE807075DL)

//
// MessageId: E_NA_FREQ_OFFSET_SOURCE2_OVERRANGE_SO_TURNED_OFF
//
// MessageText:
//
// Error Source 2 frequencies exceeded instrument range.
//
#define E_NA_FREQ_OFFSET_SOURCE2_OVERRANGE_SO_TURNED_OFF ((HRESULT)0xE807075EL)

//
// MessageId: E_NA_FREQ_OFFSET_SOURCE_IS_COUPLED
//
// MessageText:
//
// This property can not be set. The source FOM range must be uncoupled when setting this property.
//
#define E_NA_FREQ_OFFSET_SOURCE_IS_COUPLED ((HRESULT)0xE807075FL)

//
// MessageId: E_NA_NOT_ENOUGH_UNUSED_CHANNELS
//
// MessageText:
//
// There were not enough unused channels to satisfy the request.
//
#define E_NA_NOT_ENOUGH_UNUSED_CHANNELS  ((HRESULT)0xE8070760L)

//
// MessageId: E_NA_FREQ_OFFSET_SOURCE2_IS_COUPLED
//
// MessageText:
//
// This property can not be set. The source 2 FOM range must be uncoupled when setting this property.
//
#define E_NA_FREQ_OFFSET_SOURCE2_IS_COUPLED ((HRESULT)0xE8070761L)

//
// MessageId: E_NA_FREQ_OFFSET_RECEIVER_IS_COUPLED
//
// MessageText:
//
// This property can not be set. The receiver FOM range must be uncoupled when setting this property.
//
#define E_NA_FREQ_OFFSET_RECEIVER_IS_COUPLED ((HRESULT)0xE8070762L)

//
// MessageId: E_NA_FREQ_OFFSET_SOURCE_IS_UNCOUPLED
//
// MessageText:
//
// This property can not be set. The source FOM range must be coupled when setting this property.
//
#define E_NA_FREQ_OFFSET_SOURCE_IS_UNCOUPLED ((HRESULT)0xE8070763L)

//
// MessageId: E_NA_FREQ_OFFSET_SOURCE2_IS_UNCOUPLED
//
// MessageText:
//
// This property can not be set. The source 2 FOM range must be coupled when setting this property.
//
#define E_NA_FREQ_OFFSET_SOURCE2_IS_UNCOUPLED ((HRESULT)0xE8070764L)

//
// MessageId: E_NA_FREQ_OFFSET_RECEIVER_IS_UNCOUPLED
//
// MessageText:
//
// This property can not be set. The receiver FOM range must be coupled when setting this property.
//
#define E_NA_FREQ_OFFSET_RECEIVER_IS_UNCOUPLED ((HRESULT)0xE8070765L)

//
// MessageId: E_NA_FREQ_OFFSET_SOURCE_SEGMENTS_POINTS_DONT_MATCH_UP
//
// MessageText:
//
// The number of points of the source segment table must be the same as the number of points in the channel.
//  The channel has %1 points. The source segment table has %2 points.
//
#define E_NA_FREQ_OFFSET_SOURCE_SEGMENTS_POINTS_DONT_MATCH_UP ((HRESULT)0xE8070766L)

//
// MessageId: E_NA_FREQ_OFFSET_RESPONSE_SEGMENTS_POINTS_DONT_MATCH_UP
//
// MessageText:
//
// The number of points of the response segment table must be the same as the number of points in the channel.
//  The channel has %1 points. The source segment table has %2 points.
//
#define E_NA_FREQ_OFFSET_RESPONSE_SEGMENTS_POINTS_DONT_MATCH_UP ((HRESULT)0xE8070767L)

//
// MessageId: E_NA_ALC_MODE_NOT_SUPPORTED
//
// MessageText:
//
// The hardware does not support the ALC mode specified.
//
#define E_NA_ALC_MODE_NOT_SUPPORTED      ((HRESULT)0xE8070768L)

//
// MessageId: E_NA_ALC_SCPI_COMMAND_NOT_SUPPORTED
//
// MessageText:
//
// This command is not supported anymore.  Please use SOUR[chan]:POW[port]:ALC:MODE to control the ALC mode per port.
//
#define E_NA_ALC_SCPI_COMMAND_NOT_SUPPORTED ((HRESULT)0xE8070769L)

//
// MessageId: E_NA_ALC_COM_COMMAND_NOT_SUPPORTED
//
// MessageText:
//
// This command is not supported anymore.  Please use the property ALCLevelingMode on the IChannel interface to control the ALC mode per port.
//
#define E_NA_ALC_COM_COMMAND_NOT_SUPPORTED ((HRESULT)0xE807076AL)

//
// MessageId: MSG_NA_SETTING_PORT_TO_OFF
//
// MessageText:
//
// Port %1 was set to "OFF" to allow port %2 to be set to "ON"
//
#define MSG_NA_SETTING_PORT_TO_OFF       ((HRESULT)0x6807076BL)

//
// MessageId: E_NA_NO_SECOND_SOURCE_CANT_TURN_ON
//
// MessageText:
//
// ERROR: The only valid choice for a single source Network Analyzer is "AUTO".
//
#define E_NA_NO_SECOND_SOURCE_CANT_TURN_ON ((HRESULT)0xE807076CL)

//
// MessageId: E_NA_INVALID_SOURCE_PORT_NAME
//
// MessageText:
//
// ERROR: Invalid source port name.
//
#define E_NA_INVALID_SOURCE_PORT_NAME    ((HRESULT)0xE807076DL)

//
// MessageId: E_NA_INVALID_PATH_ELEMENT
//
// MessageText:
//
// Path element is not valid.
//
#define E_NA_INVALID_PATH_ELEMENT        ((HRESULT)0xE807076EL)

//
// MessageId: E_NA_INVALID_PATH_CONFIGURATION
//
// MessageText:
//
// Path configuration is not valid.
//
#define E_NA_INVALID_PATH_CONFIGURATION  ((HRESULT)0xE807076FL)

//
// MessageId: E_NA_CANNOT_DELETE_FACTORY_PATH_CONFIGURATION
//
// MessageText:
//
// Cannot delete factory path configuration.
//
#define E_NA_CANNOT_DELETE_FACTORY_PATH_CONFIGURATION ((HRESULT)0xE8070770L)

//
// MessageId: E_NA_CANT_MEASURE_BOTH_REFERENCE_RECEIVERS_ON
//
// MessageText:
//
// ERROR: It is not possible to measure the reference signal on both of these ports in the same sweep.
// Create two parameters, each referencing only one of these reference signals.
//
#define E_NA_CANT_MEASURE_BOTH_REFERENCE_RECEIVERS_ON ((HRESULT)0xE8070771L)

//
// MessageId: MSG_NA_GENERIC_GUI_HINT
//
// MessageText:
//
// %1
//
#define MSG_NA_GENERIC_GUI_HINT          ((HRESULT)0x68070772L)

//
// MessageId: E_NA_UNSUPPORTED_FOM_LOG_SWEEP_COMBINATION
//
// MessageText:
//
// Error: Coupled log sweeps with non-zero offsets are not allowed.
//
#define E_NA_UNSUPPORTED_FOM_LOG_SWEEP_COMBINATION ((HRESULT)0xE8070773L)

//
// MessageId: E_NA_UNSUPPORTED_FOM_POWER_AND_SEGMENT
//
// MessageText:
//
// Error: Combining segment sweep and power sweep is not supported.
//
#define E_NA_UNSUPPORTED_FOM_POWER_AND_SEGMENT ((HRESULT)0xE8070774L)

//
// MessageId: E_NA_NO_POINTS_IN_SET_ALL_SEGMENTS
//
// MessageText:
//
// The total number of points for all the given segments needs to be greater than 0. The segments have not changed.
//
#define E_NA_NO_POINTS_IN_SET_ALL_SEGMENTS ((HRESULT)0xE8070775L)

//
// MessageId: MSG_NA_SETTING_TO_OFF
//
// MessageText:
//
// %1 was set to "OFF" to allow %2 to be set to "ON"
//
#define MSG_NA_SETTING_TO_OFF            ((HRESULT)0x68070776L)

//
// MessageId: E_NA_CANT_COPY_APPLICATION_CHANNEL
//
// MessageText:
//
// Error: The source channel contains measurements that do not support copying.
//
#define E_NA_CANT_COPY_APPLICATION_CHANNEL ((HRESULT)0xE8070777L)

//
// MessageId: MSG_NA_POWER_ON_NEXT_SWEEP
//
// MessageText:
//
// Channel is in hold mode.  On the next sweep RF power will turn on.
//
#define MSG_NA_POWER_ON_NEXT_SWEEP       ((HRESULT)0x68070778L)

//
// MessageId: E_NA_FREQ_OFFSET_EXTERNAL_OVERRANGE
//
// MessageText:
//
// The specified external source frequencies for %1 exceeded the sources range.
//
#define E_NA_FREQ_OFFSET_EXTERNAL_OVERRANGE ((HRESULT)0xE8070779L)

//
// MessageId: E_NA_FREQ_RANGE_DOESNT_OVERLAP_WITH_RECEIVERS
//
// MessageText:
//
// Can not calibrate the source to the internal receivers, because the source frequency range exceeds the receiver range.
//
#define E_NA_FREQ_RANGE_DOESNT_OVERLAP_WITH_RECEIVERS ((HRESULT)0xE807077AL)

//
// MessageId: E_NA_POW_OFFSET_EXTERNAL_OVERRANGE
//
// MessageText:
//
// The specified external source power for %1 exceeded the sources range.
//
#define E_NA_POW_OFFSET_EXTERNAL_OVERRANGE ((HRESULT)0xE807077BL)

//
// MessageId: E_EQ_EDITOR_PROTOTYPE_INCORRECT
//
// MessageText:
//
// '%1' prototype(s) malformed and not loaded, contact DLL provider.
//
#define E_EQ_EDITOR_PROTOTYPE_INCORRECT  ((HRESULT)0xE807077CL)

//
// MessageId: E_EQ_EDITOR_PROTOTYPE_METHOD_NOT_FOUND
//
// MessageText:
//
// 'listOfFunctions()' method not found. DLL not loaded, contact DLL provider.
//
#define E_EQ_EDITOR_PROTOTYPE_METHOD_NOT_FOUND ((HRESULT)0xE807077DL)

//
// MessageId: E_EQ_EDITOR_PROTOTYPE_NOT_FOUND
//
// MessageText:
//
// '%1' method(s) not found. Contact DLL provider.
//
#define E_EQ_EDITOR_PROTOTYPE_NOT_FOUND  ((HRESULT)0xE807077EL)

//
// MessageId: E_EQ_EDITOR_METHOD_ERROR
//
// MessageText:
//
// '%1' method exception, contact DLL provider.
//
#define E_EQ_EDITOR_METHOD_ERROR         ((HRESULT)0xE807077FL)

//
// MessageId: E_EQ_EDITOR_LIBRARY_NOT_FOUND
//
// MessageText:
//
// '%1' library not loaded.
//
#define E_EQ_EDITOR_LIBRARY_NOT_FOUND    ((HRESULT)0xE8070780L)

//
// MessageId: E_NA_IF_PATH_ALL_NOT_SAME
//
// MessageText:
//
// IF Path Selection is not the same for all receivers.
//
#define E_NA_IF_PATH_ALL_NOT_SAME        ((HRESULT)0xE8070781L)

//
// MessageId: E_NA_MEAS_SPEC_GENERATION_ERROR
//
// MessageText:
//
// An internal error (Meas-Spec Generation) has been generated, save the instrument state and contact a customer representative.
//
#define E_NA_MEAS_SPEC_GENERATION_ERROR  ((HRESULT)0xE8070782L)

//
// MessageId: E_NA_ACQUISITION_CONSTRUCTION_ERROR
//
// MessageText:
//
// An internal error (Acquisition Construction) has been generated, save the instrument state and contact a customer representative.
//
#define E_NA_ACQUISITION_CONSTRUCTION_ERROR ((HRESULT)0xE8070783L)

//
// MessageId: E_NA_ACQUISITION_EXECUTION_ERROR
//
// MessageText:
//
// An internal error (Acquisition Execution) has been generated, save the instrument state and contact a customer representative.
//
#define E_NA_ACQUISITION_EXECUTION_ERROR ((HRESULT)0xE8070784L)

//
// MessageId: E_NA_ACQUISITION_LOGICAL_DEVICE_ERROR
//
// MessageText:
//
// An acquisition error due to a logical device has been generated, save the instrument state and contact a customer representative.
//
#define E_NA_ACQUISITION_LOGICAL_DEVICE_ERROR ((HRESULT)0xE8070785L)

//
// MessageId: E_NA_ACQUISITION_OTHER_ERROR
//
// MessageText:
//
// An unspecified acquisition error has been generated, save the instrument state and contact a customer representative.
//
#define E_NA_ACQUISITION_OTHER_ERROR     ((HRESULT)0xE8070786L)

//
// MessageId: E_NA_CHANNELS_ARE_WEAR_ITEM_INCOMPATIBLE
//
// MessageText:
//
// The specified PNA channels cannot simultaneously be in continuous sweep with internal trigger. They have different attenuator settings or hardware path configurations.
//
#define E_NA_CHANNELS_ARE_WEAR_ITEM_INCOMPATIBLE ((HRESULT)0xE8070787L)

//
// MessageId: MSG_NUM_POWER_POINTS_REDUCED
//
// MessageText:
//
// The number of power points have been reduced.
//
#define MSG_NUM_POWER_POINTS_REDUCED     ((HRESULT)0xA8070789L)

//
// MessageId: E_EQ_EDITOR_LIBRARY_NOT_LOADED
//
// MessageText:
//
// '%1' library not loaded.
//
#define E_EQ_EDITOR_LIBRARY_NOT_LOADED   ((HRESULT)0xE807078AL)

//
// MessageId: E_NA_CANT_MEASURE_REFERENCE_RECEIVERS_ATTRUEMODE_ON
//
// MessageText:
//
// ERROR: It is not possible to measure the single ended reference signal in the True Stimulus Mode.
//
#define E_NA_CANT_MEASURE_REFERENCE_RECEIVERS_ATTRUEMODE_ON ((HRESULT)0xE807078BL)

//
// MessageId: E_IF_CAL_FILE_MISSING
//
// MessageText:
//
// IF cal file (imscal.txt) is missing.  Please wait for file to be created.
//
#define E_IF_CAL_FILE_MISSING            ((HRESULT)0xE807078CL)

//
// MessageId: E_CANNOT_ENABLE_TRACE_TRIGGER_INCORRECT_SETUP
//
// MessageText:
//
// Trace trigger requires point sweep mode, no internal triggers and must be in channel scope.
//
#define E_CANNOT_ENABLE_TRACE_TRIGGER_INCORRECT_SETUP ((HRESULT)0xE807078DL)

//
// MessageId: E_NA_ROLE_IS_IMMUTABLE
//
// MessageText:
//
// The specified role cannot be modified.
//
#define E_NA_ROLE_IS_IMMUTABLE           ((HRESULT)0xE807078EL)

//
// MessageId: E_NA_ROLE_IS_NOT_DEFINED
//
// MessageText:
//
// The specified role is not defined.
//
#define E_NA_ROLE_IS_NOT_DEFINED         ((HRESULT)0xE807078FL)

//
// MessageId: E_NA_EXTERNAL_AND_INTERNAL_SOURCE_ON_IN_TRACE_TRIGGER
//
// MessageText:
//
// Use of external sources and internal sources while in trace triggering is not supported. Channel is in hold mode.
//
#define E_NA_EXTERNAL_AND_INTERNAL_SOURCE_ON_IN_TRACE_TRIGGER ((HRESULT)0xE8070790L)

//
// MessageId: E_NA_PORT_POWER_UNCOUPLED
//
// MessageText:
//
// Port offset may not be applied while port powers are coupled. Port powers are uncoupled.
//
#define E_NA_PORT_POWER_UNCOUPLED        ((HRESULT)0xE807079AL)

//
// MessageId: E_CHANNEL_BLOCKED
//
// MessageText:
//
// Channel blocked from sweeping due to mechanical device setting conflict.
//
#define E_CHANNEL_BLOCKED                ((HRESULT)0xE807079BL)

//
// MessageId: E_CHANNEL_BLOCKED_BY_CAL
//
// MessageText:
//
// Channel blocked from sweeping due to calibration in progress.
//
#define E_CHANNEL_BLOCKED_BY_CAL         ((HRESULT)0xE807079CL)

//
// MessageId: E_NA_PHASE_CONTROL_NO_AUTO_ATTENUATION
//
// MessageText:
//
// Auto attenuation is disabled on phase controlled ports.
//
#define E_NA_PHASE_CONTROL_NO_AUTO_ATTENUATION ((HRESULT)0xE807079DL)

//
// MessageId: E_NA_ATTEMPT_TO_COPY_INCOMPATIBLE_CHANNELS
//
// MessageText:
//
// The copy channel operation failed because the target channel exists and is incompatible with the source channel.
//
#define E_NA_ATTEMPT_TO_COPY_INCOMPATIBLE_CHANNELS ((HRESULT)0xE807079EL)

//
// MessageId: E_NA_INCOMPLETE_SWEEP_TEMP
//
// MessageText:
//
// You must first take a sweep before measuring the receiver temperature.
//
#define E_NA_INCOMPLETE_SWEEP_TEMP       ((HRESULT)0xE807079FL)

//
// MessageId: E_NA_FREQ_RANGE_NOT_FOUND
//
// MessageText:
//
// The requested frequency range does not exist.
//
#define E_NA_FREQ_RANGE_NOT_FOUND        ((HRESULT)0xE80707A0L)

//
// MessageId: E_NA_INVALID_RECEIVER_NAME
//
// MessageText:
//
// Invalid receiver name.
//
#define E_NA_INVALID_RECEIVER_NAME       ((HRESULT)0xE80707A1L)

//
// MessageId: MSG_OPCABLE_SWEEP_COMPLETE
//
// MessageText:
//
// Overlapped sweep operation completed.
//
#define MSG_OPCABLE_SWEEP_COMPLETE       ((HRESULT)0x680707A2L)

//
// MessageId: E_NA_FREQ_RANGE1_DELETE_NOT_ALLOWED
//
// MessageText:
//
// Deleting Frequency Range 1 is not allowed.
//
#define E_NA_FREQ_RANGE1_DELETE_NOT_ALLOWED ((HRESULT)0xE80707A3L)

//
// MessageId: MSG_OVERLAPPED_STARTED
//
// MessageText:
//
// Channel arm overlapped operation started
//
#define MSG_OVERLAPPED_STARTED           ((HRESULT)0x680707A4L)

//
// MessageId: MSG_OVERLAPPED_NOT_STARTED
//
// MessageText:
//
// Channel arm overlapped operation not started
//
#define MSG_OVERLAPPED_NOT_STARTED       ((HRESULT)0x680707A5L)

//
// MessageId: E_NA_NO_FREE_CHANNEL_ERROR
//
// MessageText:
//
// There are no free channels remaining. Delete a channel and try again.
//
#define E_NA_NO_FREE_CHANNEL_ERROR       ((HRESULT)0xE80707A6L)

//
// MessageId: E_NA_PRIMARY_DOMAIN_RANGE_CANNOT_BE_COUPLED
//
// MessageText:
//
// Cannot couple primary domain range.
//
#define E_NA_PRIMARY_DOMAIN_RANGE_CANNOT_BE_COUPLED ((HRESULT)0xE80707A7L)

//
// MessageId: E_NA_ILLEGAL_PARAMETER
//
// MessageText:
//
// Illegal parameter(s) in the command. 
//
#define E_NA_ILLEGAL_PARAMETER           ((HRESULT)0xE80707B1L)

//
// MessageId: E_NA_DUPLICATE_DESCRIPTOR
//
// MessageText:
//
// The key of the descriptor has been used. 
//
#define E_NA_DUPLICATE_DESCRIPTOR        ((HRESULT)0xE80707B2L)

//
// MessageId: E_NA_DESCRIPTOR_NOT_EXIST
//
// MessageText:
//
// The descriptor does not exist. 
//
#define E_NA_DESCRIPTOR_NOT_EXIST        ((HRESULT)0xE80707B3L)

//
// MessageId: E_NA_NO_VALID_RESULT
//
// MessageText:
//
// No valid result(s) returned. Please check the settings of both the VSA 89600 Software and the VNA. 
//
#define E_NA_NO_VALID_RESULT             ((HRESULT)0xE80707B4L)

//
// MessageId: E_NA_INVALID_SWEEP_NUMBER
//
// MessageText:
//
// Invalid sweep number. 
//
#define E_NA_INVALID_SWEEP_NUMBER        ((HRESULT)0xE80707B5L)

//
// MessageId: E_NA_INSUFFICIENT_PORT_LIST
//
// MessageText:
//
// The port list is insufficent.
//
#define E_NA_INSUFFICIENT_PORT_LIST      ((HRESULT)0xE80707B6L)

//
// MessageId: MSG_VSA_CONNECT_COMPLETE
//
// MessageText:
//
// Connection to the VSA 89600 software completed.
//
#define MSG_VSA_CONNECT_COMPLETE         ((HRESULT)0x680707B7L)

//
// MessageId: E_NA_ATTEMPT_TO_COPY_COUPLED_CHANNELS
//
// MessageText:
//
// The copy channel operation failed because channel coupling is on.
//
#define E_NA_ATTEMPT_TO_COPY_COUPLED_CHANNELS ((HRESULT)0xE80707B8L)

//
// MessageId: E_NA_PLATFORM_DOES_NOT_SUPPORT_FULL_VB
//
// MessageText:
//
// The PNA platform does not support ON mode for virtual bridge. The only supported modes are AUTO and OFF.
//
#define E_NA_PLATFORM_DOES_NOT_SUPPORT_FULL_VB ((HRESULT)0xE80707B9L)

//
// MessageId: E_NA_CHANNEL_DOES_NOT_SUPPORT_LFE
//
// MessageText:
//
// LFE is not supported by the selected channel
//
#define E_NA_CHANNEL_DOES_NOT_SUPPORT_LFE ((HRESULT)0xE80707BAL)

//
// MessageId: MSG_OPTION_NOT_INSTALLED
//
// MessageText:
//
// The function you requested requires a capability provided by an option
// to the standard analyzer. That option is not currently installed.
//
#define MSG_OPTION_NOT_INSTALLED         ((HRESULT)0x68080800L)

//
// MessageId: MSG_FEATURE_NOT_AVAILABLE
//
// MessageText:
//
// The feature you requested is not available on the current instrument.
//
#define MSG_FEATURE_NOT_AVAILABLE        ((HRESULT)0x68080801L)

//
// MessageId: MSG_FEATURE_NOT_VALID
//
// MessageText:
//
// The feature you requested is incompatible with the current instrument state.
//
#define MSG_FEATURE_NOT_VALID            ((HRESULT)0x68080802L)

//
// MessageId: MSG_SAVEFILE_OK
//
// MessageText:
//
// %1 has been saved.
//
#define MSG_SAVEFILE_OK                  ((HRESULT)0x68080803L)

//
// MessageId: MSG_SAVEFILE_FAIL
//
// MessageText:
//
// Attempt to save %1 failed.
//
#define MSG_SAVEFILE_FAIL                ((HRESULT)0xE8080804L)

//
// MessageId: MSG_RECALLFILE_FILE_NOT_FOUND
//
// MessageText:
//
// Attempt to recall file failed because %1 was not found.
//
#define MSG_RECALLFILE_FILE_NOT_FOUND    ((HRESULT)0xE8080805L)

//
// MessageId: MSG_RECALLFILE_BAD_HEADER
//
// MessageText:
//
// File %1 cannot be loaded. The contents are not recognized.
//
#define MSG_RECALLFILE_BAD_HEADER        ((HRESULT)0xE8080806L)

//
// MessageId: MSG_POWER_HIBERNATE
//
// MessageText:
//
// Request to enter hibernate state.  
//
#define MSG_POWER_HIBERNATE              ((HRESULT)0x68080808L)

//
// MessageId: MSG_POWER_HIBERNATE_AUTOMATIC
//
// MessageText:
//
// Power up from automatic hibernate state.
// (Program received PBT_APMRESUMEAUTOMATIC message.) 
//
#define MSG_POWER_HIBERNATE_AUTOMATIC    ((HRESULT)0x68080809L)

//
// MessageId: MSG_POWER_HIBERNATE_SUSPEND
//
// MessageText:
//
// Power up from suspend hibernate state.
// (Program received PBT_APMRESUMESUSPEND message.) 
//
#define MSG_POWER_HIBERNATE_SUSPEND      ((HRESULT)0x6808080AL)

//
// MessageId: MSG_POWER_HIBERNATE_CRITICAL
//
// MessageText:
//
// Power up from suspend hibernate state.
// (Program received PBT_APMRESUMECRITICAL message.) 
//
#define MSG_POWER_HIBERNATE_CRITICAL     ((HRESULT)0xA808080BL)

//
// MessageId: MSG_POWER_HIBERNATE_UIFAILSAFE
//
// MessageText:
//
// Power up from unknown hibernate state UI recovery called. 
// (Program received no PBT_ message within the time alloted and
// is attempting recovery.) 
//
#define MSG_POWER_HIBERNATE_UIFAILSAFE   ((HRESULT)0xA808080CL)

//
// MessageId: MSG_SAVEFILE_DUP
//
// MessageText:
//
// %1 already exists. File is being overwritten.
//
#define MSG_SAVEFILE_DUP                 ((HRESULT)0x6808080DL)

//
// MessageId: MSG_SAVEFILE_NOTDONE
//
// MessageText:
//
// File has not been saved.
//
#define MSG_SAVEFILE_NOTDONE             ((HRESULT)0xE808080EL)

//
// MessageId: MSG_RECALLFILE_SUCCESS
//
// MessageText:
//
// %1 has been recalled.
//
#define MSG_RECALLFILE_SUCCESS           ((HRESULT)0x6808080FL)

//
// MessageId: MSG_OBSOLETE_ISTATE
//
// MessageText:
//
// State version in  %1 is considered obsolete by this version of this code.
//
#define MSG_OBSOLETE_ISTATE              ((HRESULT)0xE8080810L)

//
// MessageId: MSG_ISTATE_TOONEW
//
// MessageText:
//
// State version in %1 is newer than the latest version supported by this code.
//
#define MSG_ISTATE_TOONEW                ((HRESULT)0xE8080811L)

//
// MessageId: MSG_RECALLFILE_FAIL
//
// MessageText:
//
// Error occurred while reading file %1.
//
#define MSG_RECALLFILE_FAIL              ((HRESULT)0xE8080812L)

//
// MessageId: MSG_SHELL_ERROR
//
// MessageText:
//
// Windows shell error: %1.
//
#define MSG_SHELL_ERROR                  ((HRESULT)0xE8080813L)

//
// MessageId: MSG_SENDMESSAGE_TIMEOUT
//
// MessageText:
//
// Send message timed out returning: %1.
//
#define MSG_SENDMESSAGE_TIMEOUT          ((HRESULT)0xE8080814L)

//
// MessageId: MSG_GPIB_TO_SYSTCTRL
//
// MessageText:
//
// Changing GPIB mode to System Controller.
//
#define MSG_GPIB_TO_SYSTCTRL             ((HRESULT)0x68080815L)

//
// MessageId: MSG_GPIB_TO_TALKLISTEN
//
// MessageText:
//
// Changing GPIB mode to Talker Listener.
//
#define MSG_GPIB_TO_TALKLISTEN           ((HRESULT)0x68080816L)

//
// MessageId: MSG_GPIB_IN_REMOTE
//
// MessageText:
//
// The Network Analyzer can not be put in GPIB System Controller mode 
// until the GPIB status is Local. Stop any remote GPIB programs which
// may be using the Network analyzer, press the Macro/Local key and try again.
//
#define MSG_GPIB_IN_REMOTE               ((HRESULT)0x68080817L)

//
// MessageId: MSG_INSTRUMENT_STATE_CLEARED
//
// MessageText:
//
// A preset or recall operation has begun and has cleared the instrument state.
//
#define MSG_INSTRUMENT_STATE_CLEARED     ((HRESULT)0x68080818L)

//
// MessageId: MSG_PNA_APPLICATION_EXITING
//
// MessageText:
//
// The PNA application is shutting down.
//
#define MSG_PNA_APPLICATION_EXITING      ((HRESULT)0x68080819L)

//
// MessageId: MSG_ALL_ACQUISITIONS_COMPLETE
//
// MessageText:
//
// All acquisitions for a manual trigger have completed.
//
#define MSG_ALL_ACQUISITIONS_COMPLETE    ((HRESULT)0x6808081AL)

//
// MessageId: E_NA_INVALIDFORMAT
//
// MessageText:
//
// The specified format is invalid.
//
#define E_NA_INVALIDFORMAT               ((HRESULT)0xE8080850L)

//
// MessageId: E_NA_EXCEPTION
//
// MessageText:
//
// WINNT exception caught by Automation layer.
//
#define E_NA_EXCEPTION                   ((HRESULT)0xE8080851L)

//
// MessageId: E_NA_BADPORT
//
// MessageText:
//
// Bad port specification.
//
#define E_NA_BADPORT                     ((HRESULT)0xE8080852L)

//
// MessageId: E_NA_PRINTER_TROUBLE
//
// MessageText:
//
// Failed to find a printer.
//
#define E_NA_PRINTER_TROUBLE             ((HRESULT)0xE8080853L)

//
// MessageId: E_NA_TRIGGERIGNORED
//
// MessageText:
//
// Manual trigger ignored.
//
#define E_NA_TRIGGERIGNORED              ((HRESULT)0xE8080854L)

//
// MessageId: E_NA_TRIGGERDENIED
//
// MessageText:
//
// Attempt to set trigger failed.
//
#define E_NA_TRIGGERDENIED               ((HRESULT)0xE8080855L)

//
// MessageId: E_NA_MACRO_FAILED
//
// MessageText:
//
// Macro execution failed.
//
#define E_NA_MACRO_FAILED                ((HRESULT)0xE8080856L)

//
// MessageId: E_NA_MACRO_NOT_DEFINED
//
// MessageText:
//
// Specified macro definition is incomplete.
//
#define E_NA_MACRO_NOT_DEFINED           ((HRESULT)0xE8080857L)

//
// MessageId: E_NA_DATA_LENGTH
//
// MessageText:
//
// Block data length error.
//
#define E_NA_DATA_LENGTH                 ((HRESULT)0xE8080859L)

//
// MessageId: E_NA_DATA_NOT_FOUND
//
// MessageText:
//
// Requested data not found.
//
#define E_NA_DATA_NOT_FOUND              ((HRESULT)0xE808085BL)

//
// MessageId: E_FUNCTION_NOT_SUPPORTED
//
// MessageText:
//
// This function not supported by this class.
//
#define E_FUNCTION_NOT_SUPPORTED         ((HRESULT)0xE808085CL)

//
// MessageId: E_WRONG_TYPE
//
// MessageText:
//
// This function supplied does not match the argument type.
//
#define E_WRONG_TYPE                     ((HRESULT)0xE808085DL)

//
// MessageId: S_NA_LIMIT_OUTOFRANGE
//
// MessageText:
//
// The parameter supplied was out of range, so was limited to a value in range before being applied to the instrument.
//
#define S_NA_LIMIT_OUTOFRANGE            ((HRESULT)0x2808085EL)

//
// MessageId: E_NA_LIMIT_OUTOFRANGE_ERROR
//
// MessageText:
//
// The parameter supplied was out of range, so was limited to a value in range before being applied to the instrument.
//
#define E_NA_LIMIT_OUTOFRANGE_ERROR      ((HRESULT)0xE808085FL)

//
// MessageId: E_NA_NO_LICENSE
//
// MessageText:
//
// Request failed. The required license was not found %1.
//
#define E_NA_NO_LICENSE                  ((HRESULT)0xE8080860L)

//
// MessageId: E_NA_FRONTPANEL_REMOTECALL
//
// MessageText:
//
// A remote call to the front panel has returned hresult %1.
//
#define E_NA_FRONTPANEL_REMOTECALL       ((HRESULT)0xE8080861L)

//
// MessageId: E_NA_RECALLFILE_FAIL_TERSE
//
// MessageText:
//
// The recall operation failed.
//
#define E_NA_RECALLFILE_FAIL_TERSE       ((HRESULT)0xE8080862L)

//
// MessageId: E_NA_SAVEFILE_FAIL_TERSE
//
// MessageText:
//
// Attempt to save file failed.
//
#define E_NA_SAVEFILE_FAIL_TERSE         ((HRESULT)0xE8080863L)

//
// MessageId: E_NA_RECALLFILE_FILE_NOT_FOUND_TERSE
//
// MessageText:
//
// Recall attempt failed because file was not found.
//
#define E_NA_RECALLFILE_FILE_NOT_FOUND_TERSE ((HRESULT)0xE8080864L)

//
// MessageId: E_NA_RECALLFILE_BAD_HEADER_TERSE
//
// MessageText:
//
// File cannot be loaded. The contents are not recognized.
//
#define E_NA_RECALLFILE_BAD_HEADER_TERSE ((HRESULT)0xE8080865L)

//
// MessageId: E_NA_OBSOLETE_ISTATE_TERSE
//
// MessageText:
//
// Recall file version is obsolete and no longer compatible with this instrument.
//
#define E_NA_OBSOLETE_ISTATE_TERSE       ((HRESULT)0xE8080866L)

//
// MessageId: E_NA_ISTATE_TOO_NEW_TERSE
//
// MessageText:
//
// The recall file contains an istate version newer than this instrument.
//
#define E_NA_ISTATE_TOO_NEW_TERSE        ((HRESULT)0xE8080867L)

//
// MessageId: E_NA_FRONTPANEL_ERROR
//
// MessageText:
//
// Front Panel %1.
//
#define E_NA_FRONTPANEL_ERROR            ((HRESULT)0xE8080868L)

//
// MessageId: MSG_NA_FRONTPANEL_MSG
//
// MessageText:
//
// Front Panel  %1.
//
#define MSG_NA_FRONTPANEL_MSG            ((HRESULT)0x68080869L)

//
// MessageId: E_NA_POWERSERVICE_ERROR
//
// MessageText:
//
// Power Service  %1.
//
#define E_NA_POWERSERVICE_ERROR          ((HRESULT)0xE808086AL)

//
// MessageId: MSG_NA_POWERSERVICE_MSG
//
// MessageText:
//
// Power Service  %1.
//
#define MSG_NA_POWERSERVICE_MSG          ((HRESULT)0x6808086BL)

//
// MessageId: E_NA_CANTLOAD_AGGPIB
//
// MessageText:
//
// The Agilent Technologies GPIB driver can not be loaded or unloaded.
//
#define E_NA_CANTLOAD_AGGPIB             ((HRESULT)0xE808086CL)

//
// MessageId: E_NA_CANTLOAD_NIGPIB
//
// MessageText:
//
// The National Instruments GPIB driver can not be loaded or unloaded.
//
#define E_NA_CANTLOAD_NIGPIB             ((HRESULT)0xE808086DL)

//
// MessageId: E_NA_CANTSTART_HPIB
//
// MessageText:
//
// The Agilent GPIB driver is loaded but it can not start its parser.
//
#define E_NA_CANTSTART_HPIB              ((HRESULT)0xE808086EL)

//
// MessageId: E_NA_FP_REMOTE
//
// MessageText:
//
// The front panel is in remote mode.
//
#define E_NA_FP_REMOTE                   ((HRESULT)0xA808086FL)

//
// MessageId: E_NA_CANTFIND_REGISTRY_KEY
//
// MessageText:
//
// The Registry Key specified could not be found.
//
#define E_NA_CANTFIND_REGISTRY_KEY       ((HRESULT)0xE8080870L)

//
// MessageId: E_NA_FP_PROBE_OVERCURRENT
//
// MessageText:
//
// An overcurrent condition has been detected on a probe plugged into the front panel.
//
#define E_NA_FP_PROBE_OVERCURRENT        ((HRESULT)0xA8080871L)

//
// MessageId: E_NA_OPERATION_TIMEOUT
//
// MessageText:
//
// The operation timed out.
//
#define E_NA_OPERATION_TIMEOUT           ((HRESULT)0xE8080872L)

//
// MessageId: MSG_PRESET
//
// MessageText:
//
// The Network Analyzer executed a preset.
//
#define MSG_PRESET                       ((HRESULT)0x68080873L)

//
// MessageId: E_NA_FILE_ACCESS_DENIED
//
// MessageText:
//
// Access to file denied.
//
#define E_NA_FILE_ACCESS_DENIED          ((HRESULT)0xE8080874L)

//
// MessageId: MSG_IS_STORAGE_FILE
//
// MessageText:
//
// File type is structured storage.
//
#define MSG_IS_STORAGE_FILE              ((HRESULT)0x68080875L)

//
// MessageId: E_NA_TRIGGERFAILED
//
// MessageText:
//
// The trigger operation failed.
//
#define E_NA_TRIGGERFAILED               ((HRESULT)0xE8080876L)

//
// MessageId: E_NA_BAD_ARGUMENT_VALUE
//
// MessageText:
//
// Argument out of range error.
//
#define E_NA_BAD_ARGUMENT_VALUE          ((HRESULT)0xE8080877L)

//
// MessageId: E_NA_DISPATCH_NOT_SUPPORTED
//
// MessageText:
//
// This method can not be invoked through a late-bound COM call.
//
#define E_NA_DISPATCH_NOT_SUPPORTED      ((HRESULT)0xE8080878L)

//
// MessageId: E_NA_NOT_A_CUSTOM_APPLICATION
//
// MessageText:
//
// The given COM object is not a custom application
//
#define E_NA_NOT_A_CUSTOM_APPLICATION    ((HRESULT)0xE8080879L)

//
// MessageId: E_NA_COULD_NOT_RECOGNIZE_ID
//
// MessageText:
//
// The eventID supplied was not recognized as a valid PNA eventID
//
#define E_NA_COULD_NOT_RECOGNIZE_ID      ((HRESULT)0xE808087AL)

//
// MessageId: E_NA_CANCELED
//
// MessageText:
//
// The operation was canceled.
//
#define E_NA_CANCELED                    ((HRESULT)0xE808087BL)

//
// MessageId: E_NA_SECURITY_LEVEL_LOCKED
//
// MessageText:
//
// Security levels of High or greater cannot be disabled directly.
// Only an instrument preset or recall of lower security 
// instrument state can reset a security level of High or greater.
//
#define E_NA_SECURITY_LEVEL_LOCKED       ((HRESULT)0xE808087CL)

//
// MessageId: E_NA_LOCAL_LOCKOUT
//
// MessageText:
//
// Local lockout mode is on.  The PNA application will not 
// accept input from front panel, keyboard or mouse until 
// this mode is turned off from a remote interface.
//
#define E_NA_LOCAL_LOCKOUT               ((HRESULT)0xE808087DL)

//
// MessageId: E_NA_BAD_SnP_REQUEST
//
// MessageText:
//
// The SnP request is not valid for the selected measurement.
//
#define E_NA_BAD_SnP_REQUEST             ((HRESULT)0xE808087EL)

//
// MessageId: E_NA_PRESET_NOT_SUPPORTED
//
// MessageText:
//
// Preset is not supported while this dialog or wizard is open. Close the dialog or wizard and then try again.
//
#define E_NA_PRESET_NOT_SUPPORTED        ((HRESULT)0xE808087FL)

//
// MessageId: E_NA_OPTION_NOT_INSTALLED_ERR
//
// MessageText:
//
// The function you requested requires a capability provided by an option
// to the standard analyzer. That option is not currently installed.
//
#define E_NA_OPTION_NOT_INSTALLED_ERR    ((HRESULT)0xE8080880L)

//
// MessageId: E_NA_CRASHED
//
// MessageText:
//
// Catastrophic error.  Crash dump recorded at %1.
//
#define E_NA_CRASHED                     ((HRESULT)0xE8080881L)

//
// MessageId: E_NA_GENERIC
//
// MessageText:
//
// %1
//
#define E_NA_GENERIC                     ((HRESULT)0xE8080882L)

//
// MessageId: E_NA_LICENSE_FILE_LIC
//
// MessageText:
//
// Failed to open gen.lic.
//
#define E_NA_LICENSE_FILE_LIC            ((HRESULT)0xE8080883L)

//
// MessageId: E_NA_LICENSE_JOB_LIC
//
// MessageText:
//
// Failed to start license job.
//
#define E_NA_LICENSE_JOB_LIC             ((HRESULT)0xE8080884L)

//
// MessageId: MSG_NA_RF_POWER_NOT_RECALLED
//
// MessageText:
//
// RF Power State not turned on, because the rf power state was set to OFF prior to recall/preset.
//
#define MSG_NA_RF_POWER_NOT_RECALLED     ((HRESULT)0x68080885L)

//
// MessageId: E_NA_USERPRESET_NOT_CONFIGURED
//
// MessageText:
//
// User Preset was issued, but no user preset state had been set.
//
#define E_NA_USERPRESET_NOT_CONFIGURED   ((HRESULT)0xE8080886L)

//
// MessageId: E_NA_WRONG_GPIB_MODE
//
// MessageText:
//
// ERROR: The PNA must be in system controller mode if you wish to use a device on GPIB0.
// %1 has been disabled, and the active channel has been put in HOLD.
//
#define E_NA_WRONG_GPIB_MODE             ((HRESULT)0xE8080887L)

//
// MessageId: E_NA_SET_SEGMENT_POWER_ON_ONE_OR_ALL_PORTS
//
// MessageText:
//
// Cannot set up sweep segments with a number of port power values greater than one and 
// less than the number of ports.  For each segment, please specify either just one power 
// value, or power values for every one of the ports.
//
#define E_NA_SET_SEGMENT_POWER_ON_ONE_OR_ALL_PORTS ((HRESULT)0xE8080888L)

//
// MessageId: E_BAD_ARGUMENT_COUNT
//
// MessageText:
//
// Incorrect number of arguments.
//
#define E_BAD_ARGUMENT_COUNT             ((HRESULT)0xE8080889L)

//
// MessageId: E_NA_FILE_EXCEPTION
//
// MessageText:
//
// An unexpected error occurred while attempting to read or write a file.
//
#define E_NA_FILE_EXCEPTION              ((HRESULT)0xE808088AL)

//
// MessageId: E_NA_FEATURE_IS_NOT_AVAILABLE
//
// MessageText:
//
// The requested feature is not available in the current context.
//
#define E_NA_FEATURE_IS_NOT_AVAILABLE    ((HRESULT)0xE808088BL)

//
// MessageId: S_NA_FEATURE_IS_IMMUTABLE
//
// MessageText:
//
// ERROR: This feature is locked to a particular value.
//
#define S_NA_FEATURE_IS_IMMUTABLE        ((HRESULT)0x6808088CL)

//
// MessageId: E_NA_RECALLED_STATE_HAS_TOO_MANY_PORTS
//
// MessageText:
//
// The recall operation failed.  The state originated on an instrument with a
// greater number of hardware ports. It cannot be recalled on this instrument.
//
#define E_NA_RECALLED_STATE_HAS_TOO_MANY_PORTS ((HRESULT)0xE808088CL)

//
// MessageId: E_NA_APPLICATION_NAME_NOT_FOUND
//
// MessageText:
//
// Could not create the measurement. The application name was not recognized.
//
#define E_NA_APPLICATION_NAME_NOT_FOUND  ((HRESULT)0xE808088DL)

//
// MessageId: E_NA_MEASUREMENT_NAME_NOT_FOUND
//
// MessageText:
//
// Could not create the measurement. The measurement parameter name was not recognized.
//
#define E_NA_MEASUREMENT_NAME_NOT_FOUND  ((HRESULT)0xE808088EL)

//
// MessageId: MSG_FAVORITE_MEMORIZED
//
// MessageText:
//
// This key has been added to the Favorites menu.
//
#define MSG_FAVORITE_MEMORIZED           ((HRESULT)0x6808088FL)

//
// MessageId: E_NA_FAVORITES_MENU_FULL
//
// MessageText:
//
// Unable to add this key to the Favorites menu because the menu is full.
//
#define E_NA_FAVORITES_MENU_FULL         ((HRESULT)0xE8080890L)

//
// MessageId: E_NA_UNSUPPORTED_STRING_ARGUMENT
//
// MessageText:
//
// Remote command received an argument containing a string that the remote command does not recognize.
//
#define E_NA_UNSUPPORTED_STRING_ARGUMENT ((HRESULT)0xE8080891L)

//
// MessageId: E_NA_DISABLED_FOR_HIGH_BWID
//
// MessageText:
//
// Disabled for bandwidths higher than 600KHz.
//
#define E_NA_DISABLED_FOR_HIGH_BWID      ((HRESULT)0xE8080892L)

//
// MessageId: E_NA_FILE_NOT_FOUND
//
// MessageText:
//
// The requested file was not found, %1.
//
#define E_NA_FILE_NOT_FOUND              ((HRESULT)0xE8080893L)

//
// MessageId: E_NA_DISABLED_SAVES_OF_ASCII_DATA
//
// MessageText:
//
// Cannot save ASCII data files when the security level is greater than High. 
// Only an instrument preset or recall of lower security 
// instrument state will reset this security level.
//
#define E_NA_DISABLED_SAVES_OF_ASCII_DATA ((HRESULT)0xE8080894L)

//
// MessageId: E_NA_APPLICATION_CHANNELS_ARE_DISABLED_WHEN_EXTERNAL_TESTSET_IS_ENABLED
//
// MessageText:
//
// Error: Cannot create this channel while an external testset is enabled
//
#define E_NA_APPLICATION_CHANNELS_ARE_DISABLED_WHEN_EXTERNAL_TESTSET_IS_ENABLED ((HRESULT)0xE8080895L)

//
// MessageId: E_NA_EXTERNAL_TESTSET_IS_DISABLED_WHILE_APPLICATION_CHANNELS_ARE_IN_USE
//
// MessageText:
//
// Error: Cannot enable external testset while application channels are in use. Preset, and then try again.
//
#define E_NA_EXTERNAL_TESTSET_IS_DISABLED_WHILE_APPLICATION_CHANNELS_ARE_IN_USE ((HRESULT)0xE8080896L)

//
// MessageId: E_NA_FAST_SWEEP_MODE_NOT_SUPPORTED
//
// MessageText:
//
// ERROR: Fast Sweep Mode is not supported on this instrument. 
//
#define E_NA_FAST_SWEEP_MODE_NOT_SUPPORTED ((HRESULT)0xE8080897L)

//
// MessageId: E_NA_POWER_SWEEP_NOT_SUPPORTED_WITH_NO_SOURCE_PORT
//
// MessageText:
//
// ERROR: A channel can not use power sweep if there is a parameter with no source port.
//
#define E_NA_POWER_SWEEP_NOT_SUPPORTED_WITH_NO_SOURCE_PORT ((HRESULT)0xE8080898L)

//
// MessageId: E_NA_SOURCE_PORT_REQUIRED_IN_POWER_SWEEP
//
// MessageText:
//
// ERROR: If a channel is in power sweep, then each parameter must have a source port.
//
#define E_NA_SOURCE_PORT_REQUIRED_IN_POWER_SWEEP ((HRESULT)0xE8080899L)

//
// MessageId: E_NA_FIFO_IS_NOT_TURNED_ON
//
// MessageText:
//
// ERROR: This command is invalid since the FIFO has not been turned on.
//
#define E_NA_FIFO_IS_NOT_TURNED_ON       ((HRESULT)0xE808089AL)

//
// MessageId: E_NA_FIFO_TOO_MANY_BUCKETS_REQUESTED
//
// MessageText:
//
// ERROR: The FIFO does not have enough buckets to satisfy the request. 
//
#define E_NA_FIFO_TOO_MANY_BUCKETS_REQUESTED ((HRESULT)0xE808089BL)

//
// MessageId: E_NA_COULD_NOT_CREATE_FIFO
//
// MessageText:
//
// ERROR: There was not enough disk space to create the FIFO data file.
//
#define E_NA_COULD_NOT_CREATE_FIFO       ((HRESULT)0xE808089CL)

//
// MessageId: E_NA_FEATURE_NOT_AVAILABLE_ON_THIS_HARDWARE
//
// MessageText:
//
// ERROR: This feature is not available on this model of hardware.
//
#define E_NA_FEATURE_NOT_AVAILABLE_ON_THIS_HARDWARE ((HRESULT)0xE808089DL)

//
// MessageId: E_NA_FEATURE_NOT_AVAILABLE_ON_THIS_APPLICATION
//
// MessageText:
//
// ERROR: This feature is not available on this application.
//
#define E_NA_FEATURE_NOT_AVAILABLE_ON_THIS_APPLICATION ((HRESULT)0xE808089EL)

//
// MessageId: E_NA_GLOBAL_POWER_LIMIT_VIOLATED
//
// MessageText:
//
// ERROR: Power limit(s) of %1 dBm limited on port(s) %2
//
#define E_NA_GLOBAL_POWER_LIMIT_VIOLATED ((HRESULT)0xE808089FL)

//
// MessageId: E_NA_GLOBAL_POWER_LIMIT_UNACHIEVABLE
//
// MessageText:
//
// ERROR: Power limit(s) of %1 dBm unachievable on port(s) %2. Source turned OFF.
//
#define E_NA_GLOBAL_POWER_LIMIT_UNACHIEVABLE ((HRESULT)0xE80808A0L)

//
// MessageId: E_NA_FAST_SWEEP_MODE_TURNED_OFF
//
// MessageText:
//
// ERROR: Fast sweep mode not available during power limiting. Fast sweep mode turned OFF.
//
#define E_NA_FAST_SWEEP_MODE_TURNED_OFF  ((HRESULT)0xE80808A1L)

//
// MessageId: E_NA_DSP_MISSING_FEATURE
//
// MessageText:
//
// Current DSP hardware does not support this feature.
//
#define E_NA_DSP_MISSING_FEATURE         ((HRESULT)0xE80808A2L)

//
// MessageId: MSG_CALPOD_STARTUP
//
// MessageText:
//
// Connecting to Calpod Controller...
//
#define MSG_CALPOD_STARTUP               ((HRESULT)0x680808A3L)

//
// MessageId: E_NA_EXTERNAL_TESTSET_IS_DISABLED_WHILE_PHASE_CONTROL_ENABLED
//
// MessageText:
//
// Error: Cannot enable external testset while phase control is enabled.
//
#define E_NA_EXTERNAL_TESTSET_IS_DISABLED_WHILE_PHASE_CONTROL_ENABLED ((HRESULT)0xE80808A4L)

//
// MessageId: E_NA_EXTERNAL_SOURCE_NOT_SUPPORTED_WITH_PHASE_CONTROL
//
// MessageText:
//
// Error: The %1 is not supported with phase control.
//
#define E_NA_EXTERNAL_SOURCE_NOT_SUPPORTED_WITH_PHASE_CONTROL ((HRESULT)0xE80808A5L)

//
// MessageId: E_NA_RECALLFILE_CANCELED_EXT_DEVICES_NOT_FOUND
//
// MessageText:
//
// Recall cancelled.  External device(s) missing. System left in Preset state.
//
#define E_NA_RECALLFILE_CANCELED_EXT_DEVICES_NOT_FOUND ((HRESULT)0xE80808A6L)

//
// MessageId: MSG_FAVORITE_EXISTS
//
// MessageText:
//
// This key is already on the Favorites menu.
//
#define MSG_FAVORITE_EXISTS              ((HRESULT)0xE80808A7L)

//
// MessageId: E_NA_GET_SNP_DATA_FAILED
//
// MessageText:
//
// Get SnP data failed. Check calibration is enabled.
//
#define E_NA_GET_SNP_DATA_FAILED         ((HRESULT)0xE80808A8L)

//
// MessageId: E_NA_PHASE_CONTROL_MODE_NOT_SET
//
// MessageText:
//
// Phase control mode not set, invalid mode.
//
#define E_NA_PHASE_CONTROL_MODE_NOT_SET  ((HRESULT)0xE80808A9L)

//
// MessageId: E_NA_ONLY_ONE_SYNCHRONOUS_SWEEP_AT_ANY_TIME
//
// MessageText:
//
// Error: Only one synchronous sweep allowed at a time. A client program attempted to start a new synchronous sweep before the previous one was finished.
//
#define E_NA_ONLY_ONE_SYNCHRONOUS_SWEEP_AT_ANY_TIME ((HRESULT)0xE80808AAL)

//
// MessageId: E_NA_FILE_HAS_TOO_MANY_DATA_POINTS
//
// MessageText:
//
// The data file could not be recalled because it contains more data points than the current maximum allowed number.
//
#define E_NA_FILE_HAS_TOO_MANY_DATA_POINTS ((HRESULT)0xE80808ABL)

//
// MessageId: E_NA_IO_INTERFACE_NOT_PRESENT
//
// MessageText:
//
// The requested interface is not configured for this instrument.
//
#define E_NA_IO_INTERFACE_NOT_PRESENT    ((HRESULT)0xE80808ACL)

//
// MessageId: E_NA_NO_DOCUMENT
//
// MessageText:
//
// No measurement container found.
//
#define E_NA_NO_DOCUMENT                 ((HRESULT)0xE80808ADL)

//
// MessageId: E_NA_EXECUTION_GENERAL_ERROR
//
// MessageText:
//
// Execution error.
//
#define E_NA_EXECUTION_GENERAL_ERROR     ((HRESULT)0xE80808AEL)

//
// MessageId: E_NA_SUFFIX_OUT_OF_RANGE
//
// MessageText:
//
// Header suffix out of range.
//
#define E_NA_SUFFIX_OUT_OF_RANGE         ((HRESULT)0xE80808AFL)

//
// MessageId: E_NA_LOAD_FAILED
//
// MessageText:
//
// The state was not loaded. Please check the file name.
//
#define E_NA_LOAD_FAILED                 ((HRESULT)0xE80808B0L)

//
// MessageId: E_NA_STORE_FAILED
//
// MessageText:
//
// The state was not stored. Please check the file and path names.
//
#define E_NA_STORE_FAILED                ((HRESULT)0xE80808B1L)

//
// MessageId: E_NA_DATA_OUT_OF_RANGE
//
// MessageText:
//
// Data is out of range.
//
#define E_NA_DATA_OUT_OF_RANGE           ((HRESULT)0xE80808B2L)

//
// MessageId: E_NA_REFERENCE_MARKER_NOT_FOUND
//
// MessageText:
//
// Reference marker not found.
//
#define E_NA_REFERENCE_MARKER_NOT_FOUND  ((HRESULT)0xE80808B3L)

//
// MessageId: E_NA_USER_RANGE_NOT_VALID
//
// MessageText:
//
// The currently selected user range is not valid.
//
#define E_NA_USER_RANGE_NOT_VALID        ((HRESULT)0xE80808B4L)

//
// MessageId: E_NA_RECALLED_STATE_FROM_INCOMPATIBLE_PLATFORM
//
// MessageText:
//
// Cannot recall file created on a different instrument family.
//
#define E_NA_RECALLED_STATE_FROM_INCOMPATIBLE_PLATFORM ((HRESULT)0xE80808B5L)

//
// MessageId: E_NA_MARKER_NOT_DELTA
//
// MessageText:
//
// The specified marker is not a delta marker.
//
#define E_NA_MARKER_NOT_DELTA            ((HRESULT)0xE80808B6L)

//
// MessageId: E_NA_SCPI_ERROR_EVENT
//
// MessageText:
//
// A scpi error occurred.
//
#define E_NA_SCPI_ERROR_EVENT            ((HRESULT)0xE80808B7L)

//
// MessageId: E_NA_SHUTDOWN_DENIED
//
// MessageText:
//
// The shutdown request was denied.
//
#define E_NA_SHUTDOWN_DENIED             ((HRESULT)0xE80808B8L)

//
// MessageId: E_NA_COULD_NOT_CREATE_BINARY_BLOCK
//
// MessageText:
//
// Could not produce binary block of instrument state settings.
//
#define E_NA_COULD_NOT_CREATE_BINARY_BLOCK ((HRESULT)0xE80808B9L)

//
// MessageId: E_NA_COULD_NOT_READ_BINARY_BLOCK
//
// MessageText:
//
// Could not read binary block of instrument state settings.  Unrecognized format.
//
#define E_NA_COULD_NOT_READ_BINARY_BLOCK ((HRESULT)0xE80808BAL)

//
// MessageId: E_NA_FILE_NAME_IS_EMPTY
//
// MessageText:
//
// The filename cannot be empty.
//
#define E_NA_FILE_NAME_IS_EMPTY          ((HRESULT)0xE80808BBL)

//
// MessageId: E_NA_MEASUREMENT_EXISTS
//
// MessageText:
//
// The measurement number is already in use.
//
#define E_NA_MEASUREMENT_EXISTS          ((HRESULT)0xE80808BCL)

//
// MessageId: E_NA_NO_PORTS_SPECIFIED
//
// MessageText:
//
// No port numbers were specified.
//
#define E_NA_NO_PORTS_SPECIFIED          ((HRESULT)0xE80808BDL)

//
// MessageId: E_NA_UNSUPPORTED_CONCURRENT_OVERLAPPED_OPERATION
//
// MessageText:
//
// Multiple overlapped operations are not supported.
//
#define E_NA_UNSUPPORTED_CONCURRENT_OVERLAPPED_OPERATION ((HRESULT)0xE80808BEL)

//
// MessageId: MSG_VNAPARSER_DPRINT
//
// MessageText:
//
// Used to turn on/off logging of diagnostic data in VNAParser Log Window.
//
#define MSG_VNAPARSER_DPRINT             ((HRESULT)0x680808BFL)

//
// MessageId: E_NA_BAD_PATH
//
// MessageText:
//
// The path is invalid.
//
#define E_NA_BAD_PATH                    ((HRESULT)0xE80808C0L)

//
// MessageId: E_NA_BAD_UnP_REQUEST
//
// MessageText:
//
// The UnP request is not valid for the selected measurement.
//
#define E_NA_BAD_UnP_REQUEST             ((HRESULT)0xE80808C1L)

//
// MessageId: E_NA_UNC_NOT_AVAILABLE
//
// MessageText:
//
// Uncertainty not available for the selected measurement.
//
#define E_NA_UNC_NOT_AVAILABLE           ((HRESULT)0xE80808C2L)

//
// MessageId: E_NA_BAD_DSD_REQUEST
//
// MessageText:
//
// The DSD request is not valid for the selected measurement.
//
#define E_NA_BAD_DSD_REQUEST             ((HRESULT)0xE80808C3L)

//
// MessageId: E_NA_TESTSET_INVALID_FOR_UNCERTAINTIES
//
// MessageText:
//
// The current testset file does not support uncertainties. Contact Keysight for an updated testset file.
//
#define E_NA_TESTSET_INVALID_FOR_UNCERTAINTIES ((HRESULT)0xE80808C4L)

//
// MessageId: E_NA_TESTSET_INVALID_FOR_CALIBRATION
//
// MessageText:
//
// The current testset file does not completely support vector error correction. Contact Keysight for an updated testset file.
//
#define E_NA_TESTSET_INVALID_FOR_CALIBRATION ((HRESULT)0xE80808C5L)

//
// MessageId: E_NA_UNCERTAINTY_FEATURE_OPERATION_FAILED
//
// MessageText:
//
// The Uncertainty feature operation failed.
//
#define E_NA_UNCERTAINTY_FEATURE_OPERATION_FAILED ((HRESULT)0xE80808C6L)

//
// MessageId: E_NA_BAD_SDATCV_REQUEST
//
// MessageText:
//
// The SDATCV request is not valid for the selected measurement.
//
#define E_NA_BAD_SDATCV_REQUEST          ((HRESULT)0xE80808C7L)

//
// MessageId: E_NA_BAD_DSD_PORTS
//
// MessageText:
//
// DSD files can be saved from one-port or two-port calibrations only.
//
#define E_NA_BAD_DSD_PORTS               ((HRESULT)0xE80808C8L)

//
// MessageId: E_NA_INVALID_UNCERTAINTY_FILENAME_EXTENSION
//
// MessageText:
//
// The file name extension in the specified file name is not a recognized uncertainty data file format.
//
#define E_NA_INVALID_UNCERTAINTY_FILENAME_EXTENSION ((HRESULT)0xE80808C9L)

//
// MessageId: E_NA_SEND_INIT_BEFORE_ADD
//
// MessageText:
//
// Error: Must send SYST:DATA:MEM:INIT before SYST:DATA:MEM:ADD
//
#define E_NA_SEND_INIT_BEFORE_ADD        ((HRESULT)0xE80808CAL)

//
// MessageId: E_NA_COMMIT_MAP_NAME_CANNOT_BE_EMPTY
//
// MessageText:
//
// Error: The name of the memory map cannot be an empty string
//
#define E_NA_COMMIT_MAP_NAME_CANNOT_BE_EMPTY ((HRESULT)0xE80808CBL)

//
// MessageId: E_NA_MEMORY_MAP_NAME_CANNOT_BE_FOUND
//
// MessageText:
//
// Error: The memory map name specified could not be found.
//
#define E_NA_MEMORY_MAP_NAME_CANNOT_BE_FOUND ((HRESULT)0xE80808CCL)

//
// MessageId: E_NA_INVALID_CLOCK
//
// MessageText:
//
// Error: The system clock has been set back earlier than the actual date. This may be an attempt to prevent time perishable licenses from expiring. Please set the correct time on the clock and then relaunch the firmware. If this message continues to show, even after restoring the clock, please contact support: ctd-soco_support@keysight.com.
//
#define E_NA_INVALID_CLOCK               ((HRESULT)0xE80808CDL)

//
// MessageId: E_EXPIRED_TEMP_LICENSES
//
// MessageText:
//
// Error: At least one of your temporary licenses has expired. The expired licenses are: %1. 
//
#define E_EXPIRED_TEMP_LICENSES          ((HRESULT)0xE80808CEL)

//
// MessageId: E_NA_REQUIRES_MANUAL_TRIGGER_MODE
//
// MessageText:
//
// Error: Manual trigger mode is not configured, and is required.
//
#define E_NA_REQUIRES_MANUAL_TRIGGER_MODE ((HRESULT)0xE80808CFL)

//
// MessageId: E_NA_ARMED_CHANNEL_EXISTS
//
// MessageText:
//
// Error: A channel is armed, the specified channels cannot be setup for single sweep; abort the armed channel first.
//
#define E_NA_ARMED_CHANNEL_EXISTS        ((HRESULT)0xE80808D0L)

//
// MessageId: E_NA_INVALID_STRING
//
// MessageText:
//
// Invalid string data.
//
#define E_NA_INVALID_STRING              ((HRESULT)0xE80808D1L)

//
// MessageId: E_NA_NUMERIC_OVERFLOW
//
// MessageText:
//
// Numeric overflow.
//
#define E_NA_NUMERIC_OVERFLOW            ((HRESULT)0xE80808D2L)

//
// MessageId: MSG_AME_DEV_RELEASE
//
// MessageText:
//
// WARNING:  Development Release.  Do NOT ship to Customers!
//
#define MSG_AME_DEV_RELEASE              ((HRESULT)0x690103E8L)

//
// MessageId: E_AME_MIXER_SEGMENTS_FAILED_VERIFICATION
//
// MessageText:
//
// ERROR:  Mixer Segments failed verification.
//
#define E_AME_MIXER_SEGMENTS_FAILED_VERIFICATION ((HRESULT)0xE90103E9L)

//
// MessageId: E_AME_MIXER_PARAMETER_FILE_NOT_FOUND
//
// MessageText:
//
// ERROR:  Mixer parameter file was not found
//
#define E_AME_MIXER_PARAMETER_FILE_NOT_FOUND ((HRESULT)0xE90103F0L)

//
// MessageId: E_AME_FAILED_TO_FIND_ATTRIBUTE
//
// MessageText:
//
// ERROR:  Attribute not found in External Source Configuration
//
#define E_AME_FAILED_TO_FIND_ATTRIBUTE   ((HRESULT)0xE90103F1L)

//
// MessageId: E_AME_LICENSE_NOT_INSTALLED
//
// MessageText:
//
// ERROR:  License is not installed.
//
#define E_AME_LICENSE_NOT_INSTALLED      ((HRESULT)0xE90103F2L)

//
// MessageId: E_AME_RCM_TIMEOUT
//
// MessageText:
//
// ERROR: External Source Timed out
//
#define E_AME_RCM_TIMEOUT                ((HRESULT)0xE90103F3L)

//
// MessageId: E_AME_RCM_INV_OBJECT
//
// MessageText:
//
// ERROR: External Source Invalid object detected.
//
#define E_AME_RCM_INV_OBJECT             ((HRESULT)0xE90103F4L)

//
// MessageId: E_AME_RSRC_NFOUND
//
// MessageText:
//
// ERROR: External Source Resource not found.  Is the GPIB cable connected?
//
#define E_AME_RSRC_NFOUND                ((HRESULT)0xE90103F5L)

//
// MessageId: E_AME_RCM_INVALID_INTERFACE
//
// MessageText:
//
// ERROR: External Source invalid GPIB interface.  Must use 1 or 2.
//
#define E_AME_RCM_INVALID_INTERFACE      ((HRESULT)0xE90103F6L)

//
// MessageId: E_AME_RCM_INVALID_ADDRESS
//
// MessageText:
//
// ERROR: External Source invalid GPIB address.  Must be between 0 and 31.
//
#define E_AME_RCM_INVALID_ADDRESS        ((HRESULT)0xE90103F7L)

//
// MessageId: E_AME_RCM_VISA_ERROR
//
// MessageText:
//
// ERROR:  External Source %1.
//
#define E_AME_RCM_VISA_ERROR             ((HRESULT)0xE90103F8L)

//
// MessageId: E_AME_COMPONENT_OUT_OF_DATE
//
// MessageText:
//
// ERROR: Component is out of date
//
#define E_AME_COMPONENT_OUT_OF_DATE      ((HRESULT)0xE90103F9L)

//
// MessageId: E_AME_INVALID_LO_FREQ_MODE
//
// MessageText:
//
// ERROR: Invalid Frequency Mode.
//
#define E_AME_INVALID_LO_FREQ_MODE       ((HRESULT)0xE90103FAL)

//
// MessageId: E_AME_INVALIDARG
//
// MessageText:
//
// ERROR: Invalid Argument
//
#define E_AME_INVALIDARG                 ((HRESULT)0xE90103FBL)

//
// MessageId: E_AME_INVALID_PORT_SELECTION
//
// MessageText:
//
// ERROR: Invalid Port Selection.
//
#define E_AME_INVALID_PORT_SELECTION     ((HRESULT)0xE90103FCL)

//
// MessageId: E_AME_INVALID_LO_NAME
//
// MessageText:
//
// ERROR: Invalid LO Name.
//
#define E_AME_INVALID_LO_NAME            ((HRESULT)0xE90103FDL)

//
// MessageId: E_AME_INVALID_S2P_FILE
//
// MessageText:
//
// ERROR: File format not recognized, not a valid s2p file.
//
#define E_AME_INVALID_S2P_FILE           ((HRESULT)0xE90103FEL)

//
// MessageId: E_AME_CANNOT_INTERPOLATE_FREQS
//
// MessageText:
//
// ERROR:  Cannot interpolate calibration data to specified frequencies
//
#define E_AME_CANNOT_INTERPOLATE_FREQS   ((HRESULT)0xE90103FFL)

//
// MessageId: E_AME_UNDEFINED_MESSAGE
//
// MessageText:
//
// ERROR:  Undefined measurement message.
//
#define E_AME_UNDEFINED_MESSAGE          ((HRESULT)0xE90103A0L)

//
// MessageId: E_AME_UNDEFINED_MENU_PICK
//
// MessageText:
//
// ERROR:  Undefined measurement menu selection.
//
#define E_AME_UNDEFINED_MENU_PICK        ((HRESULT)0xE90103A1L)

//
// MessageId: E_AME_DISPLAY_FAILED_TO_INIT
//
// MessageText:
//
// ERROR:  Measurement display failed to initialize.
//
#define E_AME_DISPLAY_FAILED_TO_INIT     ((HRESULT)0xE90103A2L)

//
// MessageId: E_AME_FAILED_TO_INITALIZE_RCM
//
// MessageText:
//
// ERROR:  failed to initialize the role control module
//
#define E_AME_FAILED_TO_INITALIZE_RCM    ((HRESULT)0xE90103A3L)

//
// MessageId: E_AME_FAILED_CONFIGURE_RCM
//
// MessageText:
//
// ERROR:  failed to configure the role control module
//
#define E_AME_FAILED_CONFIGURE_RCM       ((HRESULT)0xE90103A4L)

//
// MessageId: E_AME_INVALID_LO_SPECIFIED
//
// MessageText:
//
// ERROR: Invalid LO specified
//
#define E_AME_INVALID_LO_SPECIFIED       ((HRESULT)0xE90103A5L)

//
// MessageId: E_AME_NO_ECAL_FOUND
//
// MessageText:
//
// ERROR: No ECAL module found
//
#define E_AME_NO_ECAL_FOUND              ((HRESULT)0xE90103A6L)

//
// MessageId: E_AME_CANT_CONNECT_TO_RCM
//
// MessageText:
//
// ERROR: Could not connect to External Source.  Check settings and try again.
//
#define E_AME_CANT_CONNECT_TO_RCM        ((HRESULT)0xE90103A7L)

//
// MessageId: E_AME_ZERO_STEPS
//
// MessageText:
//
// ERROR
//
#define E_AME_ZERO_STEPS                 ((HRESULT)0xE90103A8L)

//
// MessageId: E_AME_REQUIRES_2_STAGE_MIXER
//
// MessageText:
//
// ERROR:  Requires two-stage Mixer.
//
#define E_AME_REQUIRES_2_STAGE_MIXER     ((HRESULT)0xE90103A9L)

//
// MessageId: E_AME_EMPTY_CALSET
//
// MessageText:
//
// ERROR:  Calset was empty or could not find it.
//
#define E_AME_EMPTY_CALSET               ((HRESULT)0xE90103AAL)

//
// MessageId: E_AME_COULD_NOT_MORPH_CUST_CAL
//
// MessageText:
//
// ERROR:  Could not turn on cal for custom measurement.
//
#define E_AME_COULD_NOT_MORPH_CUST_CAL   ((HRESULT)0xE90103ABL)

//
// MessageId: E_AME_PROCESS_DATA_ABORTED
//
// MessageText:
//
// FATAL ERROR: Process Data Aborted 
//
#define E_AME_PROCESS_DATA_ABORTED       ((HRESULT)0xE90103ACL)

//
// MessageId: E_AME_MIXER_IS_CORRUPT
//
// MessageText:
//
// ERROR: Mixer configuration is invalid. (Channel %1).
//
#define E_AME_MIXER_IS_CORRUPT           ((HRESULT)0xE90103ADL)

//
// MessageId: E_AME_SMC_FAILED_PWR_MTR_READ
//
// MessageText:
//
// FATAL ERROR: Scalar calibration failed due to power meter errors. 
//
#define E_AME_SMC_FAILED_PWR_MTR_READ    ((HRESULT)0xE90103AEL)

//
// MessageId: E_AME_OPTION_REQUIRED_080
//
// MessageText:
//
// Calibration Type or Measurement Requires Hardware Option 080
//
#define E_AME_OPTION_REQUIRED_080        ((HRESULT)0xE90103AFL)

//
// MessageId: E_AME_OPTION_REQUIRED_081
//
// MessageText:
//
// Vector Mixer/Converter Caltype or Measurement Requires internal solid state switch in the R1 reference path for controlling an external reference mixer.
//
#define E_AME_OPTION_REQUIRED_081        ((HRESULT)0xE90103B0L)

//
// MessageId: E_AME_OPTION_REQUIRED_083
//
// MessageText:
//
// Requires Software License Option 083.  For information about updates and current issues regarding the Frequency Converter Application (Option 083), please visit www.agilent.com/find/fca
//
#define E_AME_OPTION_REQUIRED_083        ((HRESULT)0xE90103B1L)

//
// MessageId: E_AME_CAL_REMOTE_START
//
// MessageText:
//
// ERROR: You need to start calibration with a configured measurement. 
//
#define E_AME_CAL_REMOTE_START           ((HRESULT)0xE90103B2L)

//
// MessageId: E_AME_SOURCE_CONFIGURATION_WAS_NOT_FOUND
//
// MessageText:
//
// ERROR:  Specified external source was not found.  %1
//
#define E_AME_SOURCE_CONFIGURATION_WAS_NOT_FOUND ((HRESULT)0xE90103B3L)

//
// MessageId: E_AME_INPUT_STOP_LESS_INPUT_START
//
// MessageText:
//
// ERROR:  The Input Stop Frequency Cannot Be Less Than The Start Frequency
//
#define E_AME_INPUT_STOP_LESS_INPUT_START ((HRESULT)0xE90103B4L)

//
// MessageId: E_AME_INPUT_START_GRE_INPUT_STOP
//
// MessageText:
//
// ERROR:  The Input Start Frequency Cannot Be Greater Than The Stop Frequency
//
#define E_AME_INPUT_START_GRE_INPUT_STOP ((HRESULT)0xE90103B5L)

//
// MessageId: E_AME_LO_2_FREQ_OVERLAPS_IF
//
// MessageText:
//
// ERROR:  The IF frequency is not permitted to overlap the LO2 frequency for a low-side mixer
//
#define E_AME_LO_2_FREQ_OVERLAPS_IF      ((HRESULT)0xE90103B7L)

//
// MessageId: E_AME_INPUT_FREQ_OVERLAPS_LO
//
// MessageText:
//
// ERROR:  The input frequency is not permitted to overlap the LO frequency for a low-side mixer
//
#define E_AME_INPUT_FREQ_OVERLAPS_LO     ((HRESULT)0xE90103B8L)

//
// MessageId: E_AME_RESULTANT_INPUT_FREQ_EXCEEDS_INSTRUMENTS_CAPABILITIES
//
// MessageText:
//
// ERROR:  The Resultant Input Start or Stop Frequency Exceeds the Limits of the Instrument
//
#define E_AME_RESULTANT_INPUT_FREQ_EXCEEDS_INSTRUMENTS_CAPABILITIES ((HRESULT)0xE90103B9L)

//
// MessageId: E_AME_RESULTANT_OUPUT_FREQ_EXCEEDS_INSTRUMENTS_CAPABILITIES
//
// MessageText:
//
// ERROR:  The Resultant Output Start or Stop Frequency Exceeds the Limits of the Instrument
//
#define E_AME_RESULTANT_OUPUT_FREQ_EXCEEDS_INSTRUMENTS_CAPABILITIES ((HRESULT)0xE90103BAL)

//
// MessageId: E_AME_FREQ_EXCEEDS_MAX_INSTRUMENT_FREQ
//
// MessageText:
//
// ERROR:  Value Exceeds The Maximum Frequency Of The Instrument
//
#define E_AME_FREQ_EXCEEDS_MAX_INSTRUMENT_FREQ ((HRESULT)0xE90103BBL)

//
// MessageId: E_AME_FREQ_EXCEEDS_MIN_INSTRUMENT_FREQ
//
// MessageText:
//
// ERROR:  Value Exceeds The Minimum Frequency Of The Instrument
//
#define E_AME_FREQ_EXCEEDS_MIN_INSTRUMENT_FREQ ((HRESULT)0xE90103BCL)

//
// MessageId: E_AME_ZERO_STEPS_ECAL
//
// MessageText:
//
// ERROR:  An error has occured during calibration and calibration cannot continue.  Please verify that the ECAL selected covers the desired calibration frequency range.
//
#define E_AME_ZERO_STEPS_ECAL            ((HRESULT)0xE90103BDL)

//
// MessageId: E_AME_ZERO_STEPS_MECH
//
// MessageText:
//
// ERROR:  An error has occured during calibration and calibration cannot continue.  Please verify that the connectors and calkits selected cover the desired calibration frequency range.
//
#define E_AME_ZERO_STEPS_MECH            ((HRESULT)0xE90103BEL)

//
// MessageId: E_AME_INPUT_OUTPUT_NO_UPCONVERTER_POSSIBLE
//
// MessageText:
//
// ERROR: It is not possible to calculate an input frequency to a mixer that can upconvert to that output frequency
//
#define E_AME_INPUT_OUTPUT_NO_UPCONVERTER_POSSIBLE ((HRESULT)0xE90103BFL)

//
// MessageId: E_AME_IF_OUTPUT_NO_UPCONVERTER_POSSIBLE
//
// MessageText:
//
// ERROR: It is not possible to calculate an IF frequency to a mixer that can upconvert to that output frequency
//
#define E_AME_IF_OUTPUT_NO_UPCONVERTER_POSSIBLE ((HRESULT)0xE90103C0L)

//
// MessageId: E_AME_INPUT_IF_NO_UPCONVERTER_POSSIBLE
//
// MessageText:
//
// ERROR: It is not possible to calculate an input frequency to a mixer that can upconvert to that IF frequency
//
#define E_AME_INPUT_IF_NO_UPCONVERTER_POSSIBLE ((HRESULT)0xE90103C1L)

//
// MessageId: E_AME_INPUT_START_FREQUENCY_OUT_OF_RANGE
//
// MessageText:
//
// ERROR: The input start frequency is out of the range of the Network Analyzer
//
#define E_AME_INPUT_START_FREQUENCY_OUT_OF_RANGE ((HRESULT)0xE90103C2L)

//
// MessageId: E_AME_INPUT_STOP_FREQUENCY_OUT_OF_RANGE
//
// MessageText:
//
// ERROR: The input stop frequency is out of the range of the Network Analyzer
//
#define E_AME_INPUT_STOP_FREQUENCY_OUT_OF_RANGE ((HRESULT)0xE90103C3L)

//
// MessageId: E_AME_OUTPUT_START_FREQUENCY_OUT_OF_RANGE
//
// MessageText:
//
// ERROR: The output start frequency is out of the range of the Network Analyzer
//
#define E_AME_OUTPUT_START_FREQUENCY_OUT_OF_RANGE ((HRESULT)0xE90103C4L)

//
// MessageId: E_AME_OUTPUT_STOP_FREQUENCY_OUT_OF_RANGE
//
// MessageText:
//
// ERROR: The output stop frequency is out of the range of the Network Analyzer
//
#define E_AME_OUTPUT_STOP_FREQUENCY_OUT_OF_RANGE ((HRESULT)0xE90103C5L)

//
// MessageId: E_AME_COULD_NOT_TRANSLATE_ECAL_PORT_MAPPING_STRING
//
// MessageText:
//
// ERROR: Could not translate the port mapping string for ecal orientation
//
#define E_AME_COULD_NOT_TRANSLATE_ECAL_PORT_MAPPING_STRING ((HRESULT)0xE90103C6L)

//
// MessageId: E_AME_LO_OUT_OF_RANGE
//
// MessageText:
//
// ERROR: The given LO number is out of range. For a one stage mixer, this number must be 1.
// For a two stage mixer, this number can be 1 or 2.
//
#define E_AME_LO_OUT_OF_RANGE            ((HRESULT)0xE90103C7L)

//
// MessageId: E_AME_SET_NUMBER_OF_LOS_FIRST
//
// MessageText:
//
// ERROR: You must set the number of LOs before making this call.
//
#define E_AME_SET_NUMBER_OF_LOS_FIRST    ((HRESULT)0xE90103C8L)

//
// MessageId: E_AME_IF_FREQUENCY_IS_NOT_FIXED
//
// MessageText:
//
// ERROR: Since the start and stop IF frequencies are not the same, the IF frequency is not considered fixed.
//
#define E_AME_IF_FREQUENCY_IS_NOT_FIXED  ((HRESULT)0xE90103C9L)

//
// MessageId: E_AME_INPUT_FREQUENCY_IS_NOT_FIXED
//
// MessageText:
//
// ERROR: Since the start and stop input frequencies are not the same, the input frequency is not considered fixed.
//
#define E_AME_INPUT_FREQUENCY_IS_NOT_FIXED ((HRESULT)0xE90103CAL)

//
// MessageId: E_AME_OUTPUT_FREQUENCY_IS_NOT_FIXED
//
// MessageText:
//
// ERROR: Since the start and stop output frequencies are not the same, the output frequency is not considered fixed.
//
#define E_AME_OUTPUT_FREQUENCY_IS_NOT_FIXED ((HRESULT)0xE90103CBL)

//
// MessageId: E_AME_CALIBRATION_NOT_COMPLETE
//
// MessageText:
//
// ERROR: Calibration incomplete.  Not all of the calibration steps have been acquired.
//
#define E_AME_CALIBRATION_NOT_COMPLETE   ((HRESULT)0xE90103CCL)

//
// MessageId: E_AME_TOO_MANY_POINTS
//
// MessageText:
//
// ERROR: The maximum number of points for a calibration have been exceeded.  The maximum number of points allowed for this calibration is half the maximum number of points in the network analyzer minus one.
//
#define E_AME_TOO_MANY_POINTS            ((HRESULT)0xE90103CDL)

//
// MessageId: E_AME_MEAS_INIT_PARAMS_NOT_PARSED
//
// MessageText:
//
// ERROR: Initialization parameter was not parsed.
//
#define E_AME_MEAS_INIT_PARAMS_NOT_PARSED ((HRESULT)0xE90103CEL)

//
// MessageId: E_AME_MEAS_FAILED_TO_CHANGE_PARAM
//
// MessageText:
//
// ERROR: Failed to changed the parameter.  Restoring previous measurement parameter.
//
#define E_AME_MEAS_FAILED_TO_CHANGE_PARAM ((HRESULT)0xE90103CFL)

//
// MessageId: E_AME_LO_OUTPUT_NO_UPCONVERTER_POSSIBLE
//
// MessageText:
//
// ERROR: It is not possible to calculate an LO frequency to a mixer that can upconvert to that output frequency
//
#define E_AME_LO_OUTPUT_NO_UPCONVERTER_POSSIBLE ((HRESULT)0xE90103D0L)

//
// MessageId: E_AME_LO2_OUTPUT_NO_UPCONVERTER_POSSIBLE
//
// MessageText:
//
// ERROR: It is not possible to calculate an LO2 frequency to a mixer that can upconvert to that output frequency
//
#define E_AME_LO2_OUTPUT_NO_UPCONVERTER_POSSIBLE ((HRESULT)0xE90103D1L)

//
// MessageId: E_AME_INCOMPATIBLE_TRIGGER_MODES
//
// MessageText:
//
// ERROR: FCA does not support having two swept LOs, where one LO is GBIB triggered, and the other is BNC triggered
// The channel will be placed in hold mode.
//
#define E_AME_INCOMPATIBLE_TRIGGER_MODES ((HRESULT)0xE90103D2L)

//
// MessageId: E_AME_SELECTED_MEASUREMENT_IS_NOT_FCA
//
// MessageText:
//
// ERROR: The selected measurement is not an FCA measurement. In order for this SCPI command to function, the selected
// measurement must be an FCA measurement.
//
#define E_AME_SELECTED_MEASUREMENT_IS_NOT_FCA ((HRESULT)0xE90103D3L)

//
// MessageId: E_AME_NOT_A_VALID_MIXER_FILE
//
// MessageText:
//
// ERROR: The selected file is not a valid mixer file.
//
#define E_AME_NOT_A_VALID_MIXER_FILE     ((HRESULT)0xE90103D4L)

//
// MessageId: E_AME_VMC_DOES_NOT_SUPPORT_FIXED_OUTPUT
//
// MessageText:
//
// ERROR: the Vector/Mixer Converter measurement does not support fixed output mode.
//
#define E_AME_VMC_DOES_NOT_SUPPORT_FIXED_OUTPUT ((HRESULT)0xE90103D5L)

//
// MessageId: E_AME_VMC_DOES_NOT_SUPPORT_SWEPT_LO
//
// MessageText:
//
// ERROR: the Vector/Mixer Converter measurement does not support swept lo mode.
//
#define E_AME_VMC_DOES_NOT_SUPPORT_SWEPT_LO ((HRESULT)0xE90103D6L)

//
// MessageId: E_AME_CANT_CALCULATE_FIXED_FREQUENCY
//
// MessageText:
//
// ERROR: The target of a calculate operation is not permitted to have a frequency mode of 'fixed'. It must be 'swept'.
//
#define E_AME_CANT_CALCULATE_FIXED_FREQUENCY ((HRESULT)0xE90103D7L)

//
// MessageId: E_AME_NUMERATOR_AND_DENOMINATOR_MUST_BE_POSITIVE
//
// MessageText:
//
// ERROR: Both the numerator and the denominator are required to be positive values
//
#define E_AME_NUMERATOR_AND_DENOMINATOR_MUST_BE_POSITIVE ((HRESULT)0xE90103D8L)

//
// MessageId: E_AME_NO_VMC_CAL_ON_FIXED_OUTPUT
//
// MessageText:
//
// ERROR: Vector Mixer Cal is not available for fixed frequency output measurements.
// For relative phase measurements with fixed output frequency, use data->memory and data/memory.
//
#define E_AME_NO_VMC_CAL_ON_FIXED_OUTPUT ((HRESULT)0xE90103D9L)

//
// MessageId: E_AME_CANT_INTERPOLATE_CHANGES_IN_LO_FOR_VMC
//
// MessageText:
//
// ERROR: The current LO settings are different than those in the calset. Interpolation of the
// error terms is not available for this condition. Calibration has been turned off
//
#define E_AME_CANT_INTERPOLATE_CHANGES_IN_LO_FOR_VMC ((HRESULT)0xE90103DAL)

//
// MessageId: E_AME_CANT_SAVE_S2P_INVALID_MEAS
//
// MessageText:
//
// ERROR: The current measurement is not supported when saving s2p data.
//
#define E_AME_CANT_SAVE_S2P_INVALID_MEAS ((HRESULT)0xE90103DBL)

//
// MessageId: E_AME_VMC_NOMINIAL_INCIDENT_POWER_UNSUPPORTED
//
// MessageText:
//
// ERROR: Nominal Incident Power is not supported for Vector Mixer measurements.
//
#define E_AME_VMC_NOMINIAL_INCIDENT_POWER_UNSUPPORTED ((HRESULT)0xE90103DCL)

//
// MessageId: E_AME_INVALID_CHANNEL
//
// MessageText:
//
// ERROR: Invalid channel value %1.
//
#define E_AME_INVALID_CHANNEL            ((HRESULT)0xE90103DDL)

//
// MessageId: E_AME_GPIB_ERROR
//
// MessageText:
//
// ERROR: GPIB error, address %1: %2.
//
#define E_AME_GPIB_ERROR                 ((HRESULT)0xE90103DEL)

//
// MessageId: E_AME_INITIALIZATION_ERROR
//
// MessageText:
//
// ERROR: Could not acquire reference to %1.
//
#define E_AME_INITIALIZATION_ERROR       ((HRESULT)0xE90103DFL)

//
// MessageId: E_AME_PORT_WRITE_ERROR
//
// MessageText:
//
// ERROR: Error writing value %1 to port %2: argument is invalid.
//
#define E_AME_PORT_WRITE_ERROR           ((HRESULT)0xE90103E0L)

//
// MessageId: E_AME_IO_ERROR
//
// MessageText:
//
// ERROR: IO error: %1
//
#define E_AME_IO_ERROR                   ((HRESULT)0xE90103E1L)

//
// MessageId: E_AME_CANT_USE_SAME_SOURCE_TWICE
//
// MessageText:
//
// ERROR: One of the other channels is already using this source. That channel is using it under the "%1"
// configuration. To communicate with the GPIB address: %2, "%1" must be chosen instead.
//
#define E_AME_CANT_USE_SAME_SOURCE_TWICE ((HRESULT)0xE90103E2L)

//
// MessageId: E_AME_TESTSET_SWITCHING_ERROR
//
// MessageText:
//
// ERROR: No external testset switching command is available for the measurement "%1".
//
#define E_AME_TESTSET_SWITCHING_ERROR    ((HRESULT)0xE90103E3L)

//
// MessageId: E_AME_INVALID_TESTSET_ID
//
// MessageText:
//
// ERROR: The testset address or ID '%1' is invalid.
//
#define E_AME_INVALID_TESTSET_ID         ((HRESULT)0xE90103E4L)

//
// MessageId: E_AME_TESTSET_CONTROLLINE_ERROR
//
// MessageText:
//
// ERROR: The external testset control lines could not be set on channel %1.
//
#define E_AME_TESTSET_CONTROLLINE_ERROR  ((HRESULT)0xE90103E5L)

//
// MessageId: E_AME_TESTSET_INVALID_TYPE
//
// MessageText:
//
// ERROR: The external testset type '%1' is invalid.
//
#define E_AME_TESTSET_INVALID_TYPE       ((HRESULT)0xE90103E6L)

//
// MessageId: E_AME_NOT_FCA_CHANNEL
//
// MessageText:
//
// ERROR: Channel %1 is not an FCA channel.
//
#define E_AME_NOT_FCA_CHANNEL            ((HRESULT)0xE90103E7L)

//
// MessageId: E_AME_MIXER_NOT_CONFIGURED_CORRECTLY
//
// MessageText:
//
// ERROR: The mixer has not been configured correctly. Use calculate to ensure correct configuration.
//
#define E_AME_MIXER_NOT_CONFIGURED_CORRECTLY ((HRESULT)0xE90103E8L)

//
// MessageId: E_AME_INCOMPATIBLE_TESTSETS
//
// MessageText:
//
// ERROR: The testset types %1 and %2 are incompatible.
//
#define E_AME_INCOMPATIBLE_TESTSETS      ((HRESULT)0xE9010400L)

//
// MessageId: E_AME_INCOMPATIBLE_TESTSET_STATES
//
// MessageText:
//
// ERROR: The testset state is incompatible with the current testset hardware.
//
#define E_AME_INCOMPATIBLE_TESTSET_STATES ((HRESULT)0xE9010401L)

//
// MessageId: E_AME_PORT_POWER_MUST_STAY_COUPLED_IN_FCA
//
// MessageText:
//
// ERROR: FCA only supports coupled port power.
//
#define E_AME_PORT_POWER_MUST_STAY_COUPLED_IN_FCA ((HRESULT)0xE9010402L)

//
// MessageId: E_AME_SWEEP_IS_ALWAYS_STEPPED_IN_FCA
//
// MessageText:
//
// ERROR: FCA only supports stepped sweep
//
#define E_AME_SWEEP_IS_ALWAYS_STEPPED_IN_FCA ((HRESULT)0xE9010403L)

//
// MessageId: E_AME_INCOMPATIBLE_TESTSET_VERSION
//
// MessageText:
//
// ERROR: Testset file version is not supported by this firmware.
//
#define E_AME_INCOMPATIBLE_TESTSET_VERSION ((HRESULT)0xE9010404L)

//
// MessageId: E_AME_LO_CAL_FILE_NOT_FOUND
//
// MessageText:
//
// ERROR: The LO cal file was not found. %1
//
#define E_AME_LO_CAL_FILE_NOT_FOUND      ((HRESULT)0xE9010405L)

//
// MessageId: E_AME_TESTSET_MISSING
//
// MessageText:
//
// ERROR: No external testset was found. Restarting the PNA in 2-port mode.
//
#define E_AME_TESTSET_MISSING            ((HRESULT)0xE9010406L)

//
// MessageId: E_AME_INVALID_RANGE_MODE
//
// MessageText:
//
// ERROR: Invalid range mode argument. Must be either mixSwept(0) or mixFixed(1)
//
#define E_AME_INVALID_RANGE_MODE         ((HRESULT)0xE9010407L)

//
// MessageId: E_AME_FORBIDDEN_IN_MULTIPORT
//
// MessageText:
//
// ERROR: The requested operation is not allowed in Multiport mode.
//
#define E_AME_FORBIDDEN_IN_MULTIPORT     ((HRESULT)0xE9010408L)

//
// MessageId: E_AME_LO_START_FREQUENCY_OUT_OF_RANGE
//
// MessageText:
//
// ERROR: The lo start frequency is out of range.
//
#define E_AME_LO_START_FREQUENCY_OUT_OF_RANGE ((HRESULT)0xE9010409L)

//
// MessageId: E_AME_LO_STOP_FREQUENCY_OUT_OF_RANGE
//
// MessageText:
//
// ERROR: The lo stop frequency is out of range.
//
#define E_AME_LO_STOP_FREQUENCY_OUT_OF_RANGE ((HRESULT)0xE901040AL)

//
// MessageId: E_AME_CANT_USE_TWO_INTERNAL_LOS
//
// MessageText:
//
// ERROR: The internal 2nd source can not be used for both of the LOs.
//
#define E_AME_CANT_USE_TWO_INTERNAL_LOS  ((HRESULT)0xE901040BL)

//
// MessageId: E_AME_MULTIPORT_SWEEP_COMPUTATION_ERROR
//
// MessageText:
//
// ERROR: An error has occurred in computing sweep lists.
//
#define E_AME_MULTIPORT_SWEEP_COMPUTATION_ERROR ((HRESULT)0xE901040CL)

//
// MessageId: E_AME_TESTSET_PORT_CONFLICT
//
// MessageText:
//
// ERROR: The specified port mapping is invalid.
//
#define E_AME_TESTSET_PORT_CONFLICT      ((HRESULT)0xE901040DL)

//
// MessageId: E_NA_TESTSET_COMMAND_UNSUPPORTED
//
// MessageText:
//
// ERROR: This testset model does not support this command.
//
#define E_NA_TESTSET_COMMAND_UNSUPPORTED ((HRESULT)0xE901040EL)

//
// MessageId: E_AME_FCA_DOES_NOT_SUPPORT_MULTIPORT
//
// MessageText:
//
// ERROR: FCA measurements may not be created in mulitport mode. Disable multiport before using FCA
//
#define E_AME_FCA_DOES_NOT_SUPPORT_MULTIPORT ((HRESULT)0xE901040FL)

//
// MessageId: E_AME_SWEEP_IS_ALWAYS_STEPPED_IN_NFIG
//
// MessageText:
//
// ERROR: Noise measurements require stepped sweep.
//
#define E_AME_SWEEP_IS_ALWAYS_STEPPED_IN_NFIG ((HRESULT)0xE9010410L)

//
// MessageId: E_AME_EMBEDDED_LO_REQUIRES_CONTROLLED_REFERENCE_LO
//
// MessageText:
//
// ERROR: To turn on embedded LO, you must specify a controlled LO in the mixer setup control. That LO should be used 
// as the LO for the reference mixer,
//
#define E_AME_EMBEDDED_LO_REQUIRES_CONTROLLED_REFERENCE_LO ((HRESULT)0xE9010411L)

//
// MessageId: E_AME_FCA_DOES_NOT_SUPPORT_SPARAMETER_EXTERNAL_SOURCES
//
// MessageText:
//
// ERROR: FCA measurements may not be created when external sources are selected for SParameter channels. Deselect external sources before launching FCA.
//
#define E_AME_FCA_DOES_NOT_SUPPORT_SPARAMETER_EXTERNAL_SOURCES ((HRESULT)0xE9010412L)

//
// MessageId: E_AME_NOISE_TUNER_NOT_FOUND
//
// MessageText:
//
// ERROR: The noise tuner could not be identified, %1.
//
#define E_AME_NOISE_TUNER_NOT_FOUND      ((HRESULT)0xE9010413L)

//
// MessageId: E_AME_MISSING_ENR_DATA
//
// MessageText:
//
// ERROR: Noise calibration requires ENR data.
//
#define E_AME_MISSING_ENR_DATA           ((HRESULT)0xE9010414L)

//
// MessageId: E_AME_CALIBRATION_DATA_MISSING
//
// MessageText:
//
// ERROR: Internal Error. Correction cannot be computed, data missing.
//
#define E_AME_CALIBRATION_DATA_MISSING   ((HRESULT)0xE9010415L)

//
// MessageId: E_AME_MISSING_TUNER_CODES
//
// MessageText:
//
// ERROR:  ECal codes for model %1 are missing.
//
#define E_AME_MISSING_TUNER_CODES        ((HRESULT)0xE9010416L)

//
// MessageId: E_AME_FAILED_TO_HIT_TARGET_POWER
//
// MessageText:
//
// ERROR:  Could not achieve target power.
//
#define E_AME_FAILED_TO_HIT_TARGET_POWER ((HRESULT)0xE9010417L)

//
// MessageId: E_AME_NOT_RECALLABLE
//
// MessageText:
//
// ERROR:  The state contains a measurement that cannot be recalled, %1.
//
#define E_AME_NOT_RECALLABLE             ((HRESULT)0xE9010418L)

//
// MessageId: E_AME_INVALID_PORT_SELECTED
//
// MessageText:
//
// ERROR:  The port selected is invalid.
//
#define E_AME_INVALID_PORT_SELECTED      ((HRESULT)0xE9010419L)

//
// MessageId: E_AME_NO_GC_DATA
//
// MessageText:
//
// ERROR: No gain compression 2D data.  Please verify that the channel has compression parameters and is sweeping. 
//
#define E_AME_NO_GC_DATA                 ((HRESULT)0xE901041AL)

//
// MessageId: E_AME_ALL_SWEPT_INVALID
//
// MessageText:
//
// ERROR: It is not valid to setup a mixer with all the ranges as swept. Change one of the ranges to fixed.
//
#define E_AME_ALL_SWEPT_INVALID          ((HRESULT)0xE901041BL)

//
// MessageId: E_AME_SAME_SOURCE_ERROR
//
// MessageText:
//
// ERROR: RF source and LO source cannot be the same.
//
#define E_AME_SAME_SOURCE_ERROR          ((HRESULT)0xE901041CL)

//
// MessageId: E_AME_PORT_MAPPING_ERROR
//
// MessageText:
//
// ERROR: External or embedded LO required for port mapping.
//
#define E_AME_PORT_MAPPING_ERROR         ((HRESULT)0xE901041DL)

//
// MessageId: E_AME_PMAR_CONFIGURATION_WAS_NOT_FOUND
//
// MessageText:
//
// ERROR:  Specified external PMAR was not found.  %1
//
#define E_AME_PMAR_CONFIGURATION_WAS_NOT_FOUND ((HRESULT)0xE901041EL)

//
// MessageId: E_AME_DEVICE_CONFIGURATION_WAS_NOT_FOUND
//
// MessageText:
//
// ERROR:  Specified external device was not found.  %1
//
#define E_AME_DEVICE_CONFIGURATION_WAS_NOT_FOUND ((HRESULT)0xE901041FL)

//
// MessageId: E_AME_PMAR_NAME_CONFLICT_WITH_OTHER_MEAS
//
// MessageText:
//
// ERROR:  Specified PMAR name conflicts with existing measurement parameter name %1.
//
#define E_AME_PMAR_NAME_CONFLICT_WITH_OTHER_MEAS ((HRESULT)0xE9010420L)

//
// MessageId: E_AME_NOISE_PULLER_NOT_FOUND
//
// MessageText:
//
// ERROR:  The identify of the ecal used for noise pulling is ambiguous, %1. You may need to supply a serial number.
//
#define E_AME_NOISE_PULLER_NOT_FOUND     ((HRESULT)0xE9010421L)

//
// MessageId: E_AME_DEVICE_INVALID_IO_CONFIG
//
// MessageText:
//
// ERROR:  %1's I/O Configuration %2 is invalid.
//
#define E_AME_DEVICE_INVALID_IO_CONFIG   ((HRESULT)0xE9010422L)

//
// MessageId: E_AME_DEVICE_INVALID_TYPE_CONFIG
//
// MessageText:
//
// ERROR:  %1's device type %2 is invalid.
//
#define E_AME_DEVICE_INVALID_TYPE_CONFIG ((HRESULT)0xE9010423L)

//
// MessageId: E_AME_INCONSISTENT_INPUT_SWEEP_DIRECTION
//
// MessageText:
//
// ERROR: The segment input frequency ranges are not sweeping in the same direction.
//
#define E_AME_INCONSISTENT_INPUT_SWEEP_DIRECTION ((HRESULT)0xE9010424L)

//
// MessageId: E_AME_INCONSISTENT_OUTPUT_SWEEP_DIRECTION
//
// MessageText:
//
// ERROR: The segment output frequency ranges are not sweeping in the same direction.
//
#define E_AME_INCONSISTENT_OUTPUT_SWEEP_DIRECTION ((HRESULT)0xE9010425L)

//
// MessageId: E_AME_ALL_SEGMENTS_OFF
//
// MessageText:
//
// Error: At least one segment needs to be ON.
//
#define E_AME_ALL_SEGMENTS_OFF           ((HRESULT)0xE9010426L)

//
// MessageId: E_AME_IMD_CAL_INIT_FAILURE
//
// MessageText:
//
// Error: Calibration cannot start.  One of the tones is undefined. 
//
#define E_AME_IMD_CAL_INIT_FAILURE       ((HRESULT)0xE9010427L)

//
// MessageId: E_AME_USE_CONVERTER_INTERFACE
//
// MessageText:
//
// Error: Use the converter interface for accessing roles in converter applications.
//
#define E_AME_USE_CONVERTER_INTERFACE    ((HRESULT)0xE9010428L)

//
// MessageId: E_AME_CANNOT_IMPORT_POWER_WITHOUT_PHASE
//
// MessageText:
//
// Error: Importing the power is not supported when the phase measurement is enabled
//
#define E_AME_CANNOT_IMPORT_POWER_WITHOUT_PHASE ((HRESULT)0xE9010429L)

//
// MessageId: E_AME_PULSE_CONFIGURATION_WAS_NOT_FOUND
//
// MessageText:
//
// ERROR:  Specified external pulse generator was not found.  %1
//
#define E_AME_PULSE_CONFIGURATION_WAS_NOT_FOUND ((HRESULT)0xE901042AL)

//
// MessageId: E_AME_DC_SRC_CONFIGURATION_WAS_NOT_FOUND
//
// MessageText:
//
// ERROR:  Specified external DC source was not found.  %1
//
#define E_AME_DC_SRC_CONFIGURATION_WAS_NOT_FOUND ((HRESULT)0xE901042BL)

//
// MessageId: E_AME_DC_MTR_CONFIGURATION_WAS_NOT_FOUND
//
// MessageText:
//
// ERROR:  Specified external DC meter was not found.  %1
//
#define E_AME_DC_MTR_CONFIGURATION_WAS_NOT_FOUND ((HRESULT)0xE901042CL)

//
// MessageId: E_AME_POWER_METER_NOISE_CAL_NOT_ALLOWED
//
// MessageText:
//
// ERROR: Power meter receiver characterization cannot be used with the selected noise bandwidth.
//
#define E_AME_POWER_METER_NOISE_CAL_NOT_ALLOWED ((HRESULT)0xE901042DL)

//
// MessageId: E_AME_LO_FREQUENCY_OUT_OF_RANGE
//
// MessageText:
//
// ERROR: The lo frequency is out of range.
//
#define E_AME_LO_FREQUENCY_OUT_OF_RANGE  ((HRESULT)0xE901042EL)

//
// MessageId: E_AME_SMU_CONFIGURATION_WAS_NOT_FOUND
//
// MessageText:
//
// ERROR:  Specified external SMU was not found.  %1
//
#define E_AME_SMU_CONFIGURATION_WAS_NOT_FOUND ((HRESULT)0xE901042FL)

//
// MessageId: E_LOAD_XML_FILE_FAIL
//
// MessageText:
//
// ERROR:  The specified XML file is not loaded. Please ensure the filename is correct or the device type is matched.
//
#define E_LOAD_XML_FILE_FAIL             ((HRESULT)0xE9010430L)

//
// MessageId: E_SAVE_XML_FILE_FAIL
//
// MessageText:
//
// ERROR:  The specified XML file is not saved.
//
#define E_SAVE_XML_FILE_FAIL             ((HRESULT)0xE9010431L)

//
// MessageId: E_AME_NARROWBAND_NF_NOT_AVAILABLE
//
// MessageText:
//
// ERROR:  Narrowband noise compensation is not available for noise bandwidths greater than 4 MHz.
//
#define E_AME_NARROWBAND_NF_NOT_AVAILABLE ((HRESULT)0xE9010432L)

//
// MessageId: E_AME_NOT_MIXER_CHANNEL
//
// MessageText:
//
// ERROR:  Channel is not a mixer channel.
//
#define E_AME_NOT_MIXER_CHANNEL          ((HRESULT)0xE9010433L)

//
// MessageId: E_AME_MILIMETER_MODE_NOT_SUPPORTED
//
// MessageText:
//
// ERROR:  This measurement class doesn't support millimeter configuration currently.
//
#define E_AME_MILIMETER_MODE_NOT_SUPPORTED ((HRESULT)0xE9010434L)

//
// MessageId: E_AME_IMS_TRACKING_NOT_ENABLED
//
// MessageText:
//
// ERROR:  IMD channel tracking not enabled.
//
#define E_AME_IMS_TRACKING_NOT_ENABLED   ((HRESULT)0xE9010435L)

//
// MessageId: E_AME_SMC_PHASE_NOT_COMPATIBLE_WITH_LFE
//
// MessageText:
//
// ERROR:  Phase has been disabled because it is not compatible with low frequency extensions.
//
#define E_AME_SMC_PHASE_NOT_COMPATIBLE_WITH_LFE ((HRESULT)0xE9010436L)

//
// MessageId: MSG_AME_SA_FREQUENCY_TUNER_COMPLETE
//
// MessageText:
//
// SA app frequency tuner completed.
//
#define MSG_AME_SA_FREQUENCY_TUNER_COMPLETE ((HRESULT)0x69010437L)

