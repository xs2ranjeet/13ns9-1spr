#include "MyWndClass.h"
//----------------------
MyWndClass::MyWndClass() {	
	SetWindowLong( hMainWnd, GWL_USERDATA, (LONG)this);
	SetWindowLong( hMainWnd, GWL_WNDPROC, (LONG)WndProcStub); 
};
//----------------------
MyWndClass::MyWndClass(HINSTANCE hInstancem):hInstance(hInstancem) {
	SetWindowLong( hMainWnd, GWL_USERDATA, (LONG)this);
	SetWindowLong( hMainWnd, GWL_WNDPROC, (LONG)WndProcStub);
};
//----------------------
LRESULT CALLBACK MyWndClass::WndProcStub(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam) {
	pMyWndClass pThis = (pMyWndClass)GetWindowLong(hWnd, GWL_USERDATA);
	return pThis->WndProc(hWnd, msg, wParam, lParam);
};
//----------------------
const LOGFONT MyWndClass::DefineFont(HWND hWnd){
	LOGFONT tmpFont;
	
    tmpFont.lfHeight = 16;
    tmpFont.lfWidth =12;
    tmpFont.lfEscapement =0;
    tmpFont.lfOrientation =0;
    tmpFont.lfWeight = FW_BOLD;
    tmpFont.lfItalic = true;
    tmpFont.lfUnderline = true;
    tmpFont.lfStrikeOut = true;
    tmpFont.lfCharSet = ANSI_CHARSET;
    tmpFont.lfOutPrecision = OUT_DEFAULT_PRECIS;
    tmpFont.lfClipPrecision  = CLIP_DEFAULT_PRECIS;
    tmpFont.lfQuality = CLEARTYPE_QUALITY;
    tmpFont.lfPitchAndFamily = DEFAULT_PITCH;
	lstrcpy(tmpFont.lfFaceName,"Arial");

	return tmpFont;
};
//-----------------------
void MyWndClass::ANSI_Tabbed_Out(HWND hWnd){
	RECT rect;
	::GetClientRect(hWnd,&rect);
	HDC hDC = ::GetDC(hWnd);
	//char text[260];
	//---------------
	//POINT center;
	//center.x = (rect.left+rect.right)/2;
	//center.y = (rect.bottom+rect.top)/2;
	//int x=10, y=10;
	//int h=30;
	//char s[2] ={'\n','\n'};
	//char k=0;
	//	for(int i=0; i<16; ++i)
	//	for(int j=0; j<16; ++j){
	//		s[0]=k;
	//		++k;
	//		//::TextOut(hDC,center.x-x+j*h, center.y-y+i*h,s,1);
	//		::TabbedTextOut(hDC,x,y,s,16*16,1,-1,1);
	//	}	
	////---
	////::DrawText(hDC,text,-1,&rect,DT_VCENTER| DT_SINGLELINE | DT_CENTER);
	////---
	//---------------------------------------------
	int tabstop[] = {-120, 125, 250 };

	const TCHAR * lines[] ={
		"Group" "\t" "Result" "\t" "Function"    "\t" "Parametrs",
		"Font"  "\t" "DWORD"  "\t" "GetFontData" "\t" "(HDC hDC, ...)",
		"Text"  "\t" "BOOL"   "\t" "TextOut"     "\t" "(HDC hDC, ...)"
	  };

	int x = 150;
	int y = 50;

	for ( int i=0; i<3; i++ )
	  y += HIWORD(TabbedTextOut(hDC, x, y, lines[i], strlen(lines[i]), sizeof(tabstop) / sizeof(tabstop[0]), tabstop, x)); 
	//---------------------------------------------
	::ReleaseDC(hWnd,hDC);
	//::InvalidateRect(hWnd,&rect,false);
};
//-----------------------
void MyWndClass::ANSI_OUT(HWND hWnd){
	RECT rect;
	::GetClientRect(hWnd,&rect);
	HDC hDC = ::GetDC(hWnd);
	//char text[260];
	//---------------
	POINT center;
	center.x = (rect.left+rect.right)/2;
	center.y = (rect.bottom+rect.top)/2;
	//::SetTextAlign(hDC,TA_CENTER);
	int x=10, y=10;
	int h=30;
	char s[2] ={'\n','\n'};
	char k=0;
		for(int i=0; i<16; ++i)
		for(int j=0; j<16; ++j){
			s[0]=k;
			++k;
			::TextOut(hDC,center.x/2-x+j*h, center.y/2-y+i*h,s,1);
			//::TabbedTextOut(hDC,x,y,s,16*16,
		}	
	//---
	//::DrawText(hDC,text,-1,&rect,DT_VCENTER| DT_SINGLELINE | DT_CENTER);
	//---
	::ReleaseDC(hWnd,hDC);
	::InvalidateRect(hWnd,&rect,false);
};
//----------------------
LRESULT MyWndClass::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	PAINTSTRUCT ps;
	RECT rect;
	//-------------
	switch(uMsg) {
	case WM_PAINT: {
		::BeginPaint(hWnd, &ps);
		    ::GetClientRect(hWnd,&rect);
			HDC hDC = ::GetDC(hWnd);
		//-------------1---------		
			//LOGFONT logFont = DefineFont(hWnd);
			//HFONT hFon = ::CreateFontIndirect(&logFont);
			//HFONT oldFont = (HFONT)::SelectObject(hDC,hFon);
			////---
			//::DrawText(hDC,"Some logical font",-1,&rect,DT_VCENTER|DT_WORDBREAK | DT_SINGLELINE | DT_CENTER);
			//::SetTextAlign(hDC,TA_LEFT);
			////::SetTextAlign(hDC,TA_RIGHT);
			//::TextOut(hDC,100,100,"Text Out",lstrlen("Text Out"));
			////---
			//::SelectObject(hDC,oldFont);
			//::DeleteObject(hFon);	
		//-------------2---------------
		ANSI_OUT(hWnd);
		//ANSI_Tabbed_Out(hWnd);
		//---------------------------
			::ReleaseDC(hWnd,hDC);
		//----------------------
		::EndPaint(hWnd, &ps);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	};
	return 0;
};
//---------------------
void MyWndClass::CreateWndClass() {
	this->szClassName="MyClassTimer";
	//--
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProcStub;
	wc.cbClsExtra = 0;
	wc.cbWndExtra=0;
	wc.hInstance = this->hInstance;
	wc.hIcon = LoadIcon(NULL,IDI_EXCLAMATION);
	wc.hCursor = LoadCursor(NULL,IDC_HAND);	
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szClassName.c_str();
	wc.hIconSm = LoadIcon(NULL, IDI_EXCLAMATION);
};
//---
int MyWndClass::CreateWnd(){
	if(!RegisterClassEx(&this->wc)){
		throw "Error can't register window class";		
	};
	//--
	hMainWnd=CreateWindow(this->szClassName.c_str(), "Hallo man ", WS_OVERLAPPEDWINDOW,
		100, 100, 600, 600,(HWND)NULL,
		(HMENU)NULL, (HINSTANCE)this->hInstance, NULL);
	
	if(!hMainWnd){
		throw "Cant create main window";		
	};
	return 0;
};
//---
int MyWndClass::Run() {
	//--
	CreateWndClass();
	//--
	CreateWnd();
	//--
	ShowWindow(hMainWnd, SW_SHOWNORMAL);
	//--
	while(GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	};
	return msg.wParam;
};
//---