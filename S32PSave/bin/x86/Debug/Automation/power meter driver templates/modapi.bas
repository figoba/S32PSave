Attribute VB_Name = "WinAPI"
'---------------------------------------------------------------------
' File:
'   modAPI.bas (WinAPI)
'
' Description:
'   This Visual Basic 6.0 module defines the Microsoft Windows API
'   functions which this power meter driver will make use of.
'   The Help system onboard the PNA describes in detail how to write
'   a PNA power meter driver using these template files.
'---------------------------------------------------------------------

Option Explicit
Option Base 0

Public Const sCLASSNAME As String = "PowerMeter"

' This string -- sIDSEARCH -- is where you define the substrings of ID strings
' returned by your supported power meters in response to the "*IDN?" IEEE 488.2
' command.  The IEEE 488.2 standard dictates that the ID string always begin with
' brand name then model number, separated by a comma, followed by information such
' as serial number, firmware/software revision, etc.  An ID string of an "Acme"
' brand of power meter might look like this:
'     Acme Brand,100A,US12345678,A1.01.00
' You would put the brand and model number part of the string into sIDSEARCH:
'     Acme Brand,100A
' Modify this sIDSEARCH string so it contains just the comma-delimited brand and
' model numbers from the ID strings of all power meters supported by your driver,
' a semicolon between each pair as you see in the example sIDSEARCH string here.
' The ID substrings will be used in registering your driver on the PNA, and also
' as a default search string whenever the IPowerMeter_Connect() method of your
' driver is asked to search for supported power meters.
Public Const sIDSEARCH As String = "Acme Brand,100A;Acme Brand,100B;Acme Brand,200A"

'Main registry keys where we will be referencing PNA settings
Private Const HKEY_CLASSES_ROOT = &H80000000
Private Const HKEY_LOCAL_MACHINE = &H80000002

'Security access masks for specifying the level of registry access we are requesting.
Private Const KEY_WRITE = &H20006
Private Const KEY_READ = &H20019

'To specify we want new registry keys to persist after reboot
Private Const REG_OPTION_NON_VOLATILE = &H0

'The PNA power meter driver registry section under HKEY_LOCAL_MACHINE
Private Const sDRIVER_SECTION As String = "SOFTWARE\Agilent\Network Analyzer\Power Calibration\AvailablePowerMeterDrivers"

'API functions contained in advapi32.dll.
'For setting and retrieving information in the registry.
'=================

Private Declare Function RegOpenKeyEx Lib "AdvAPI32.dll" Alias _
   "RegOpenKeyExA" (ByVal hKey As Long, ByVal lpSubKey As String, _
   ByVal ulOptions As Long, ByVal samDesired As Long, _
   phkResult As Long) As Long
   
Private Declare Function RegQueryValueEx Lib "AdvAPI32.dll" Alias _
   "RegQueryValueExA" (ByVal hKey As Long, _
   ByVal lpValueName As String, ByVal lpReserved As Long, _
   lpType As Long, ByVal lpData As String, lpcbData As Long) As Long
   
Private Declare Function RegCloseKey _
   Lib "AdvAPI32.dll" (ByVal hKey As Long) As Long
   
Private Declare Function RegCreateKeyEx Lib "AdvAPI32.dll" Alias _
   "RegCreateKeyExA" (ByVal hKey As Long, ByVal lpSubKey As String, _
   ByVal Reserved As Long, lpClass As String, ByVal lOptions As Long, _
   ByVal samDesired As Long, lpSecurityAttributes As Any, _
   phkResult As Long, lpDisposition As Long) As Long
   
Private Declare Function RegSetValueEx Lib "AdvAPI32.dll" Alias _
   "RegSetValueExA" (ByVal hKey As Long, _
   ByVal lpValueName As String, ByVal Reserved As Long, _
   ByVal dwType As Long, ByVal lpData As String, _
   ByVal cbData As Long) As Long
   
Private Declare Function RegFlushKey _
   Lib "AdvAPI32.dll" (ByVal hKey As Long) As Long

'API function contained in kernel32.
'For inserting delays such as are sometimes needed between GPIB transactions
'=================

Public Declare Sub Sleep Lib "kernel32" (ByVal dwMilliseconds As Long)

