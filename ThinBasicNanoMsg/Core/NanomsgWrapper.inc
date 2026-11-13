'--------------------------------------------------------------------------------------------
'  Copyright (c) Ji-Feng Tsai. All rights reserved.
'  Code released under the MIT license.
'--------------------------------------------------------------------------------------------

' OOP façade over the procedural API.
#INCLUDE Once "NanoMsg.inc"

' Type

Type LibNanomsgRuntime
  Public

  ' <summary>
  ' GetErrno
  ' </summary>
  ' <returns>Returns long.</returns>
  Function GetErrno() As Long
    Function = NnErrno()
  End Function

  ' <summary>
  ' GetStrerror
  ' </summary>
  ' <param name="errnum">Long</param>
  ' <returns>Returns string.</returns>
  Function GetStrerror(ByVal errnum As Long) As String
    Function = NnStrerrorString(errnum)
  End Function

  ' <summary>
  ' GetSymbol
  ' </summary>
  ' <param name="index">Long</param>
  ' <param name="value">Long</param>
  ' <returns>Returns string.</returns>
  Function GetSymbol(ByVal index As Long, ByRef value As Long) As String
    Local p As Long

    p = NnSymbol(index, value)
    If p Then
      Function = Peek$(ASCIIZ, p)
    Else
      Function = ""
    End If
  End Function

  ' <summary>
  ' Term
  ' </summary>
  ' <returns>Returns void.</returns>
  Sub Term()
    NnTerm()
  End Sub
End Type

Type LibNanomsgMessage
  Public

  ' <summary>
  ' Allocmsg
  ' </summary>
  ' <param name="size">DWord</param>
  ' <param name="type_">Long</param>
  ' <returns>Returns long.</returns>
  Function Allocmsg(ByVal size As DWord, ByVal type_ As Long) As Long
    Function = NnAllocmsg(size, type_)
  End Function

  ' <summary>
  ' Reallocmsg
  ' </summary>
  ' <param name="msg">Long</param>
  ' <param name="size">DWord</param>
  ' <returns>Returns long.</returns>
  Function Reallocmsg(ByVal msg As Long, ByVal size As DWord) As Long
    Function = NnReallocmsg(msg, size)
  End Function

  ' <summary>
  ' Freemsg
  ' </summary>
  ' <param name="msg">Long</param>
  ' <returns>Returns long.</returns>
  Function Freemsg(ByVal msg As Long) As Long
    Function = NnFreemsg(msg)
  End Function
End Type

