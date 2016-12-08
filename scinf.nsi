; scinf.nsi
;--------------------------------

!include MUI2.nsh
!define MUI_ABORTWARNING

; The name of the installer
Name "ScInf"
AddBrandingImage right 200
BrandingText "ScInf v0.61 20120121 (c) baltasarq 2010/11/12"
Icon "scinf.ico"
UninstallIcon "scinf.ico"

; The file to write
OutFile "scinf.exe"

; The default installation directory
InstallDir $PROGRAMFILES\scinf

; Request application privileges for WinVista, Win7
RequestExecutionLevel admin

; Languages -------------------------
!insertmacro MUI_LANGUAGE "Spanish"
!insertmacro MUI_LANGUAGE "English"

; Pages -------------------------
;!insertmacro MUI_PAGE_LICENSE
Page license
LicenseLangString license ${LANG_SPANISH} license_ES.txt
LicenseLangString license ${LANG_ENGLISH} license_EN.txt
LicenseData $(license)

!insertmacro MUI_PAGE_COMPONENTS
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES

!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES

; Texts --------------------------
LangString "MUI_TEXT_DIRECTORY_TITLE" ${LANG_ENGLISH} "ScInf"
LangString "MUI_TEXT_DIRECTORY_TITLE" ${LANG_SPANISH} "ScInf"

LangString "MUI_TEXT_COMPONENTS_TITLE" ${LANG_ENGLISH} "ScInf"
LangString "MUI_TEXT_COMPONENTS_TITLE" ${LANG_SPANISH} "ScInf"

LangString "MUI_TEXT_INSTALLING_TITLE" ${LANG_ENGLISH} "ScInf"
LangString "MUI_TEXT_INSTALLING_TITLE" ${LANG_SPANISH} "ScInf"

LangString "MUI_TEXT_UNINSTALLING_TITLE" ${LANG_ENGLISH} "ScInf"
LangString "MUI_TEXT_UNINSTALLING_TITLE" ${LANG_SPANISH} "ScInf"

LangString "secTranslateText" ${LANG_ENGLISH} "Translate editor into Spanish"
LangString "secTranslateText" ${LANG_SPANISH} "Traducir editor al español"

LangString "secMenuShortcutsText" ${LANG_ENGLISH} "Shortcuts in the start menu"
LangString "secMenuShortcutsText" ${LANG_SPANISH} "Accesos en el menú de inicio"

LangString "secDesktopShortcutsText" ${LANG_ENGLISH} "Shortcuts in the desktop"
LangString "secDesktopShortcutsText" ${LANG_SPANISH} "Accesos en el escritorio"


LangString "secTranslateText" ${LANG_ENGLISH} "Translate editor into Spanish"
LangString "secTranslateText" ${LANG_SPANISH} "Traducir editor al español"

; Functions ----------------------
Function .onInit
  !insertmacro MUI_LANGDLL_DISPLAY
FunctionEnd

Function un.onInit
  !insertmacro MUI_LANGDLL_DISPLAY
FunctionEnd

; Install ------------------------

; The stuff to install
Section "ScInf" secScInfDistribution

  SectionIn RO

  ; Set output path to the installation directory.
  SetOutPath $INSTDIR

  ; Put files here
  File /r /x "scinf.exe" /x "scinf-*.exe" "*.*"

;  SetBrandingImage /RESIZETOFIT scinf.bmp

  ; Write the installation path into the registry
  WriteRegStr HKLM SOFTWARE\scinf "Install_Dir" "$INSTDIR"

  ; Write the uninstall keys for Windows
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\scinf" "DisplayName" "ScInf"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\scinf" "UninstallString" '"$INSTDIR\uninstall.exe"'
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\scinf" "NoModify" 1
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\scinf" "NoRepair" 1
  WriteUninstaller "uninstall.exe"

SectionEnd

Section /o $(secTranslateText) secTranslate

  Rename /REBOOTOK "$INSTDIR\locale.es.properties" "$INSTDIR\locale.properties"

SectionEnd

Section $(secMenuShortcutsText) secMenuShortcuts

  CreateDirectory "$SMPROGRAMS\scinf"
  CreateShortCut "$SMPROGRAMS\scinf\Uninstall.lnk" "$INSTDIR\uninstall.exe" "" "$INSTDIR\uninstall.exe" 0
  CreateShortCut "$SMPROGRAMS\scinf\scinf.lnk" "$INSTDIR\scite.exe" "" "$INSTDIR\scite.exe" 0
  CreateShortCut "$SMPROGRAMS\scinf\Gargoyle.lnk" "$INSTDIR\bin\gargoyle\gargoyle.exe" "" "$INSTDIR\bin\gargoyle\gargoyle.exe" 0

SectionEnd

Section $(secDesktopShortcutsText) secDesktopShortcuts

  CreateShortCut "$DESKTOP\scinf.lnk" "$INSTDIR\scite.exe" "" "$INSTDIR\scite.exe" 0
  CreateShortCut "$DESKTOP\Gargoyle.lnk" "$INSTDIR\bin\gargoyle\gargoyle.exe" "" "$INSTDIR\bin\gargoyle\gargoyle.exe" 0

SectionEnd

;--------------------------------

; Uninstaller

Section "Uninstall"

  ; Remove registry keys
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\scinf"
  DeleteRegKey HKLM SOFTWARE\scinf

  ; Remove files and uninstaller
  RmDir /r /REBOOTOK $INSTDIR

  ; Remove shortcuts, if any
  Delete "$SMPROGRAMS\scinf\*.*"

  ; Remove directories used
  RMDir "$SMPROGRAMS\scinf"
  RMDir "$INSTDIR"

SectionEnd

; Sections descriptions --------------

LangString DESC_secScinfDistribution ${LANG_ENGLISH} "ScInf"
LangString DESC_secTranslate ${LANG_ENGLISH} "Translate the program into Spanish."
LangString DESC_secMenuShortcuts ${LANG_ENGLISH} "Start menu Scinf shortcuts."
LangString DESC_secDesktopShortcuts ${LANG_ENGLISH} "Desktop Scinf shortcuts."

LangString DESC_secScinfDistribution ${LANG_SPANISH} "ScInf"
LangString DESC_secTranslate ${LANG_SPANISH} "Traduce el editor al español."
LangString DESC_secMenuShortcuts ${LANG_SPANISH} "Coloca accesos directos en el menú de inicio."
LangString DESC_secDesktopShortcuts ${LANG_SPANISH} "Coloca accesos directos en el escritorio."

!insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
  !insertmacro MUI_DESCRIPTION_TEXT ${secScinfDistribution} $(DESC_secScinfDistribution)
  !insertmacro MUI_DESCRIPTION_TEXT ${secTranslate} $(DESC_secTranslate)
  !insertmacro MUI_DESCRIPTION_TEXT ${secMenuShortcuts} $(DESC_secMenuShortcuts)
  !insertmacro MUI_DESCRIPTION_TEXT ${secDesktopShortcuts} $(DESC_secDesktopShortcuts)
!insertmacro MUI_FUNCTION_DESCRIPTION_END