'After COM "/regserver" registration of this power meter driver EXE,
'this will register the ID strings of the supported power meters
'so PNA Source Power Cal will use this driver for those meters.
Public Sub Main()
   Dim sCLSID As String
   Dim sReadBack As String
   Dim sIDs() As String
   Dim i As Integer
      
   If App.StartMode = vbSModeStandalone Then
       sCLSID = ReadRegistry(HKEY_CLASSES_ROOT, _
                             App.EXEName & "." & sCLASSNAME & "\CLSID", "")
          
       If Len(sCLSID) = 0 Then
           MsgBox App.EXEName & "." & sCLASSNAME & " is not in the Registry.  " & _
                  "Either the exe name does not match the driver's VB Project Name, " & _
                  "or the sCLASSNAME string in the source code does not match the driver's Class Name.", _
                   vbOKOnly + vbExclamation
           Exit Sub
       End If
       
       getSemicolonDelimitedStrings sIDSEARCH, sIDs()
       
       For i = 0 To UBound(sIDs)
           If Len(sIDs(i)) = 0 Then
               MsgBox "Problem parsing the power meter ID substrings in the sIDSEARCH constant of the driver.", _
                   vbOKOnly + vbExclamation
               Exit Sub
           End If
           
           WriteRegistry HKEY_LOCAL_MACHINE, sDRIVER_SECTION, _
               sIDs(i), sCLSID
           sReadBack = ReadRegistry(HKEY_LOCAL_MACHINE, sDRIVER_SECTION, _
               sIDs(i))
       
           If Len(sReadBack) = 0 Then
               MsgBox "Problem writing to the registry.  Please check that you have sufficient privileges.", _
                   vbOKOnly + vbExclamation
               Exit Sub
           End If
       Next i
       
       MsgBox "Registration was successful."
   End If
End Sub

' Sub getSemicolonDelimitedStrings
'   Inputs : sInput contains instrument IDs separated by semicolons
'   Outputs: sIDs contains the IDs as separate strings (delimiters removed)
'   Description:
'       Helper method for IPowerMeter_Connect().
'---------------------------------------------------------------------------
Public Sub getSemicolonDelimitedStrings(ByVal strInput As String, strIDs() As String)
    Const strDelimiter As String = ";"
    Dim strRemainder As String
    Dim iDelimiter As Integer
    Dim i As Integer
    
    strRemainder = strInput
    i = 0
    iDelimiter = InStr(1, strRemainder, strDelimiter)
    Do While (iDelimiter > 0)
       ReDim Preserve strIDs(i)
       strIDs(i) = Trim(Mid(strRemainder, 1, iDelimiter - 1))             ' copy to new str
       strRemainder = Right(strRemainder, Len(strRemainder) - iDelimiter) ' shift old str
       iDelimiter = InStr(1, strRemainder, strDelimiter)
       i = i + 1
    Loop
    ReDim Preserve strIDs(i)
    strIDs(i) = Trim(strRemainder)  ' last one
    
End Sub

'To read from the registry...
Private Function ReadRegistry(ByVal lBaseKey As Long, ByVal sSection As String, ByVal sKey As String) As String

   'Declare error check variable lResult, key handling variables lKeyValue, lDataTypeValue, lValueLength and sValue
   Dim lResult As Long, lKeyValue As Long, lDataTypeValue As Long, lValueLength As Long, sValue As String

   'Turn on error trapping
   On Error Resume Next

   'Now open the specified registry section under the specified base key
   lResult = RegOpenKeyEx(lBaseKey, sSection, 0, KEY_READ, lKeyValue)

   'Initiate an empty variable sValue to hold retrieved information to a maximum of 2048 bytes
   sValue = Space$(2048)
   lValueLength = Len(sValue)

   'Now open the selected key under the base key
   lResult = RegQueryValueEx(lKeyValue, sKey, 0&, lDataTypeValue, sValue, lValueLength)

   'Check if an error occured meanwhile. If so, return a default empty string
   If (lResult = 0) And (Err.Number = 0) Then
       sValue = Left$(sValue, lValueLength - 1)
   Else
       sValue = Empty
   End If

   'Now close the opened key and return the value to the function
   lResult = RegCloseKey(lKeyValue)
   ReadRegistry = sValue

End Function

'To write to the registry...
Private Sub WriteRegistry(ByVal lBaseKey As Long, ByVal sSection As String, ByVal sKey As String, ByVal sValue As String)

   'Declare error check variable lResult and key handling variables
   Dim lResult As Long, lKeyValue As Long, sKeyClass As String, lDisposition As Long

   'Turn on error trapping
   On Error Resume Next

   'If the section we wish to write to does not exist, create it
   lResult = RegCreateKeyEx(lBaseKey, sSection, 0, sKeyClass, _
      REG_OPTION_NON_VOLATILE, KEY_WRITE, 0, lKeyValue, lDisposition)

   'Now set value in the registry
   lResult = RegSetValueEx(lKeyValue, sKey, 0&, 1&, sValue, Len(sValue))

   'And finally, flush the registry buffer and close the key
   lResult = RegFlushKey(lKeyValue)
   lResult = RegCloseKey(lKeyValue)

End Sub

