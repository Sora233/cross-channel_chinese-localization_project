// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once
#pragma pack( 1 )

#include "targetver.h"
#include "resource.h"

#define DLLIMPORT extern "C" __declspec (dllexport)
//#define DEBUG
//#define SETALLLOG // a simple hijack dll
#define CHECKARC // need to check arc size

#define _CRT_SECURE_NO_WARNINGS

#define WIN32_LEAN_AND_MEAN             //  从 Windows 头文件中排除极少使用的信息
#include <windows.h>
#include <shlobj.h>
#include <shellapi.h>
#include <CommCtrl.h>
#include <mmsystem.h>
#include <cstdio>
#include <cstdlib>
#include <string>
#include "textFinder.h"
#pragma comment(lib, "WINMM.LIB")

using namespace std;

#include "E:\\libs\\OpenCV-2.1.0\\include\\opencv\\cv.h"
#include "E:\\libs\\OpenCV-2.1.0\\include\\opencv\\cxcore.h"
#include "E:\\libs\\OpenCV-2.1.0\\include\\opencv\\highgui.h"
#pragma comment( lib, "E:\\libs\\OpenCV-2.1.0\\lib\\cv210.lib" )
#pragma comment( lib, "E:\\libs\\OpenCV-2.1.0\\lib\\cxcore210.lib" )
#pragma comment( lib, "E:\\libs\\OpenCV-2.1.0\\lib\\highgui210.lib" )
using namespace cv;

// TODO: 在此处引用程序需要的其他头文件
DLLIMPORT void HelloWorld( char * );
DLLIMPORT LONG HegCloseKey( HKEY );
DLLIMPORT LONG HegCreateKeyExA( HKEY, LPCSTR, DWORD, LPSTR, DWORD, REGSAM, LPSECURITY_ATTRIBUTES, PHKEY, LPDWORD );
DLLIMPORT LONG HegOpenKeyExA( HKEY, LPCSTR, DWORD, REGSAM, PHKEY );
DLLIMPORT LONG HegQueryValueExA( HKEY, LPCSTR, LPDWORD, LPDWORD, LPBYTE, LPDWORD lpcbData );
DLLIMPORT LONG HegSetValueExA(HKEY, LPCSTR, DWORD, DWORD, CONST BYTE *, DWORD cbData);

#pragma pack(1)

// Arc Strutures
typedef struct {
	unsigned long section_count; // 区段数
} ARCHDR; // 归档头部

typedef struct {
	char          type[ 4 ];   // "PNG", "MOS", "OGG"
	unsigned long entry_count; // 文件数
	unsigned long toc_offset;  // 开始处的偏移地址
} ARCSECTHDR; // 归档区段细节

typedef struct {
	char          filename[ 13 ];
	unsigned long length; // 文件长度
	unsigned long offset; // 文件开始处偏移地址
} ARCENTRY; // 文件细节

/* 键名表要按照数据结构的顺序来 */
#define TableSize 52
const static char KeyTable[ TableSize ][ 20 ] = {
	"Adapter",
	"DisplayMode_Window",
	"Size_Full.Width",
	"Size_Full.Height",
	"Size_Window.Width",
	"Size_Window.Height",
	"FullScreen",
	"BackBuffer.Width",
	"BackBuffer.Height",
	"KeepAspectRatio",
	"VSync",
	"UnDivideTexture",
	"DisableDialog",
	"UseCV",
	"JoyPad",

	"InstallType",
	"InstallDir",
	"InstallSrc",
	"FontName",
	"SpecialFontName",
	"AutoMsg",
	"AutoSkip",
	"CursorHide",
	"CursorTime", // OTOMEGA
	"D3D.DisableTnL",
	"D3D.Tex16",
	"DeactivePlay",
	"Dialog",
	"DisableCursor",
	"DisablePan",
	"DisableQuick",
	"DisplayMode",
	"EffectSkip",
	"FontEdge",
	"LogAlpha", // OTOMEGA
	"MsgAlpha",
	"MsgPos",
	"MsgSpeed",
	"Mute",
	"RButtonMode",
	"SelAuto",
	"SelSkip",
	"SimpleWindow",
	"SkipIcon",
	"SkipType",
	"SysVoice",
	"TextColor", // OTOMEGA
	"UseDefaultFont",
	"UseFilt",
	"VoiceSkip",
	"Volume",
	"WndPos"
};

/* 直接把所有东西都放过来，读写都是二进制 ( Need to be decryped ) */
typedef struct {
	DWORD Adapter,
		DisplayMode_Window,
		Size_Full_Width, Size_Full_Height,
		Size_Window_Width, Size_Window_Height,
		FullScreen,
		BackBuffer_Width, BackBuffer_Height,
		KeepAspectRatio,
		VSync,
		UnDivideTexture,
		DisableDialog,
		UseCV,
		JoyPad;
	char InstallType[ 4 ],
		InstallDir[ 260 ], InstallSrc[ 260 ],
		FontName[ 1024 ], SpecialFontName[ 1024 ],
		AutoMsg[ 4 ], AutoSkip[ 4 ],
		CursorHide[ 4 ],
		CursorTime[ 4 ], // OTOMEGA
		D3D_DisableTnL[ 4 ], D3D_Tex16[ 4 ],
		DeactivePlay[ 4 ],
		Dialog[ 4 ],
		DisableCursor[ 4 ],
		DisablePan[ 4 ],
		DisableQuick[ 4 ],
		DisplayMode[ 4 ],
		EffectSkip[ 4 ],
		FontEdge[ 4 ],
		LogAlpha[ 4 ], // OTOMEGA
		MsgAlpha[ 4 ],
		MsgPos[ 8 ],
		MsgSpeed[ 4 ],
		Mute[ 84 ],
		RButtonMode[ 4 ],
		SelAuto[ 4 ], SelSkip[ 4 ],
		SimpleWindow[ 4 ],
		SkipIcon[ 4 ], SkipType[ 4 ],
		SysVoice[ 4 ],
		TextColor[ 4 ], // OTOMEGA
		UseDefaultFont[ 4 ],
		UseFilt[ 4 ],
		VoiceSkip[ 4 ],
		Volume[ 84 ],
		WndPos[ 8 ];
} RegCC;

// Global vars
static FILE *FakeReg;
static RegCC Reg;
const static char ForSafe[ 1024 ] = { 0 };
static int DllErrorStatus;
static int i;

#ifdef DEBUG
static DWORD LoopCount;
static FILE *LogFile;
#endif

// Dialog Size
#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 250
