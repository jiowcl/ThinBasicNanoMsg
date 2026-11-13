'--------------------------------------------------------------------------------------------
'  Copyright (c) Ji-Feng Tsai. All rights reserved.
'  Code released under the MIT license.
'--------------------------------------------------------------------------------------------

' Package DLLs live under Library\x86 (x86 only; ThinBasic cannot load x64 nanomsg).
' ThinBasic #INCLUDE is script-relative, but Declare Lib uses the process CWD.
' Include this file before other Core modules that Declare Lib "nanomsg.dll".

' <summary>
' NnSetCurrentDirectory
' </summary>
' <param name="lpPathName">Asciiz</param>
' <returns>Returns long.</returns>
Declare Function NnSetCurrentDirectory Lib "kernel32.dll" Alias "SetCurrentDirectoryA" (ByVal lpPathName As Asciiz) As Long

' <summary>
' NnLibraryPathSet
' </summary>
' <returns>Returns void.</returns>
Sub NnLibraryPathSet()
  Local sPath As String

  ' Scripts in ThinBasicNanoMsg\
  sPath = APP_SourcePath & "Library\x86"
  If NnSetCurrentDirectory(sPath) <> 0 Then Exit Sub
  ' Scripts in ThinBasicNanoMsg\Example\
  sPath = APP_SourcePath & "..\Library\x86"
  If NnSetCurrentDirectory(sPath) <> 0 Then Exit Sub
  ' Scripts in ThinBasicNanoMsg\Example\Module\
  sPath = APP_SourcePath & "..\..\Library\x86"
  NnSetCurrentDirectory(sPath)
End Sub

' Switch CWD so subsequent Declare Lib "nanomsg.dll" resolves package DLLs.
NnLibraryPathSet()
