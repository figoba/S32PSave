VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "PowerMeter"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
'---------------------------------------------------------------------
' File:
'   PowerMeter.cls
'
' Description:
'   This Visual Basic 6.0 class module is a template for people who
'   have a power meter currently not supported by Source Power Cal on
'   Agilent PNA Network Analyzers, who wish to write a software driver
'   for their power meter which will allow PNA source power cal to use
'   that meter.  The Help system onboard the PNA describes in detail
'   how to write a PNA power meter driver using this template file.
'---------------------------------------------------------------------

'!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
' Please be aware that PNA source power cal is designed to catch and
' display errors that are reported by your driver (particularly those
' produced using the Err.Raise method).  So you should limit your use
' of "On Error" error handlers within your driver, and don't forget to
' use "On Error GoTo 0" to turn off your error handlers.
'!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

Option Explicit
Option Base 0
                        
' For cases where you might wish to test this driver from within the
' Visual Basic development environment of another project, this boolean
' is provided to allow control of whether the driver will print debug
' messages to the Visual Basic 'Immediate' window.  See the
' getVISAerror function below as an example of how this is used.
Const bDEBUG_MODE As Boolean = True

' Implements the COM interface defined for PNA usage.  This also makes
' available constants defined in the IPowerMeter type library file:
' pmOff, pmOn, pmSuccess, pmFailure, pmInputError, pmdBm and pmWatts
Implements IPowerMeter

' *****************  PRIVATE MEMBER VARIABLES ******************

Private m_hRsrcMgr As ViSession        ' handle to the VISA Resource Manager
Private m_hSession As ViSession        ' handle to the VISA session with the power meter
Private m_strVisaDescriptor As String  ' VISA I/O descriptor used for opening the session
Private m_strID As String              ' ID string read from the power meter
Private m_strErrorSource As String     ' when an error occurs, describes where the error occurred
Private m_lSensor As Long              ' the currently selected power sensor
Private m_lMaxSensor As Long           ' the number of sensor channels the power meter has
Private m_bFixedDelay As Boolean       ' indicates if IPowerMeter_FixedDelay is currently ON or OFF

' ******************   CONSTANTS  ********************************

Const iMAXSTRING As Long = 256         ' Used for sizing fixed-length strings created within this driver
Const sCMD_IDN As String = "*IDN?"     ' IEEE 488 command for querying instrument IDs

' Default VISA locator string, when searching for power meters supported by this driver.
Const sRESOURCELOCATOR As String = "(GPIB)?*INSTR"

' Minimum timeout (milliseconds) for driver functions
Const m_MINIMUM_TIMEOUT As Long = 3000

' Most if not all power meters offer a "Trigger with delay" function.  This consists of
' the power meter delaying after receiving a trigger before taking the power reading,
' attempting to improve accuracy by allowing sufficient time for the power meter's analog
' circuitry and digital filters to settle.  The delay is calculated by the power meter as
' a function of the current filter (averaging) setting on the meter.
'
' As used with the PNA, this driver will also need to support an alternative mode of
' operation where the delay between the trigger and the power reading is handled by the
' driver rather than by the power meter.  This mode is only used by the PNA in certain cases
' where the power meter averaging factor is 1 (i.e., no filtering), and meters which support
' auto power ranging are in auto power range mode.  For your driver, you should assign this
' delay value (m_FIXED_DELAY) based upon the difference in time it takes to read from
' the meter after triggering in "trigger immediate" mode versus the meter's built-in
' "trigger with delay" mode.  Add to that any additional delay you encounter if you put your
' meter in auto power range mode.
' For example, let's say this sample value of 10 came from:
'      In "trigger immediate" mode with auto power range mode off, took 25 milliseconds to
'      receive data over GPIB after trigger.
'      In "trigger with delay" mode with auto power range mode on, took 35 milliseconds to
'      receive data over GPIB after trigger.
'      m_FIXED_DELAY = 35 - 25 = 10
Const m_FIXED_DELAY As Long = 10


