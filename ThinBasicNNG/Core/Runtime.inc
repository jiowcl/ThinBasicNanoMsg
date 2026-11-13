'--------------------------------------------------------------------------------------------
'  Copyright (c) Ji-Feng Tsai. All rights reserved.
'  Code released under the MIT license.
'--------------------------------------------------------------------------------------------

' Declare Function

' <summary>
' NngInit
' </summary>
' <param name="params">Long</param>
' <returns>Returns long.</returns>
Declare Function NngInit Lib "nng.dll" Alias "nng_init" (ByVal params As Long) As Long

' <summary>
' NngFini
' </summary>
' <returns>Returns void.</returns>
Declare Sub NngFini Lib "nng.dll" Alias "nng_fini" ()

' <summary>
' NngStrerror
' </summary>
' <param name="errnum">Long</param>
' <returns>Returns pointer to ASCIIZ error string.</returns>
Declare Function NngStrerror Lib "nng.dll" Alias "nng_strerror" (ByVal errnum As Long) As Long

' Last nng_err from NngRecvBuffer and related helpers.
Global NngLastErr As Long

' <summary>
' NngStrerrorString
' </summary>
' <param name="errnum">Long</param>
' <returns>Returns string.</returns>
Function NngStrerrorString(ByVal errnum As Long) As String
  Local pErr As Long

  pErr = NngStrerror(errnum)
  If pErr Then
    Function = Peek$(ASCIIZ, pErr)
  Else
    Function = ""
  End If
End Function

' <summary>
' NngInitDefault
' </summary>
' <returns>Returns long.</returns>
Function NngInitDefault() As Long
  NngLastErr = NngInit(0)
  Function = NngLastErr
End Function

' NNG_ETIMEDOUT is 5 (nng_err). Compare with literal in If — not $NNG_ETIMEDOUT
' after nng_send/nng_recv in the same loop (ThinBasic equate compare quirk).
Function NngErrIsTimedOut(ByVal errnum As Long) As Long
  Function = (errnum = 5)
End Function
