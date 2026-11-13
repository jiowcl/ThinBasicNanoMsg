'--------------------------------------------------------------------------------------------
'  Copyright (c) Ji-Feng Tsai. All rights reserved.
'  Code released under the MIT license.
'--------------------------------------------------------------------------------------------

' Declare Function

' <summary>
' NnSocket
' </summary>
' <param name="domain">Long</param>
' <param name="protocol">Long</param>
' <returns>Returns socket handle.</returns>
Declare Function NnSocket Lib "nanomsg.dll" Alias "nn_socket" (ByVal domain As Long, ByVal protocol As Long) As Long

' <summary>
' NnClose
' </summary>
' <param name="socket">Long</param>
' <returns>Returns long.</returns>
Declare Function NnClose Lib "nanomsg.dll" Alias "nn_close" (ByVal socket As Long) As Long

' <summary>
' NnSetsockopt
' </summary>
' <param name="socket">Long</param>
' <param name="level">Long</param>
' <param name="options">Long</param>
' <param name="optval">Long</param>
' <param name="optvallen">DWord</param>
' <returns>Returns long.</returns>
Declare Function NnSetsockopt Lib "nanomsg.dll" Alias "nn_setsockopt" (ByVal socket As Long, ByVal level As Long, ByVal options As Long, ByVal optval As Long, ByVal optvallen As DWord) As Long

' <summary>
' NnGetsockopt
' </summary>
' <param name="socket">Long</param>
' <param name="level">Long</param>
' <param name="options">Long</param>
' <param name="optval">Long</param>
' <param name="optvallen">DWord</param>
' <returns>Returns long.</returns>
Declare Function NnGetsockopt Lib "nanomsg.dll" Alias "nn_getsockopt" (ByVal socket As Long, ByVal level As Long, ByVal options As Long, ByVal optval As Long, ByRef optvallen As DWord) As Long

' <summary>
' NnBind
' </summary>
' <param name="socket">Long</param>
' <param name="addr">Asciiz</param>
' <returns>Returns long.</returns>
Declare Function NnBind Lib "nanomsg.dll" Alias "nn_bind" (ByVal socket As Long, ByVal addr As Asciiz) As Long

' <summary>
' NnConnect
' </summary>
' <param name="socket">Long</param>
' <param name="addr">Asciiz</param>
' <returns>Returns long.</returns>
Declare Function NnConnect Lib "nanomsg.dll" Alias "nn_connect" (ByVal socket As Long, ByVal addr As Asciiz) As Long

' <summary>
' NnShutdown
' </summary>
' <param name="socket">Long</param>
' <param name="how">Long</param>
' <returns>Returns long.</returns>
Declare Function NnShutdown Lib "nanomsg.dll" Alias "nn_shutdown" (ByVal socket As Long, ByVal how As Long) As Long

' <summary>
' NnSend
' </summary>
' <param name="socket">Long</param>
' <param name="buf">Long</param>
' <param name="buflen">DWord</param>
' <param name="flags">Long</param>
' <returns>Returns long.</returns>
Declare Function NnSend Lib "nanomsg.dll" Alias "nn_send" (ByVal socket As Long, ByVal buf As Long, ByVal buflen As DWord, ByVal flags As Long) As Long

' <summary>
' NnRecv
' </summary>
' <param name="socket">Long</param>
' <param name="buf">Long</param>
' <param name="buflen">DWord</param>
' <param name="flags">Long</param>
' <returns>Returns long.</returns>
Declare Function NnRecv Lib "nanomsg.dll" Alias "nn_recv" (ByVal socket As Long, ByVal buf As Long, ByVal buflen As DWord, ByVal flags As Long) As Long

' <summary>
' NnPoll
' </summary>
' <param name="fds">Long</param>
' <param name="nfds">Long</param>
' <param name="timeout">Long</param>
' <returns>Returns long.</returns>
Declare Function NnPoll Lib "nanomsg.dll" Alias "nn_poll" (ByVal fds As Long, ByVal nfds As Long, ByVal timeout As Long) As Long

' <summary>
' NnGetStatistic
' </summary>
' <param name="socket">Long</param>
' <param name="stat">Long</param>
' <returns>Returns DWord.</returns>
Declare Function NnGetStatistic Lib "nanomsg.dll" Alias "nn_get_statistic" (ByVal socket As Long, ByVal stat As Long) As DWord

' <summary>
' NnSetsockoptString
' </summary>
' <param name="socket">Long</param>
' <param name="level">Long</param>
' <param name="options">Long</param>
' <param name="optval">String</param>
' <returns>Returns long.</returns>
Function NnSetsockoptString(ByVal socket As Long, ByVal level As Long, ByVal options As Long, ByVal optval As String) As Long
  Function = NnSetsockopt(socket, level, options, StrPtr(optval), Len(optval))
End Function

' <summary>
' NnSetsockoptInt
' </summary>
' <param name="socket">Long</param>
' <param name="level">Long</param>
' <param name="options">Long</param>
' <param name="optval">Long</param>
' <returns>Returns long.</returns>
Function NnSetsockoptInt(ByVal socket As Long, ByVal level As Long, ByVal options As Long, ByVal optval As Long) As Long
  Local lOptVal As Long

  lOptVal = optval
  Function = NnSetsockopt(socket, level, options, VarPtr(lOptVal), SizeOf(Long))
End Function

' <summary>
' NnGetsockoptInt
' </summary>
' <param name="socket">Long</param>
' <param name="level">Long</param>
' <param name="options">Long</param>
' <param name="optval">Long</param>
' <returns>Returns long.</returns>
Function NnGetsockoptInt(ByVal socket As Long, ByVal level As Long, ByVal options As Long, ByRef optval As Long) As Long
  Local optvallen As DWord

  optvallen = SizeOf(Long)
  Function = NnGetsockopt(socket, level, options, VarPtr(optval), optvallen)
End Function

' <summary>
' NnSendString
' </summary>
' <param name="socket">Long</param>
' <param name="msg">String</param>
' <param name="flags">Long</param>
' <returns>Returns long.</returns>
Function NnSendString(ByVal socket As Long, ByVal msg As String, ByVal flags As Long) As Long
  Function = NnSend(socket, StrPtr(msg), Len(msg), flags)
End Function

' <summary>
' NnRecvString
' </summary>
' <param name="socket">Long</param>
' <param name="buflen">DWord</param>
' <param name="flags">Long</param>
' <returns>Returns string.</returns>
Function NnRecvString(ByVal socket As Long, ByVal buflen As DWord, ByVal flags As Long) As String
  Local buf As Asciiz * 4096
  Local n As Long

  If buflen > SizeOf(buf) Then buflen = SizeOf(buf)
  n = NnRecv(socket, VarPtr(buf), buflen, flags)
  If n < 0 Then
    Function = ""
  Else
    Function = Left$(buf, n)
  End If
End Function
