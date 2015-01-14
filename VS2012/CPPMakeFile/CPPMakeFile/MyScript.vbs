CallTheAction()
Public Function CallTheAction()
  MsgBox "OK"
  CallTheAction = msiDoActionStatusSuccess
  MsgBox "DeleteConfigFolder:" & "C:\Program Files (x86)\SetupProject2\" & "Config\"
 On Error Resume Next
 Set objFso = CreateObject("Scripting.FileSystemObject")
 strFolderPath = "C:\Program Files (x86)\SetupProject2\" & "Config\"
 objFso.DeleteFolder(strFolderPath)
End Function