' Sub stripTermCharsFromString
'   Inputs :
'       strModify is a string that was read from the power meter.
'       It may be terminated in carriage return and linefeed characters,
'       or perhaps linefeed only.  This subroutine can also be called when
'       there is no termination character because the power meter uses the
'       EOI line on the GPIB bus instead.  But in that case, this subroutine
'       actually does nothing.
'   Outputs:
'       strModify with the termination characters replaced by whitespace
'   Description:
'       Helper function used by functions in this driver that read from
'       the meter.
'---------------------------------------------------------------------------
Private Sub stripTermCharsFromString(strModify As String)
    Dim iTermCharPosn As Integer
    
    iTermCharPosn = InStrRev(strModify, Chr(13))
    If iTermCharPosn = 0 Then ' perhaps linefeed only
        iTermCharPosn = InStrRev(strModify, Chr(10))
        If iTermCharPosn = 0 Then Exit Sub ' no CR or LF, so just return
    End If
    
    strModify = Left(strModify, iTermCharPosn - 1)
End Sub

' Function getVISAerror
'   Inputs : errNum is VISA error number to translate.
'   Outputs: Returns string containing error message related to errNum.
'   Description:
'       Gets the VISA error message string associated with a VISA
'       error number.
'-------------------------------------------------------------------------
Private Function getVISAerror(ByVal errNum As Long) As String
      Dim errStat As ViStatus
      Dim errMsg As String
      
      errMsg = Space(iMAXSTRING)
      errStat = viStatusDesc(m_hSession, errNum, errMsg)
      If bDEBUG_MODE Then Debug.Print "VISA error: ", errMsg
      
      getVISAerror = errMsg
End Function

' Subroutine Class_Initialize
'   Inputs :  none
'   Outputs:  none
'   Description:
'       Initialize class member variables here.
'-------------------------------------------------------------------------
Private Sub Class_Initialize()
    m_lSensor = 1               ' default to sensor 1 (sensor A)
    m_hRsrcMgr = VI_NULL
    m_hSession = VI_NULL
    m_strVisaDescriptor = vbEmpty
    m_strID = vbEmpty
    m_strErrorSource = vbEmpty
    m_lMaxSensor = 1
    m_bFixedDelay = False
End Sub

' Subroutine Class_Terminate
'   Inputs : none
'   Outputs: none
'   Description:
'       Releases the handles to the VISA session and VISA resource manager.
'-------------------------------------------------------------------------
Private Sub Class_Terminate()
    viClose (m_hSession)
    viClose (m_hRsrcMgr)
End Sub
 
' Property Let: AutoDelay
'   Inputs : mode is pmOn or pmOff
'   Outputs: none
'   Description:
'       Toggles the use of an auto settling time by the power meter.
'       This is as opposed to using the FixedDelay feature of this driver.
'       AutoDelay and FixedDelay are alternate ways of allowing time for the
'       power meter to reach a steady-state condition before each power
'       reading is taken.
'-------------------------------------------------------------------------
Private Property Let IPowerMeter_AutoDelay(ByVal mode As Boolean)
    ' Your code here
    If IPowerMeter_AutoDelay = True Then IPowerMeter_FixedDelay = False
End Property

' Property Get: Autodelay
'   Inputs : none
'   Outputs: returns the state of the AutoDelay feature
'   Description:
'       Auto Delay ON means the power meter is waiting for internal
'       filters and amplifiers to settle before allowing the measurement.
'-------------------------------------------------------------------------
Private Property Get IPowerMeter_AutoDelay() As Boolean
    ' Your code here
End Property

' Property Let: Averaging
'   Inputs : mode is pmOn or pmOff
'   Outputs: none
'   Description:
'       Sets the averaging mode on or off for the current channel (sensor).
'-------------------------------------------------------------------------
Private Property Let IPowerMeter_Averaging(ByVal mode As Boolean)
    ' Your code here
End Property

' Property Get: Averaging
'   Inputs : none
'   Outputs: pmOn or pmOff
'   Description:
'       Returns the current sensor's averaging state.
'-------------------------------------------------------
Private Property Get IPowerMeter_Averaging() As Boolean
    ' Your code here
