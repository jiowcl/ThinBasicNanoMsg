'--------------------------------------------------------------------------------------------
'  Copyright (c) Ji-Feng Tsai. All rights reserved.
'  Code released under the MIT license.
'--------------------------------------------------------------------------------------------

' Declare Function

' <summary>
' NnErrno
' </summary>
' <returns>Returns long.</returns>
Declare Function NnErrno Lib "nanomsg.dll" Alias "nn_errno" () As Long

' <summary>
' NnStrerror
' </summary>
' <param name="errnum">Long</param>
' <returns>Returns pointer to ASCIIZ error string.</returns>
Declare Function NnStrerror Lib "nanomsg.dll" Alias "nn_strerror" (ByVal errnum As Long) As Long

' <summary>
' NnSymbol
' </summary>
' <param name="index">Long</param>
' <param name="value">Long</param>
' <returns>Returns pointer to ASCIIZ symbol name.</returns>
Declare Function NnSymbol Lib "nanomsg.dll" Alias "nn_symbol" (ByVal index As Long, ByRef value As Long) As Long

' <summary>
' NnTerm
' </summary>
' <returns>Returns void.</returns>
Declare Sub NnTerm Lib "nanomsg.dll" Alias "nn_term" ()

' <summary>
' NnSymbolString
' </summary>
' <param name="index">Long</param>
' <param name="value">Long</param>
' <returns>Returns string.</returns>
Function NnSymbolString(ByVal index As Long, ByRef value As Long) As String
  Local p As Long

  p = NnSymbol(index, value)
  If p Then
    Function = Peek$(ASCIIZ, p)
  Else
    Function = ""
  End If
End Function

' <summary>
' NnStrerrorString
' </summary>
' <param name="errnum">Long</param>
' <returns>Returns string.</returns>
Function NnStrerrorString(ByVal errnum As Long) As String
  Local pErr As Long

  pErr = NnStrerror(errnum)
  If pErr Then
    Function = Peek$(ASCIIZ, pErr)
  Else
    Function = ""
  End If
End Function
