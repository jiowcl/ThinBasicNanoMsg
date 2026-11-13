'--------------------------------------------------------------------------------------------
'  Copyright (c) Ji-Feng Tsai. All rights reserved.
'  Code released under the MIT license.
'--------------------------------------------------------------------------------------------

' Declare Function

' <summary>
' NngPub0Open
' </summary>
' <param name="sock">Long</param>
' <returns>Returns long.</returns>
Declare Function NngPub0Open Lib "nng.dll" Alias "nng_pub0_open" (ByRef sock As Long) As Long

' <summary>
' NngSub0Open
' </summary>
' <param name="sock">Long</param>
' <returns>Returns long.</returns>
Declare Function NngSub0Open Lib "nng.dll" Alias "nng_sub0_open" (ByRef sock As Long) As Long

' <summary>
' NngReq0Open
' </summary>
' <param name="sock">Long</param>
' <returns>Returns long.</returns>
Declare Function NngReq0Open Lib "nng.dll" Alias "nng_req0_open" (ByRef sock As Long) As Long

' <summary>
' NngRep0Open
' </summary>
' <param name="sock">Long</param>
' <returns>Returns long.</returns>
Declare Function NngRep0Open Lib "nng.dll" Alias "nng_rep0_open" (ByRef sock As Long) As Long

' <summary>
' NngPush0Open
' </summary>
' <param name="sock">Long</param>
' <returns>Returns long.</returns>
Declare Function NngPush0Open Lib "nng.dll" Alias "nng_push0_open" (ByRef sock As Long) As Long

' <summary>
' NngPull0Open
' </summary>
' <param name="sock">Long</param>
' <returns>Returns long.</returns>
Declare Function NngPull0Open Lib "nng.dll" Alias "nng_pull0_open" (ByRef sock As Long) As Long

' <summary>
' NngPair1Open
' </summary>
' <param name="sock">Long</param>
' <returns>Returns long.</returns>
Declare Function NngPair1Open Lib "nng.dll" Alias "nng_pair1_open" (ByRef sock As Long) As Long

' <summary>
' NngPair0Open
' </summary>
' <param name="sock">Long</param>
' <returns>Returns long.</returns>
Declare Function NngPair0Open Lib "nng.dll" Alias "nng_pair0_open" (ByRef sock As Long) As Long

' <summary>
' NngSurveyor0Open
' </summary>
' <param name="sock">Long</param>
' <returns>Returns long.</returns>
Declare Function NngSurveyor0Open Lib "nng.dll" Alias "nng_surveyor0_open" (ByRef sock As Long) As Long

' <summary>
' NngRespondent0Open
' </summary>
' <param name="sock">Long</param>
' <returns>Returns long.</returns>
Declare Function NngRespondent0Open Lib "nng.dll" Alias "nng_respondent0_open" (ByRef sock As Long) As Long

' <summary>
' NngBus0Open
' </summary>
' <param name="sock">Long</param>
' <returns>Returns long.</returns>
Declare Function NngBus0Open Lib "nng.dll" Alias "nng_bus0_open" (ByRef sock As Long) As Long

' <summary>
' NngSocketClose
' </summary>
' <param name="sock">Long</param>
' <returns>Returns long.</returns>
Declare Function NngSocketClose Lib "nng.dll" Alias "nng_socket_close" (ByVal sock As Long) As Long

' <summary>
' NngListen
' </summary>
' <param name="sock">Long</param>
' <param name="addr">Asciiz</param>
' <param name="listener">Long</param>
' <param name="flags">Long</param>
' <returns>Returns long.</returns>
Declare Function NngListen Lib "nng.dll" Alias "nng_listen" (ByVal sock As Long, ByVal addr As Asciiz, ByVal listener As Long, ByVal flags As Long) As Long

' <summary>
' NngDial
' </summary>
' <param name="sock">Long</param>
' <param name="addr">Asciiz</param>
' <param name="dialer">Long</param>
' <param name="flags">Long</param>
' <returns>Returns long.</returns>
Declare Function NngDial Lib "nng.dll" Alias "nng_dial" (ByVal sock As Long, ByVal addr As Asciiz, ByVal dialer As Long, ByVal flags As Long) As Long

' <summary>
' NngSend
' </summary>
' <param name="sock">Long</param>
' <param name="buf">Long</param>
' <param name="leng">DWord</param>
' <param name="flags">Long</param>
' <returns>Returns long.</returns>
Declare Function NngSend Lib "nng.dll" Alias "nng_send" (ByVal sock As Long, ByVal buf As Long, ByVal leng As DWord, ByVal flags As Long) As Long

' <summary>
' NngRecv
' </summary>
' <param name="sock">Long</param>
' <param name="buf">Long</param>
' <param name="sz">DWord</param>
' <param name="flags">Long</param>
' <returns>Returns long.</returns>
Declare Function NngRecv Lib "nng.dll" Alias "nng_recv" (ByVal sock As Long, ByVal buf As Long, ByRef sz As DWord, ByVal flags As Long) As Long