End Property

' Property Let:  AveragingFactor
'   Inputs : numAvgs is the requested number of averages
'   Outputs: none
'   Description:
'       Sets the averaging factor for the current channel (sensor) to
'       whichever supported value is nearest to the requested value.
'----------------------------------------------------------------------
Private Property Let IPowerMeter_AveragingFactor(ByVal numAvgs As Long)
    ' Your code here
End Property

' Property Get: AveragingFactor
'   Inputs : none
'   Outputs: Returns the averaging factor for the current sensor.
'   Description:
'----------------------------------------------------------------------
Private Property Get IPowerMeter_AveragingFactor() As Long
    ' Your code here
End Property

' Property Let: CalFactor
'   Inputs : Calibration factor (in percent) for the current sensor,
'            by which the power meter will adjust its power readings.
'   Outputs: none
'   Description:
'--------------------------------------------------------------------
Private Property Let IPowerMeter_CalFactor(ByVal dCalFactor As Double)
    ' Your code here
End Property

' Property Get: CalFactor
'   Inputs : none
'   Outputs: cal factor (percent) associated with the current sensor.
'   Description:
'--------------------------------------------------------------------
Private Property Get IPowerMeter_CalFactor() As Double
    ' Your code here
End Property

' Subroutine Calibrate
'   Inputs : none
'   Outputs: none
'   Description:
'       Initiates a calibration of the current sensor using the
'       power meter's reference port.
'--------------------------------------------------------------------
Private Sub IPowerMeter_Calibrate()
    ' Your code here
End Sub

' Subroutine ClearErrors
'   Inputs : none
'   Outputs: none
'   Description:
'       Clears the power meter error queue.  The alternative method
'       of clearing the queue is to call ReportErrors until the
'       returned error number is 0.
'--------------------------------------------------------------------
Private Sub IPowerMeter_ClearErrors()
    ' Your code here
End Sub

