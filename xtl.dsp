# Microsoft Developer Studio Project File - Name="xtl" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=xtl - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "xtl.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "xtl.mak" CFG="xtl - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "xtl - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "xtl - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=xicl6.exe
RSC=rc.exe

!IF  "$(CFG)" == "xtl - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GR /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x406 /d "NDEBUG"
# ADD RSC /l 0x406 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "xtl - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GR /GX /ZI /Od /I "include" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE RSC /l 0x406 /d "_DEBUG"
# ADD RSC /l 0x406 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "xtl - Win32 Release"
# Name "xtl - Win32 Debug"
# Begin Group "examples"

# PROP Default_Filter ""
# Begin Group "auto"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\examples\auto\auto.cpp

# PROP Exclude_From_Build 1

# End Source File
# End Group
# Begin Group "bench"

# PROP Default_Filter ""
# Begin Group "memcpy"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\examples\bench\memcpy\tests.cpp

# PROP Exclude_From_Build 1

# End Source File
# End Group
# Begin Group "rpcgen"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\examples\bench\rpcgen\tests.c

# PROP Exclude_From_Build 1

# End Source File
# End Group
# Begin Group "vxtl"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\examples\bench\vxtl\giop.cpp

# PROP Exclude_From_Build 1

# End Source File
# Begin Source File

SOURCE=.\examples\bench\vxtl\raw.cpp

# PROP Exclude_From_Build 1

# End Source File
# Begin Source File

SOURCE=.\examples\bench\vxtl\xdr.cpp

# PROP Exclude_From_Build 1

# End Source File
# End Group
# Begin Group "xtl"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\examples\bench\xtl\giop.cpp

# PROP Exclude_From_Build 1

# End Source File
# Begin Source File

SOURCE=.\examples\bench\xtl\raw.cpp

# PROP Exclude_From_Build 1

# End Source File
# Begin Source File

SOURCE=.\examples\bench\xtl\xdr.cpp

# PROP Exclude_From_Build 1

# End Source File
# End Group
# End Group
# Begin Group "graph"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\examples\graph\gtest.cpp

# PROP Exclude_From_Build 1

# End Source File
# End Group
# Begin Group "smart"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\examples\smart\smart.cpp

# PROP Exclude_From_Build 1

# End Source File
# End Group
# Begin Group "tests"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\examples\tests\compare.cpp
# End Source File
# Begin Source File

SOURCE=.\examples\tests\giopi.cpp
# End Source File
# Begin Source File

SOURCE=.\examples\tests\giopo.cpp
# End Source File
# Begin Source File

SOURCE=.\examples\tests\main.cpp
# End Source File
# Begin Source File

SOURCE=.\examples\tests\rawi.cpp
# End Source File
# Begin Source File

SOURCE=.\examples\tests\rawo.cpp
# End Source File
# Begin Source File

SOURCE=.\examples\tests\xdri.cpp
# End Source File
# Begin Source File

SOURCE=.\examples\tests\xdro.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\examples\alltests.h
# End Source File
# End Group
# Begin Group "include"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\include\xtl\autoio.h
# End Source File
# Begin Source File

SOURCE=.\include\xtl\byteswap.h
# End Source File
# Begin Source File

SOURCE=.\include\xtl\config.h
# End Source File
# Begin Source File

SOURCE=.\include\xtl\giop.h
# End Source File
# Begin Source File

SOURCE=.\include\xtl\graphio.h
# End Source File
# Begin Source File

SOURCE=.\include\xtl\macros.h
# End Source File
# Begin Source File

SOURCE=.\include\xtl\objio.h
# End Source File
# Begin Source File

SOURCE=.\include\xtl\text.h
# End Source File
# Begin Source File

SOURCE=.\include\xtl\vobjio.h
# End Source File
# Begin Source File

SOURCE=.\include\xtl\xdr.h
# End Source File
# End Group
# End Target
# End Project
