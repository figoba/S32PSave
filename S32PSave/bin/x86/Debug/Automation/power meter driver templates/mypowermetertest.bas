Attribute VB_Name = "modMain"
'---------------------------------------------------------------------
' File:
'   MyPowerMeterTest.bas (modMain)
'
' Description:
'   This Visual Basic 6.0 module consists of code to aid in testing a
'   power meter driver prior to use of that driver on an Agilent PNA
'   network analyzer.
'
'   This code is intended to be run within the Visual Basic development
'   environment instead of compiling to an EXE -- printed output is
'   all sent to the 'Immediate' window.
'---------------------------------------------------------------------

Public Sub Main()
   ' The IPowerMeter COM interface
   Dim PowerMeterIntf As AgilentPNAPowerMeter.IPowerMeter
   ' The object instance of your power meter driver
   Dim PowerMeterObj As Object
   Dim bRetVal As Boolean
   Dim lRetVal As Long
   Dim strResult As String
   Dim dFreq As Double
   Dim dReading As Double
    
   ' Like the PNA reports errors thrown by the power meter driver,
   ' so does this test project.
   On Error GoTo ErrorHandler
   
   ' Create the object instance of your power meter driver
   Set PowerMeterObj = CreateObject("MyPowerMeter.PowerMeter", "MyPNA")
   ' We communicate with the driver through the IPowerMeter interface
   Set PowerMeterIntf = PowerMeterObj
   
   ' "Connect" opens a VISA session to the power meter and presets the meter.
   ' Note as we are passing no parameters to Connect, it will perform a
   ' default VISA GPIB search for the meter.
   bRetVal = PowerMeterIntf.Connect
   If bRetVal = pmFailure Then
       MsgBox "Connect could not identify the power meter", vbOKOnly + vbExclamation
       Exit Sub
   End If

   ' Write to and read from the Properties of the driver.
   ' Set current sensor first, since many other properties are
   ' with respect to current sensor.
   Debug.Print "Setting CurrentSensor to 2"
   PowerMeterIntf.CurrentSensor = 2
   Debug.Print "CurrentSensor reads back as:", PowerMeterIntf.CurrentSensor
   Debug.Print "Setting CurrentSensor to 1"
   PowerMeterIntf.CurrentSensor = 1
   Debug.Print "CurrentSensor reads back as:", PowerMeterIntf.CurrentSensor
   Debug.Print
   Debug.Print "Setting AutoDelay = True"
   PowerMeterIntf.AutoDelay = True
   Debug.Print "AutoDelay reads back as:", PowerMeterIntf.AutoDelay
   Debug.Print "Setting AutoDelay = False"
   PowerMeterIntf.AutoDelay = False
   Debug.Print "AutoDelay reads back as:", PowerMeterIntf.AutoDelay
   Debug.Print
   Debug.Print "Setting Averaging = True"
   PowerMeterIntf.Averaging = True
   Debug.Print "Averaging reads back as:", PowerMeterIntf.Averaging
   Debug.Print "Setting Averaging = False"
   PowerMeterIntf.Averaging = False
   Debug.Print "Averaging reads back as:", PowerMeterIntf.Averaging
   Debug.Print
   Debug.Print "Setting AveragingFactor = 2"
   PowerMeterIntf.AveragingFactor = 2
   Debug.Print "AveragingFactor reads back as:", PowerMeterIntf.AveragingFactor
   Debug.Print
   Debug.Print "Setting ContinuousTrigger to True"
   PowerMeterIntf.ContinuousTrigger = True
   Debug.Print "ContinuousTrigger reads back as:", PowerMeterIntf.ContinuousTrigger
   Debug.Print "Setting ContinuousTrigger to False"
   PowerMeterIntf.ContinuousTrigger = False
   Debug.Print "ContinuousTrigger reads back as:", PowerMeterIntf.ContinuousTrigger
   Debug.Print
   Debug.Print "Setting FixedDelay to True"
   PowerMeterIntf.FixedDelay = True
   Debug.Print "FixedDelay reads back as:", PowerMeterIntf.FixedDelay
   Debug.Print "Setting FixedDelay to False"
   PowerMeterIntf.FixedDelay = False
   Debug.Print "FixedDelay reads back as:", PowerMeterIntf.FixedDelay
   Debug.Print
   Debug.Print "IDString is:", PowerMeterIntf.IDString
   Debug.Print
   Debug.Print "MaximumSensorNumber is:", PowerMeterIntf.MaximumSensorNumber
   Debug.Print
   Debug.Print "Setting Timeout to 10000 milliseconds"
   PowerMeterIntf.Timeout = 10000
   Debug.Print "Timeout reads back as:", PowerMeterIntf.Timeout
   Debug.Print
   Debug.Print "Setting Units to Watts"
   PowerMeterIntf.Units = pmWatts
   If PowerMeterIntf.Units = pmWatts Then
       Debug.Print "Units read back as:", "Watts"
   Else ' PowerMeterIntf.Units = pmdBm
       Debug.Print "Units read back as:", "dBm"
   End If
   Debug.Print "Setting Units to dBm"
   PowerMeterIntf.Units = pmdBm
   If PowerMeterIntf.Units = pmdBm Then
       Debug.Print "Units read back as:", "dBm"
   Else ' PowerMeterIntf.Units = pmWatts
       Debug.Print "Units read back as:", "Watts"
   End If
   Debug.Print
   Debug.Print "VISADescriptor is:", PowerMeterIntf.VISADescriptor
   
   Debug.Print
   ' Check which channels have sensors attached.
   Debug.Print "Sensor 1 attached: ", PowerMeterIntf.IsSensorAttached(1)
   ' Note: PowerMeterIntf.IsSensorAttached(2) should equal False for a
   '       single channel power meter.
   Debug.Print "Sensor 2 attached: ", PowerMeterIntf.IsSensorAttached(2)
   ' Check if the sensors contain cal factors or not.
   Debug.Print
   Debug.Print "Sensor 1 contains cal factors: ", PowerMeterIntf.SensorContainsCalFactors(1)
   Debug.Print "Sensor 2 contains cal factors: ", PowerMeterIntf.SensorContainsCalFactors(2)
   ' CalFactor and ReferenceCalFactor properties are only relevant
   ' if the current sensor does not contain it's cal factors in memory
   If Not PowerMeterIntf.SensorContainsCalFactors(PowerMeterIntf.CurrentSensor) Then
      Debug.Print
      Debug.Print "Setting CalFactor = 0.98"
      PowerMeterIntf.CalFactor = 0.98
      Debug.Print "CalFactor reads back as:", PowerMeterIntf.CalFactor
      Debug.Print
      Debug.Print "Setting ReferenceCalFactor = 0.98"
      PowerMeterIntf.ReferenceCalFactor = 0.98
      Debug.Print "ReferenceCalFactor reads back as:", PowerMeterIntf.ReferenceCalFactor
   End If
   ' Send a direct query to the meter.
   strResult = Space(256)
   PowerMeterIntf.QueryMeter "*IDN?", strResult
   Debug.Print
   Debug.Print "QueryMeter result of *IDN?: ", strResult
   ' Write two invalid command strings to the meter.
   PowerMeterIntf.WriteMeter "BADCOMMAND1"
   PowerMeterIntf.WriteMeter "BADCOMMAND2"
   ' Query the meter's error queue (error from most recent bad command)
   lRetVal = PowerMeterIntf.ReportErrors(strResult)
   Debug.Print
   Debug.Print "ReportErrors returned: ", lRetVal, strResult
   ' Clear the error generated by the first bad command from the error queue
   PowerMeterIntf.ClearErrors
   ' Query the meter's error queue again (should now be no errors)
   lRetVal = PowerMeterIntf.ReportErrors(strResult)
   Debug.Print "ReportErrors returned: ", lRetVal, strResult
   
   ' Now the functions for zeroing, calibrating and reading the meter
   lRetVal = MsgBox("Connect sensor to POWER REFerence on the meter", vbOKCancel)
   If lRetVal = vbCancel Then GoTo SubExit
   PowerMeterIntf.Zero
   Debug.Print
   Debug.Print "Zeroed"
   PowerMeterIntf.Calibrate
   Debug.Print "Calibrated"
   lRetVal = MsgBox("Connect sensor to power source to be measured", vbOKCancel)
   If lRetVal = vbCancel Then GoTo SubExit
   ' Change the value of dFreq if necessary
   dFreq = 50000000#
   dReading = PowerMeterIntf.ReadMeter(dFreq)
   Debug.Print
   Debug.Print "ReadMeter returned: ", dReading
   
   ' Preset the meter
   PowerMeterIntf.Preset
   
SubExit:
   ' Close the VISA session
   PowerMeterIntf.CloseConnection
   Exit Sub
   
ErrorHandler:
   MsgBox "Error Number " & Err.Number & ": " & Err.Description, _
      vbOKOnly + vbExclamation
   ' Close the VISA session
   PowerMeterIntf.CloseConnection
End Sub