' Function Connect
'   Inputs:
'        strLocator    (optional): Overrides the default VISA locator string.
'                                  Has the form: GPIB0::13:INSTR
'                                  Can embed regular expressions. See VISA Help.
'        strIdentifiers(optional): Substrings (delimited by semicolons) to search for
'                                  within the returned *IDN string that let us
'                                  know we have a found a power meter supported
'                                  by this driver.  Overrides the default
'                                  (sIDSEARCH) defined in this driver.
'        bSearch       (optional): Indicates whether or not to do a VISA I/O search
'                                  for the power meter.  If strLocator includes a
'                                  specific address (e.g., 13 in "GPIB0::13:INSTR"),
'                                  then there is of course no need to search.
'   Outputs:
'        Returns pmSuccess (0) or pmFailure (-1).
'
'   Description:
'       Establishes a VISA session with the power meter.  If requested to,
'       will first search I/O busses supported by VISA to find the power meter
'       supported by this driver.  If no strLocator is passed to this routine,
'       the default will search only ports on the machine where this driver is
'       running that are defined as VISA GPIB, no serial ports (RS232 or RS422).
'---------------------------------------------------------------------------------
Private Function IPowerMeter_Connect(Optional ByVal strLocator As String, Optional ByVal strIdentifiers As String, Optional ByVal bSearch As Boolean = True) As Boolean
   
   Dim hSession As ViSession        ' handle to local instrument session
   Dim hList As ViFindList          ' handle to a list
   Dim iCount As ViUInt32           ' count of instruments found
   Dim sInstrDescriptor As String   ' description of instrument
   Dim iChars As ViUInt32
   Dim iLen As ViUInt32
   Dim lStat As ViUInt32
   Dim functionStatus As ViUInt32
   Dim strRsrcPattern As String
   Dim strIDPattern As String

   ' Initialize string to be thrown as "Source" field of Err objects
   m_strErrorSource = "Error in Connect() method of power meter driver"
   
   functionStatus = pmFailure                ' init returned value to failure
   
   On Error GoTo 0
   
   sInstrDescriptor = Space(iMAXSTRING)      ' init string length
   lStat = viOpenDefaultRM(m_hRsrcMgr)       ' start a session with the VISA DLL
   If (lStat <> VI_SUCCESS) Then
      Call Err.Raise(lStat, m_strErrorSource, getVISAerror(lStat))
      GoTo ERRORRAISED
   End If
     
   If IsMissing(strLocator) Or Len(strLocator) = 0 Then
      strRsrcPattern = sRESOURCELOCATOR      ' the default search string
   Else
      strRsrcPattern = strLocator            ' use the locator string passed in by the user
   End If
      
   If bSearch = True Then
      If bDEBUG_MODE Then Debug.Print "Searching Resource: ", strRsrcPattern
   
      ' Do VISA search of the specified I/O ports for instruments
      lStat = viFindRsrc(m_hRsrcMgr, strRsrcPattern, hList, iCount, sInstrDescriptor)
      If (lStat <> VI_SUCCESS) Then
         Call Err.Raise(lStat, m_strErrorSource, getVISAerror(lStat))
         GoTo ERRORRAISED
      End If
   
      If bDEBUG_MODE Then Debug.Print "Found ", iCount, " resources"
   Else
      iCount = 1
      sInstrDescriptor = strRsrcPattern
   End If
   
   If IsMissing(strIdentifiers) Or Len(strIdentifiers) = 0 Then
     strIDPattern = sIDSEARCH               ' default IDs we are looking for
   Else
     strIDPattern = strIdentifiers          ' ID strings sent in by client
   End If
   
   If bDEBUG_MODE Then Debug.Print "Searching for ID:  ", strIDPattern
   
   ' slice the search patterns up into an array to make the search easier
   Dim strModelNums() As String
   Call getSemicolonDelimitedStrings(strIDPattern, strModelNums)
   
   iLen = Len(sCMD_IDN)
   
   ' Temporarily activate this error handler, so that we won't stop if we timeout
   ' while looping through the instrument list, but will keep looking for the target.
   On Error GoTo LOOPERROR
   
   ' search the resource list for a supported power meter
   Do While (iCount)
        ' initiate a session with the specific instrument
        lStat = viOpen(m_hRsrcMgr, sInstrDescriptor, VI_NULL, VI_NULL, hSession)
        If bDEBUG_MODE Then Debug.Print "Opened: ", vbCrLf, sInstrDescriptor
        
        If (lStat >= VI_SUCCESS) Then
            ' request the ID string
            m_strID = Space(iMAXSTRING)
            
            lStat = viWrite(hSession, sCMD_IDN, iLen, iChars)
            If (lStat <> VI_SUCCESS) Then
               Call Err.Raise(lStat, m_strErrorSource, getVISAerror(lStat))
            End If
            
            lStat = viRead(hSession, m_strID, iMAXSTRING, iChars)
            If (lStat <> VI_SUCCESS) Then
               Call Err.Raise(lStat, m_strErrorSource, getVISAerror(lStat))
            End If
            stripTermCharsFromString m_strID
            
            If bDEBUG_MODE Then Debug.Print "Returned ID string: ", vbCrLf, m_strID
            
            ' if this is a supported meter, save the session information
            ' for use in subsequent driver calls.
            
            Dim found As Boolean
            Dim loopInt As Integer
            found = 0
            loopInt = 0
            
            Do While Not found And loopInt <= UBound(strModelNums)
             found = InStr(1, m_strID, strModelNums(loopInt))
             loopInt = loopInt + 1
            Loop
           
            If found <> 0 Then
                ' power meter found is supported by this driver
                m_strVisaDescriptor = sInstrDescriptor
                m_hSession = hSession
                ' If some of your power meters have more than one sensor channel,
                ' this is where you will want to set the value of m_lMaxSensor.
                ' For example, Agilent E4417 and E4419 have two channels:
                '    If InStr(m_strID, "E4417") Then m_lMaxSensor = 2
                '    If InStr(m_strID, "E4419") Then m_lMaxSensor = 2
                ' Your code here.
                functionStatus = pmSuccess
                Exit Do
            End If
            
            viClose (hSession)
        End If
        