' <summary>
' NngSocketSetMs
' </summary>
' <param name="sock">Long</param>
' <param name="opt">Asciiz</param>
' <param name="optval">Long</param>
' <returns>Returns long.</returns>
Declare Function NngSocketSetMs Lib "nng.dll" Alias "nng_socket_set_ms" (ByVal sock As Long, ByVal opt As Asciiz, ByVal optval As Long) As Long

' <summary>
' NngSocketGetMs
' </summary>
' <param name="sock">Long</param>
' <param name="opt">Asciiz</param>
' <param name="optval">Long</param>
' <returns>Returns long.</returns>
Declare Function NngSocketGetMs Lib "nng.dll" Alias "nng_socket_get_ms" (ByVal sock As Long, ByVal opt As Asciiz, ByRef optval As Long) As Long

' <summary>
' NngSocketSetInt
' </summary>
' <param name="sock">Long</param>
' <param name="opt">Asciiz</param>
' <param name="optval">Long</param>
' <returns>Returns long.</returns>
Declare Function NngSocketSetInt Lib "nng.dll" Alias "nng_socket_set_int" (ByVal sock As Long, ByVal opt As Asciiz, ByVal optval As Long) As Long

' <summary>
' NngSocketGetInt
' </summary>
' <param name="sock">Long</param>
' <param name="opt">Asciiz</param>
' <param name="optval">Long</param>
' <returns>Returns long.</returns>
Declare Function NngSocketGetInt Lib "nng.dll" Alias "nng_socket_get_int" (ByVal sock As Long, ByVal opt As Asciiz, ByRef optval As Long) As Long

' <summary>
' NngSub0Subscribe
' </summary>
' <param name="sock">Long</param>
' <param name="topic">Asciiz</param>
' <returns>Returns long.</returns>
Declare Function NngSub0Subscribe Lib "nng.dll" Alias "nng_sub0_socket_subscribe" (ByVal sock As Long, ByVal topic As Asciiz) As Long

' <summary>
' NngSub0Unsubscribe
' </summary>
' <param name="sock">Long</param>
' <param name="topic">Asciiz</param>
' <returns>Returns long.</returns>
Declare Function NngSub0Unsubscribe Lib "nng.dll" Alias "nng_sub0_socket_unsubscribe" (ByVal sock As Long, ByVal topic As Asciiz) As Long

' <summary>
' NngSendString
' </summary>
' <param name="sock">Long</param>
' <param name="msg">String</param>
' <param name="flags">Long</param>
' <returns>Returns long.</returns>
Function NngSendString(ByVal sock As Long, ByVal msg As String, ByVal flags As Long) As Long
  Function = NngSend(sock, StrPtr(msg), Len(msg), flags)
End Function

' <summary>
' NngRecvBuffer
' </summary>
' <param name="sock">Long</param>
' <param name="buf">Long</param>
' <param name="buflen">DWord</param>
' <param name="flags">Long</param>
' <returns>Returns long.</returns>
Function NngRecvBuffer(ByVal sock As Long, ByVal buf As Long, ByVal buflen As DWord, ByVal flags As Long) As Long
  Local sz As DWord
  Local rc As Long

  sz = buflen
  rc = NngRecv(sock, buf, sz, flags)
  If rc = $NNG_OK Then
    Function = sz
  Else
    NngLastErr = rc
    Function = -1
  End If
End Function

' <summary>
' NngListenDefault
' </summary>
' <param name="sock">Long</param>
' <param name="addr">String</param>
' <param name="flags">Long</param>
' <returns>Returns long.</returns>
Function NngListenDefault(ByVal sock As Long, ByVal addr As String, ByVal flags As Long) As Long
  Function = NngListen(sock, addr, 0, flags)
End Function

' <summary>
' NngDialDefault
' </summary>
' <param name="sock">Long</param>
' <param name="addr">String</param>
' <param name="flags">Long</param>
' <returns>Returns long.</returns>
Function NngDialDefault(ByVal sock As Long, ByVal addr As String, ByVal flags As Long) As Long
  Function = NngDial(sock, addr, 0, flags)
End Function

' <summary>
' NngSetRecvTimeoutMs
' </summary>
' <param name="lSock">Long</param>
' <param name="lMs">Long</param>
' <returns>Returns long.</returns>
Function NngSetRecvTimeoutMs(ByVal lSock As Long, ByVal lMs As Long) As Long
  Function = NngSocketSetMs(lSock, "recv-timeout", lMs)
End Function

' <summary>
' NngSetSurveyTimeMs
' </summary>
' <param name="lSock">Long</param>
' <param name="lMs">Long</param>
' <returns>Returns long.</returns>
Function NngSetSurveyTimeMs(ByVal lSock As Long, ByVal lMs As Long) As Long
  Function = NngSocketSetMs(lSock, "surveyor:survey-time", lMs)
End Function

' <summary>
' NngSetOptMs
' </summary>
' <param name="lSock">Long</param>
' <param name="opt">String</param>
' <param name="optval">Long</param>
' <returns>Returns long.</returns>
Function NngSetOptMs(ByVal lSock As Long, ByVal opt As String, ByVal optval As Long) As Long
  Function = NngSocketSetMs(lSock, opt, optval)
End Function
