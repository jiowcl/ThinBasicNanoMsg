'--------------------------------------------------------------------------------------------
'  Copyright (c) Ji-Feng Tsai. All rights reserved.
'  Code released under the MIT license.
'--------------------------------------------------------------------------------------------

' OOP façade over the procedural API.
' ThinBasic limits: Type methods cannot use parameter name "sock"; avoid NngSocketSetMs
' with a String option from inside the Type (use SockSetMs + NngSetRecvTimeoutMs helpers).
#INCLUDE Once "Nng.inc"

' Type

Type LibNngRuntime
  Public

  ' <summary>
  ' DoInit
  ' </summary>
  ' <returns>Returns long.</returns>
  Function DoInit() As Long
    Function = NngInitDefault()
  End Function

  ' <summary>
  ' DoFini
  ' </summary>
  ' <returns>Returns void.</returns>
  Sub DoFini()
    NngFini()
  End Sub

  ' <summary>
  ' GetLastError
  ' </summary>
  ' <returns>Returns long.</returns>
  Function GetLastError() As Long
    Function = NngLastErr
  End Function

  ' <summary>
  ' GetStrerror
  ' </summary>
  ' <param name="errnum">Long</param>
  ' <returns>Returns string.</returns>
  Function GetStrerror(ByVal errnum As Long) As String
    Function = NngStrerrorString(errnum)
  End Function

  Function IsTimedOut(ByVal errnum As Long) As Long
    Function = NngErrIsTimedOut(errnum)
  End Function
End Type

Type LibNngSocket
  Public

  ' ThinBasic type methods: do not name parameters "sock" (conflicts with SOCK token in DLL calls).

  Function PubOpen(ByRef socket As Long) As Long
    socket = 0
    Function = NngPub0Open(socket)
  End Function

  Function SubOpen(ByRef socket As Long) As Long
    socket = 0
    Function = NngSub0Open(socket)
  End Function

  Function ReqOpen(ByRef socket As Long) As Long
    socket = 0
    Function = NngReq0Open(socket)
  End Function

  Function RepOpen(ByRef socket As Long) As Long
    socket = 0
    Function = NngRep0Open(socket)
  End Function

  Function PushOpen(ByRef socket As Long) As Long
    socket = 0
    Function = NngPush0Open(socket)
  End Function

  Function PullOpen(ByRef socket As Long) As Long
    socket = 0
    Function = NngPull0Open(socket)
  End Function

  Function PairOpen(ByRef socket As Long) As Long
    socket = 0
    Function = NngPair1Open(socket)
  End Function

  Function Pair0Open(ByRef socket As Long) As Long
    socket = 0
    Function = NngPair0Open(socket)
  End Function

  Function SurveyorOpen(ByRef socket As Long) As Long
    socket = 0
    Function = NngSurveyor0Open(socket)
  End Function

  Function RespondentOpen(ByRef socket As Long) As Long
    socket = 0
    Function = NngRespondent0Open(socket)
  End Function

  Function BusOpen(ByRef socket As Long) As Long
    socket = 0
    Function = NngBus0Open(socket)
  End Function

  Function SockClose(ByVal lId As Long) As Long
    Function = NngSocketClose(lId)
  End Function

  Function SockListen(ByVal socket As Long, ByVal addr As String, ByVal flags As Long) As Long
    Function = NngListenDefault(socket, addr, flags)
  End Function

  Function SockDial(ByVal socket As Long, ByVal addr As String, ByVal flags As Long) As Long
    Function = NngDialDefault(socket, addr, flags)
  End Function

  Function SockSend(ByVal socket As Long, ByVal buf As Long, ByVal leng As DWord, ByVal flags As Long) As Long
    Function = NngSend(socket, buf, leng, flags)
  End Function

  Function SockSendStr(ByVal socket As Long, ByVal msg As String, ByVal flags As Long) As Long
    Function = NngSendString(socket, msg, flags)
  End Function

  Function SockRecv(ByVal socket As Long, ByVal buf As Long, ByVal buflen As DWord, ByVal flags As Long) As Long
    Function = NngRecvBuffer(socket, buf, buflen, flags)
  End Function

  Function SockSetMs(ByVal lId As Long, ByVal sOption As String, ByVal lMs As Long) As Long
    If sOption = "recv-timeout" Then
      Function = NngSetRecvTimeoutMs(lId, lMs)
    ElseIf sOption = "surveyor:survey-time" Then
      Function = NngSetSurveyTimeMs(lId, lMs)
    Else
      Function = NngSetOptMs(lId, sOption, lMs)
    End If
  End Function

  Function Subscribe(ByVal socket As Long, ByVal topic As String) As Long
    Function = NngSub0Subscribe(socket, topic)
  End Function

  Function Unsubscribe(ByVal socket As Long, ByVal topic As String) As Long
    Function = NngSub0Unsubscribe(socket, topic)
  End Function
End Type
