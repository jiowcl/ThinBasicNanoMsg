'--------------------------------------------------------------------------------------------
'  Copyright (c) Ji-Feng Tsai. All rights reserved.
'  Code released under the MIT license.
'--------------------------------------------------------------------------------------------

' NNG SDK helpers. Requires USES "NNG" before #INCLUDE.

Function SdkNngInit() As Long
  Local libPath As String
  Local ok As Long

  libPath = APP_SourcePath & "..\..\..\Library\x86"
  ok = NngLibraryInit(libPath)
  If ok = 0 Then
    libPath = APP_SourcePath & "..\..\Library\x86"
    ok = NngLibraryInit(libPath)
  End If
  If ok = 0 Then
    Printl("NngLibraryInit failed")
    Printl("Last path: " & libPath)
    Printl("Need: ...\ThinBasicNNG\Library\x86\nng.dll")
  End If
  Function = ok
End Function

Sub SdkNngShutdown()
  NngLibraryShutdown()
End Sub

Function SdkNngErrTimedOut(ByVal err As Long) As Long
  Function = (err = 5)
End Function