LOOPERROR:
        iCount = iCount - 1
        lStat = viFindNext(hList, sInstrDescriptor)
   Loop
   
   ' Reset error handling so errors will propagate through to the client application
   On Error GoTo 0
   
   ' if we found the meter, then set timeout and do preset
   If functionStatus = pmSuccess Then
       ' set the default timeout, though timeout will vary with gpib interfaces
       lStat = viSetAttribute(m_hSession, VI_ATTR_TMO_VALUE, m_MINIMUM_TIMEOUT)
       If lStat <> VI_SUCCESS Then
           functionStatus = pmFailure
           Call Err.Raise(lStat, m_strErrorSource, getVISAerror(lStat))
           GoTo ERRORRAISED
       End If
       IPowerMeter_Preset
   End If
   
FUNCTIONEXIT:  '  single exit point
   IPowerMeter_Connect = functionStatus
   Exit Function
   
ERRORRAISED:
    If bDEBUG_MODE Then Debug.Print "returned", Err.Number, Err.Description
    GoTo FUNCTIONEXIT
End Function
' ---------------------------------------------------------------
' close and release the VISA resources
'----------------------------------------------------------------
Private Sub IPowerMeter_CloseConnection()
  Class_Terminate
  m_lSensor = 1               ' default to sensor 1 (sensor A)
  m_hRsrcMgr = VI_NULL
  m_hSession = VI_NULL
  m_strVisaDescriptor = vbEmpty
  m_strID = vbEmpty
  m_strErrorSource = vbEmpty
  m_lMaxSensor = 1
  m_bFixedDelay = False
End Sub

' Property Let: ContinuousTrigger
'   Inputs :
'       mode is pmOn or pmOff
'   Outputs:
'       none
'   Description:
'       pmOn puts the meter in a continuous measurement mode.
'       pmOff puts the meter in an idle state.
'---------------------------------------------------------------
Private Property Let IPowerMeter_ContinuousTrigger(ByVal mode As Boolean)
    ' Your code here
End Property

' Property Get: ContinuousTrigger
'   Inputs : none
'   Outputs: returns True if trigger is continuous, else False
'   Description:
'---------------------------------------------------------------
Private Property Get IPowerMeter_ContinuousTrigger() As Boolean
    ' Your code here
End Property

' Property Let: CurrentSensor
'   Inputs :
'       sensorNum is the sensor number which will become the selected sensor
'   Outputs:
'       none
'   Description:
'       This property determines which channel (sensor) is acted upon
'       by the majority of the power meter methods.  When a measurement
'       is made, or the measurement configuration is modified, it is the
'       CurrentSensor channel that is used.
'--------------------------------------------------------------------------
Private Property Let IPowerMeter_CurrentSensor(ByVal sensorNum As Long)
    ' Initialize string to be thrown as "Source" field of Err objects
    m_strErrorSource = "Error in CurrentSensor property of power meter driver"
   
    If sensorNum > 0 And sensorNum <= m_lMaxSensor Then
        m_lSensor = sensorNum
        ' Perhaps send a command to power meter here if necessary for your meter.
        ' Your code here
    Else
        Call Err.Raise(pmInputError, m_strErrorSource, "Specified sensor number not valid")
    End If
End Property

' Property Get: CurrentSensor
'   Inputs : none
'   Outputs: returns the current sensor being used
'   Description:
'--------------------------------------------------------------------------
Private Property Get IPowerMeter_CurrentSensor() As Long
    IPowerMeter_CurrentSensor = m_lSensor
End Property

' Property Let: FixedDelay
'   Inputs :
'       mode - pmOn or pmOff
'   Outputs:
'       none
'   Description:
'       Toggles the use of the fixed settling time specified by the
'       m_FIXED_DELAY constant in this driver.
'--------------------------------------------------------------------------
Private Property Let IPowerMeter_FixedDelay(ByVal mode As Boolean)
    If mode = True And IPowerMeter_AutoDelay = True Then
        IPowerMeter_AutoDelay = False
    End If
    m_bFixedDelay = mode
