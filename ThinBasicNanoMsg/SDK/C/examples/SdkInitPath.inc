'--------------------------------------------------------------------------------------------
'  Copyright (c) Ji-Feng Tsai. All rights reserved.
'  Code released under the MIT license.
'--------------------------------------------------------------------------------------------

' NanoMsg SDK helpers. Requires USES "NanoMsg" before #INCLUDE.

' <summary>
' SdkNanoMsgInit — load nanomsg.dll from ThinBasicNanoMsg\Library\x86
' </summary>
' <returns>1 on success, 0 on failure</returns>
Function SdkNanoMsgInit() As Long
  Local libPath As String
  Local ok As Long

  libPath = APP_SourcePath & "..\..\..\Library\x86"
  ok = NnLibraryInit(libPath)
  If ok = 0 Then
    libPath = APP_SourcePath & "..\..\Library\x86"
    ok = NnLibraryInit(libPath)
  End If
  If ok = 0 Then
    Printl("NnLibraryInit failed")
    Printl("Last path: " & libPath)
    Printl("Need: ...\ThinBasicNanoMsg\Library\x86\nanomsg.dll")
  End If
  Function = ok
End Function

' <summary>
' SdkNanoMsgShutdown
' </summary>
Sub SdkNanoMsgShutdown()
  NnLibraryShutdown()
End Sub
