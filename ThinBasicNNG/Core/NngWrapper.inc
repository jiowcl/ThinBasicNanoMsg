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

  ' <summary>
  ' IsTimedOut
  ' </summary>
  ' <param name="errnum">Long</param>
  ' <returns>Returns Long.</returns>
  Function IsTimedOut(ByVal errnum As Long) As Long
    Function = NngErrIsTimedOut(errnum)
  End Function
End Type

Type LibNngSocket
  Public

  ' ThinBasic type methods: do not name parameters "sock" (conflicts with SOCK token in DLL calls).

  ' <summary>
  ' Pub0Open
  ' </summary>
  ' <param name="socket">Long</param>
  ' <returns>Returns long.</returns>
  Function PubOpen(ByRef socket As Long) As Long
    socket = 0
    Function = NngPub0Open(socket)
  End Function

  ' <summary>
  ' SubOpen
  ' </summary>
  ' <param name="socket">Long</param>
  ' <returns>Returns long.</returns>
  Function SubOpen(ByRef socket As Long) As Long
    socket = 0
    Function = NngSub0Open(socket)
  End Function

  ' <summary>
  ' ReqOpen
  ' </summary>
  ' <param name="socket">Long</param>
  ' <returns>Returns long.</returns>
  Function ReqOpen(ByRef socket As Long) As Long
    socket = 0
    Function = NngReq0Open(socket)
  End Function

  ' <summary>
  ' RepOpen
  ' </summary>
  ' <param name="socket">Long</param>
  ' <returns>Returns long.</returns>
  Function RepOpen(ByRef socket As Long) As Long
    socket = 0
    Function = NngRep0Open(socket)
  End Function

  ' <summary>
  ' PushOpen
  ' </summary>
  ' <param name="socket">Long</param>
  ' <returns>Returns long.</returns>
  Function PushOpen(ByRef socket As Long) As Long
    socket = 0
    Function = NngPush0Open(socket)
  End Function

  ' <summary>
  ' PullOpen
  ' </summary>
  ' <param name="socket">Long</param>
  ' <returns>Returns long.</returns>
  Function PullOpen(ByRef socket As Long) As Long
    socket = 0
    Function = NngPull0Open(socket)
  End Function

  ' <summary>
  ' PairOpen
  ' </summary>
  ' <param name="socket">Long</param>
  ' <returns>Returns long.</returns>
  Function PairOpen(ByRef socket As Long) As Long
    socket = 0
    Function = NngPair1Open(socket)
  End Function

  ' <summary>
  ' Pair0Open
  ' </summary>
  ' <param name="socket">Long</param>
  ' <returns>Returns long.</returns>
  Function Pair0Open(ByRef socket As Long) As Long
    socket = 0
    Function = NngPair0Open(socket)
  End Function

  ' <summary>
  ' SurveyorOpen
  ' </summary>
  ' <param name="socket">Long</param>
  ' <returns>Returns long.</returns>
  Function SurveyorOpen(ByRef socket As Long) As Long
    socket = 0
    Function = NngSurveyor0Open(socket)
  End Function

  ' <summary>
  ' RespondentOpen
  ' </summary>
  ' <param name="socket">Long</param>
  ' <returns>Returns long.</returns>
  Function RespondentOpen(ByRef socket As Long) As Long
    socket = 0
    Function = NngRespondent0Open(socket)
  End Function

  ' <summary>
  ' BusOpen
  ' </summary>
  ' <param name="socket">Long</param>
  ' <returns>Returns long.</returns>
  Function BusOpen(ByRef socket As Long) As Long
    socket = 0
    Function = NngBus0Open(socket)
  End Function

  ' <summary>
  ' SockClose
  ' </summary>
  ' <param name="lId">Long</param>
  ' <returns>Returns long.</returns>
  Function SockClose(ByVal lId As Long) As Long
    Function = NngSocketClose(lId)
  End Function

  ' <summary>
  ' SockListen
  ' </summary>
  ' <param name="socket">Long</param>
  ' <param name="addr">String</param>
  ' <param name="flags">Long</param>
  ' <returns>Returns long.</returns>
  Function SockListen(ByVal socket As Long, ByVal addr As String, ByVal flags As Long) As Long
    Function = NngListenDefault(socket, addr, flags)
  End Function

  ' <summary>
  ' SockDial
  ' </summary>
  ' <param name="socket">Long</param>
  ' <param name="addr">String</param>
  ' <param name="flags">Long</param>
  ' <returns>Returns long.</returns>
  Function SockDial(ByVal socket As Long, ByVal addr As String, ByVal flags As Long) As Long
    Function = NngDialDefault(socket, addr, flags)
  End Function

  ' <summary>
  ' SockSend
  ' </summary>
  ' <param name="socket">Long</param>
  ' <param name="buf">Long</param>
  ' <param name="leng">DWord</param>
  ' <param name="flags">Long</param>
  ' <returns>Returns long.</returns>
  Function SockSend(ByVal socket As Long, ByVal buf As Long, ByVal leng As DWord, ByVal flags As Long) As Long
    Function = NngSend(socket, buf, leng, flags)
  End Function

  ' <summary>
  ' SockSendStr
  ' </summary>
  ' <param name="socket">Long</param>
  ' <param name="msg">String</param>
  ' <param name="flags">Long</param>
  ' <returns>Returns long.</returns>
  Function SockSendStr(ByVal socket As Long, ByVal msg As String, ByVal flags As Long) As Long
    Function = NngSendString(socket, msg, flags)
  End Function

  ' <summary>
  ' SockRecv
  ' </summary>
  ' <param name="socket">Long</param>
  ' <param name="buf">Long</param>
  ' <param name="buflen">DWord</param>
  ' <param name="flags">Long</param>
  ' <returns>Returns long.</returns>
  Function SockRecv(ByVal socket As Long, ByVal buf As Long, ByVal buflen As DWord, ByVal flags As Long) As Long
    Function = NngRecvBuffer(socket, buf, buflen, flags)
  End Function

  ' <summary>
  ' SockSetMs
  ' </summary>
  ' <param name="lId">Long</param>
  ' <param name="sOption">String</param>
  ' <param name="lMs">Long</param>
  ' <returns>Returns long.</returns>
  Function SockSetMs(ByVal lId As Long, ByVal sOption As String, ByVal lMs As Long) As Long
    If sOption = "recv-timeout" Then
      Function = NngSetRecvTimeoutMs(lId, lMs)
    ElseIf sOption = "surveyor:survey-time" Then
      Function = NngSetSurveyTimeMs(lId, lMs)
    Else
      Function = NngSetOptMs(lId, sOption, lMs)
    End If
  End Function

  ' <summary>
  ' Subscribe
  ' </summary>
  ' <param name="socket">Long</param>
  ' <param name="topic">String</param>
  ' <returns>Returns long.</returns>
  Function Subscribe(ByVal socket As Long, ByVal topic As String) As Long
    Function = NngSub0Subscribe(socket, topic)
  End Function

  ' <summary>
  ' Unsubscribe
  ' </summary>
  ' <param name="socket">Long</param>
  ' <param name="topic">String</param>
  ' <returns>Returns long.</returns>
  Function Unsubscribe(ByVal socket As Long, ByVal topic As String) As Long
    Function = NngSub0Unsubscribe(socket, topic)
  End Function
End Type