End Property

' Property Get: FixedDelay
'   Inputs : none
'   Outputs: returns the state of the FixedDelay feature of this driver
'   Description:
'       FixedDelay ON means that IPowerMeter_ReadMeter will wait until the
'       fixed settling time specified within this driver has elapsed before
'       performing a power reading.
'--------------------------------------------------------------------------
Private Property Get IPowerMeter_FixedDelay() As Boolean
    IPowerMeter_FixedDelay = m_bFixedDelay
End Property

' Property Get: IDString
'   Inputs : none
'   Outputs: IEEE 488.2 ID string of the power meter
'   Description:
'       The ID string is queried and stored during IPowerMeter_Connect
'--------------------------------------------------------------------------
Private Property Get IPowerMeter_IDString() As String
    IPowerMeter_IDString = m_strID
End Property

' Function IsSensorAttached
'   Inputs : sensor to be checked
'   Outputs: boolean (True if sensor is connected to the power meter, False if not)
'   Description: Queries the power meter as to whether the sensor is
'                attached to it.  If your power meter does not have that
'                capability, simply have this function always return True.
'--------------------------------------------------------------------------
Private Function IPowerMeter_IsSensorAttached(ByVal sensorNum As Long) As Boolean
    ' Your code here
End Function

' Property Get: MaximumSensorNumber
'   Inputs : none
'   Outputs: returns the number of channels the power meter has
'   Description:
'--------------------------------------------------------------------------
Private Property Get IPowerMeter_MaximumSensorNumber() As Long
    IPowerMeter_MaximumSensorNumber = m_lMaxSensor
End Property

' Subroutine Preset
'   Inputs : none
'   Outputs: none
'   Description:
'       This method should put your power meter into this specific condition:
'           - absolute (not relative) power measurements
'           - IPowerMeter_CurrentSensor = 1 (channel A)
'           - filter (averaging) = Auto
'           - power ranging = Auto (if your meter supports that)
'           - IPowerMeter_ContinuousTrigger = False (trigger hold mode)
'           - measurement units = dBm
'           - IPowerMeter_AutoDelay = True (pmOn)
'           - IPowerMeter_ReferenceCalFactor = 100 (percent)
'           - IPowerMeter_CalFactor = 100 (percent)
'       So you may need to send additional commands to your power meter besides
'       it's preset command to put the meter into this state.
'
' Note: IPowerMeter_Connect also calls this subroutine
' -------------------------------------------------------------------------------
Private Sub IPowerMeter_Preset()
    IPowerMeter_CurrentSensor = 1
    ' Your code here
End Sub

' Function QueryMeter
'   Inputs :
'       command = A query command string to be sent to your power meter.
'                 For example, "*IDN?" or "SYST:ERR?"
'       msg     = String to receive the response from the power meter.
'   Outputs:
'       Returns pmSuccess (0) or pmFailure (-1).
'   Description:
'       A "passthrough" method for querying specific data from the meter.
' -------------------------------------------------------------------------------
Private Function IPowerMeter_QueryMeter(ByVal command As String, msg As String) As Long
    Dim lReturnVal As Long
    Dim lStat As ViStatus
    Dim iChars As ViUInt32
    Dim iLen As ViUInt32
    Dim strResult As String
    
    ' Initialize string to be thrown as "Source" field of Err objects
    m_strErrorSource = "Error in QueryMeter() method of power meter driver"
    
    lReturnVal = pmFailure
    
    On Error GoTo 0
    
    If bDEBUG_MODE Then Debug.Print "QueryMeter, command = ", command
    
    ' ****** make sure we have a current VISA session ********
    If m_hSession = VI_NULL Then
       If IPowerMeter_Connect() = pmFailure Then
          ' Connect() will have raised error
          GoTo FUNCTIONEXIT
       End If
    End If
    
    iLen = Len(command)
    lStat = viWrite(m_hSession, command, iLen, iChars)
    If (lStat <> VI_SUCCESS) Then
        Call Err.Raise(lStat, m_strErrorSource, getVISAerror(lStat))
        GoTo FUNCTIONEXIT
    End If
    
    strResult = Space(iMAXSTRING)  ' must pass init'd string
    lStat = viRead(m_hSession, strResult, iMAXSTRING, iChars)
    If (lStat <> VI_SUCCESS) Then
        Call Err.Raise(lStat, m_strErrorSource, getVISAerror(lStat))
        GoTo FUNCTIONEXIT
    End If
    stripTermCharsFromString strResult
    
    msg = strResult
    lReturnVal = pmSuccess
   
