'--------------------------------------------------------------------------------------------
'  Copyright (c) Ji-Feng Tsai. All rights reserved.
'  Code released under the MIT license.
'--------------------------------------------------------------------------------------------

' Package DLLs live under Library\x86 (x86 only; ThinBasic cannot load x64 nng).
' ThinBasic #INCLUDE is script-relative, but Declare Lib uses the process CWD.
' Include this file before other Core modules that Declare Lib "nng.dll".

' <summary>
' NngSetCurrentDirectory
' </summary>
' <param name="lpPathName">Asciiz</param>
' <returns>Returns long.</returns>
Declare Function NngSetCurrentDirectory Lib "kernel32.dll" Alias "SetCurrentDirectoryA" (ByVal lpPathName As Asciiz) As Long

' <summary>
' NngLibraryPathSet
' </summary>
' <returns>Returns void.</returns>
Sub NngLibraryPathSet()
  Local sPath As String

  ' Scripts in ThinBasicNNG\
  sPath = APP_SourcePath & "Library\x86"
  If NngSetCurrentDirectory(sPath) <> 0 Then Exit Sub
  ' Scripts in ThinBasicNNG\Example\
  sPath = APP_SourcePath & "..\Library\x86"
  If NngSetCurrentDirectory(sPath) <> 0 Then Exit Sub
  ' Scripts in ThinBasicNNG\Example\Module\
  sPath = APP_SourcePath & "..\..\Library\x86"
  NngSetCurrentDirectory(sPath)
End Sub

' Switch CWD so subsequent Declare Lib "nng.dll" resolves package DLLs.
NngLibraryPathSet()