Type LibNanomsgSocket
  Public

  ' <summary>
  ' NewSocket
  ' </summary>
  ' <param name="domain">Long</param>
  ' <param name="protocol">Long</param>
  ' <returns>Returns socket handle.</returns>
  Function NewSocket(ByVal domain As Long, ByVal protocol As Long) As Long
    Function = NnSocket(domain, protocol)
  End Function

  ' <summary>
  ' SockClose
  ' </summary>
  ' <param name="socket">Long</param>
  ' <returns>Returns long.</returns>
  Function SockClose(ByVal socket As Long) As Long
    Function = NnClose(socket)
  End Function

  ' <summary>
  ' SockSetsockopt
  ' </summary>
  ' <param name="socket">Long</param>
  ' <param name="level">Long</param>
  ' <param name="options">Long</param>
  ' <param name="optval">Long</param>
  ' <param name="optvallen">DWord</param>
  ' <returns>Returns long.</returns>
  Function SockSetsockopt(ByVal socket As Long, ByVal level As Long, ByVal options As Long, ByVal optval As Long, ByVal optvallen As DWord) As Long
    Function = NnSetsockopt(socket, level, options, optval, optvallen)
  End Function

  ' <summary>
  ' SockSetsockoptStr
  ' </summary>
  ' <param name="socket">Long</param>
  ' <param name="level">Long</param>
  ' <param name="options">Long</param>
  ' <param name="optval">String</param>
  ' <returns>Returns long.</returns>
  Function SockSetsockoptStr(ByVal socket As Long, ByVal level As Long, ByVal options As Long, ByVal optval As String) As Long
    Function = NnSetsockoptString(socket, level, options, optval)
  End Function

  ' <summary>
  ' SockSetsockoptInt
  ' </summary>
  ' <param name="socket">Long</param>
  ' <param name="level">Long</param>
  ' <param name="options">Long</param>
  ' <param name="optval">Long</param>
  ' <returns>Returns long.</returns>
  Function SockSetsockoptInt(ByVal socket As Long, ByVal level As Long, ByVal options As Long, ByVal optval As Long) As Long
    Function = NnSetsockoptInt(socket, level, options, optval)
  End Function

  ' <summary>
  ' SockGetsockoptInt
  ' </summary>
  ' <param name="socket">Long</param>
  ' <param name="level">Long</param>
  ' <param name="options">Long</param>
  ' <param name="optval">Long</param>
  ' <returns>Returns long.</returns>
  Function SockGetsockoptInt(ByVal socket As Long, ByVal level As Long, ByVal options As Long, ByRef optval As Long) As Long
    Function = NnGetsockoptInt(socket, level, options, optval)
  End Function

  ' <summary>
  ' SockBind
  ' </summary>
  ' <param name="socket">Long</param>
  ' <param name="addr">String</param>
  ' <returns>Returns long.</returns>
  Function SockBind(ByVal socket As Long, ByVal addr As String) As Long
    Function = NnBind(socket, addr)
  End Function

  ' <summary>
  ' SockConnect
  ' </summary>
  ' <param name="socket">Long</param>
  ' <param name="addr">String</param>
  ' <returns>Returns long.</returns>
  Function SockConnect(ByVal socket As Long, ByVal addr As String) As Long
    Function = NnConnect(socket, addr)
  End Function

  ' <summary>
  ' SockShutdown
  ' </summary>
  ' <param name="socket">Long</param>
  ' <param name="how">Long</param>
  ' <returns>Returns long.</returns>
  Function SockShutdown(ByVal socket As Long, ByVal how As Long) As Long
    Function = NnShutdown(socket, how)
  End Function

  ' <summary>
  ' SockSend
  ' </summary>
  ' <param name="socket">Long</param>
  ' <param name="buf">Long</param>
  ' <param name="buflen">DWord</param>
  ' <param name="flags">Long</param>
  ' <returns>Returns long.</returns>
  Function SockSend(ByVal socket As Long, ByVal buf As Long, ByVal buflen As DWord, ByVal flags As Long) As Long
    Function = NnSend(socket, buf, buflen, flags)
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
    Function = NnRecv(socket, buf, buflen, flags)
  End Function

  ' <summary>
  ' SockSendStr
  ' </summary>
  ' <param name="socket">Long</param>
  ' <param name="msg">String</param>
  ' <param name="flags">Long</param>
  ' <returns>Returns long.</returns>
  Function SockSendStr(ByVal socket As Long, ByVal msg As String, ByVal flags As Long) As Long
    Function = NnSendString(socket, msg, flags)
  End Function

  ' <summary>
  ' DoPoll
  ' </summary>
  ' <param name="fds">Long</param>
  ' <param name="nfds">Long</param>
  ' <param name="timeout">Long</param>
  ' <returns>Returns long.</returns>
  Function DoPoll(ByVal fds As Long, ByVal nfds As Long, ByVal timeout As Long) As Long
    Function = NnPoll(fds, nfds, timeout)
  End Function

  ' <summary>
  ' GetStatistic
  ' </summary>
  ' <param name="socket">Long</param>
  ' <param name="stat">Long</param>
  ' <returns>Returns DWord.</returns>
  Function GetStatistic(ByVal socket As Long, ByVal stat As Long) As DWord
    Function = NnGetStatistic(socket, stat)
  End Function
End Type