FUNCTIONEXIT:
    IPowerMeter_QueryMeter = lReturnVal
    Exit Function
    
End Function
 
' Function ReadMeter
'   Inputs :
'       Freq is the frequency at which the measurement is being taken
'   Outputs:
'       Returns a double in the units prescribed by the IPowerMeter_Units property
'   Description:
'       Does one-shot trigger of the power meter, queries the power
'       reading, and returns the result.
'
'       The frequency is in the interface definition to allow for cases where you
'       want the power meter to correct for cal factors using it's own cal factor
'       table, instead of letting the PNA do cal factor correction with a sensor
'       table on the PNA.  For example, the power meter should do the correction
'       if the power sensor contains cal factors in memory within the sensor (such
'       as with an Agilent E-series sensor).
'
'       In general, unless the sensor contains it's own cal factors, you should
'       let the PNA do the cal factor correction using the table that you have
'       filled in on the PNA (so then frequency would just be ignored here).
' -------------------------------------------------------------------------------
Private Function IPowerMeter_ReadMeter(Optional ByVal Freq As Double) As Double
    ' Wait for delay time to elapse before reading the power
    If IPowerMeter_FixedDelay = True Then Sleep m_FIXED_DELAY
    ' Your code here
End Function
 
' Property Let: ReferenceCalFactor
'   Inputs : Reference cal factor (in percent) for calibrating the current sensor
'            channel.
'   Outputs: none
'   Description:
' -------------------------------------------------------------------------------
Private Property Let IPowerMeter_ReferenceCalFactor(ByVal dCalFactor As Double)
    ' Your code here
End Property

' Property Get: ReferenceCalFactor
'   Inputs : none
'   Outputs: reference cal factor (percent) for the current sensor channel
'   Description:
' -------------------------------------------------------------------------------
Private Property Get IPowerMeter_ReferenceCalFactor() As Double
    ' Your code here
End Property

' Function ReportErrors
'   Inputs : msg string to be written to by this function
'   Outputs: msg string, and function return value is the error number
'   Description:
'       Performs one read from the error queue of the power meter.
'       Must separate the error number and error message contained
'       in the power meter response, and return the message as the
'       "msg" argument and error number as the return value of this
'       function.
' -------------------------------------------------------------------------------
Private Function IPowerMeter_ReportErrors(ByRef msg As String) As Long
    ' Your code here
End Function

' Function SensorContainsCalFactors
'   Inputs : sensor to be checked
'   Outputs: True if cal factors are stored within the sensor, False otherwise
'   Description:
'       This is how PNA source power cal determines whether or not a cal factor
'       table is necessary on the PNA for a particular sensor.
'
'       For example, Agilent E-Series sensors have their cal factors stored in
'       the sensor EEPROM, so they do not need a table on the PNA.  If your power
'       meters do not support sensors which contain their own cal factors, you
'       should have this function always return False.
' -------------------------------------------------------------------------------
Private Function IPowerMeter_SensorContainsCalFactors(ByVal sensorNum As Long) As Boolean
    ' Your code here
End Function

