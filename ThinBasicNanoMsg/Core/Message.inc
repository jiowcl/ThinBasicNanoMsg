'--------------------------------------------------------------------------------------------
'  Copyright (c) Ji-Feng Tsai. All rights reserved.
'  Code released under the MIT license.
'--------------------------------------------------------------------------------------------

' Declare Function

' <summary>
' NnAllocmsg
' </summary>
' <param name="size">DWord</param>
' <param name="type_">Long</param>
' <returns>Returns message buffer pointer.</returns>
Declare Function NnAllocmsg Lib "nanomsg.dll" Alias "nn_allocmsg" (ByVal size As DWord, ByVal type_ As Long) As Long

' <summary>
' NnReallocmsg
' </summary>
' <param name="msg">Long</param>
' <param name="size">DWord</param>
' <returns>Returns message buffer pointer.</returns>
Declare Function NnReallocmsg Lib "nanomsg.dll" Alias "nn_reallocmsg" (ByVal msg As Long, ByVal size As DWord) As Long

' <summary>
' NnFreemsg
' </summary>
' <param name="msg">Long</param>
' <returns>Returns long.</returns>
Declare Function NnFreemsg Lib "nanomsg.dll" Alias "nn_freemsg" (ByVal msg As Long) As Long