' Property Let: Timeout
'   Inputs :
'   Outputs: timeout set by driver in milliseconds
'   Description: Note:  this value is rounded up or down depending on hardware
' -------------------------------------------------------------------------------
Private Property Let IPowerMeter_Timeout(ByVal lTime As Long)
    Dim lStat As ViStatus
    
    ' Initialize string to be thrown as "Source" field of Err objects
    m_strErrorSource = "Error in Let Timeout of power meter driver"
    
    If bDEBUG_MODE Then Debug.Print "Set Timeout: ", lTime
    If lTime >= m_MINIMUM_TIMEOUT Then
        lStat = viSetAttribute(m_hSession, VI_ATTR_TMO_VALUE, lTime)
        If lStat <> VI_SUCCESS Then
            Call Err.Raise(lStat, m_strErrorSource, getVISAerror(lStat))
        End If
    End If
End Property

' Property Get: Timeout
'   Inputs :
'   Outputs: timeout set by driver in milliseconds
'   Description:
' -------------------------------------------------------------------------------
Private Property Get IPowerMeter_Timeout() As Long
    Dim lTimeout As Long
    Dim lStat As ViStatus
    
    ' Initialize string to be thrown as "Source" field of Err objects
    m_strErrorSource = "Error in Get Timeout of power meter driver"
    
    If bDEBUG_MODE Then Debug.Print "Querying the Timeout value"
    lStat = viGetAttribute(m_hSession, VI_ATTR_TMO_VALUE, lTimeout)
    If bDEBUG_MODE Then Debug.Print "timeout value is:", lTimeout
    If (lStat) <> VI_SUCCESS Then
      Call Err.Raise(lStat, m_strErrorSource, getVISAerror(lStat))
    End If
    IPowerMeter_Timeout = lTimeout
End Property

' Property Let: Units
'   Inputs :
'       unit: pmdBm or pmWatts
'   Outputs: none
'   Description:
'       Sets meter to the requested units of measure for the current sensor
'       channel.
' -------------------------------------------------------------------------------
Private Property Let IPowerMeter_Units(ByVal unit As Integer)
    ' Your code here
End Property

' Property Get: Units
'   Inputs : none
'   Outputs: returns the measurement units associated with the current sensor
'   Description:
'       Should return pmdBm or pmWatts
'   Note: This driver is not intended to account for relative units like percent.
' -------------------------------------------------------------------------------
Private Property Get IPowerMeter_Units() As Integer
    ' Your code here
End Property

' Property Get: VISADescriptor
'   Inputs : none
'   Outputs: Returns the descriptor determined during IPowerMeter_Connect()
'   Description:
'       The descriptor has the form:  GPIB0::13::INSTR
' -------------------------------------------------------------------------------
Private Property Get IPowerMeter_VISADescriptor() As String
    IPowerMeter_VISADescriptor = m_strVisaDescriptor
End Property

' Subroutine WriteMeter
'   Inputs : A command string to be sent to your power meter.
'            For example, "*RST" or "SYST:PRES"
'   Outputs: none
'   Description:
'       A "passthrough" method for sending direct commands to the meter.
' -------------------------------------------------------------------------------
Private Sub IPowerMeter_WriteMeter(command As String)
    Dim lStat As ViStatus
    Dim iChars As ViUInt32
    Dim iLen As ViUInt32
    
    ' Initialize string to be thrown as "Source" field of Err objects
    m_strErrorSource = "Error in WriteMeter() method of power meter driver"
    
    On Error GoTo 0
    
    If bDEBUG_MODE Then Debug.Print "WriteMeter, command = ", command
    
    ' ****** make sure we have a current VISA session ********
    If m_hSession = VI_NULL Then
       If IPowerMeter_Connect() = pmFailure Then
          ' Connect() will have raised error
          Exit Sub
       End If
    End If
    
    iLen = Len(command)
    lStat = viWrite(m_hSession, command, iLen, iChars)
    If (lStat <> VI_SUCCESS) Then
        Call Err.Raise(lStat, m_strErrorSource, getVISAerror(lStat))
        Exit Sub
    End If
    
End Sub

' Subroutine Zero
'   Inputs : none
'   Outputs: none
'   Description:
'       Performs a zero of the power sensor, as must be done to establish
'       measurement reference with no power input, prior to IPowerMeter_Calibrate.
' -------------------------------------------------------------------------------
Private Sub IPowerMeter_Zero()
    ' Your code here
End Sub
