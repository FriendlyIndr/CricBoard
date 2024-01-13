#include <windows.h>         //win32 api
#include <iostream>
#include <string>            //for converting global integer variables to wchar_t
#include <cwchar>
using namespace std;

#define FILE_MENU_NEW 1
#define FILE_MENU_OPEN 2
#define FILE_MENU_EXIT 3
#define HELP 30
#define _SUBMIT 4
#define DLG_DELETEITEM 5
#define _WICKET 6
#define _DOT 7
#define _GIVECH 8            //macros defined for each action/choice
#define _SINGLE 9
#define _WIDE 10
#define _NOB 11
#define _RO 12
#define _DOUBLE 13
#define _WIDE2 14
#define _NOB2 15
#define _RO2 16
#define _TRIPLE 17
#define _WIDE3 18
#define _NOB3 19
#define _RO3 20
#define _FOUR 21
#define _WIDE4 22
#define _NOB4 23
#define _RO4 24
#define _WIDE5 25
#define _NOB5 26
#define _SIX 27
#define _WIDE7 28
#define _NOB7 29


LRESULT CALLBACK WindowProcedure(HWND,UINT,WPARAM,LPARAM);

void AddMenus(HWND);
void AddControls(HWND);                                            //function prototypes declared
void registerDialogClass(HINSTANCE);
void displayDialog(HWND, int);

HMENU hMenu;
HWND hSubmit;
HWND hRuns;
HWND hBalls;
HWND hWickets;
HWND hChoice;
HWND hstatus;
HWND hwicket; HWND hdot;                                          //declaring window handles
HWND hsingle; HWND hwide; HWND hnob; HWND hrunout;                //handles act as IDs for the windows
HWND hdouble; HWND hwide2; HWND hnob2; HWND hrunout2;             //(each element is defined as a window in the win32 api)
HWND htriple; HWND hwide3; HWND hnob3; HWND hrunout3;
HWND hfour; HWND hwide4; HWND hnob4; HWND hrunout4;
HWND hwide5; HWND hnob5;
HWND hsix;
HWND hwide7; HWND hnob7;
HWND hreason;


int run = 0;
int over = 0;                     //global variables to be used
int ball = 0;
int wicket = 0;



int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow)
{
    WNDCLASSW wc = {0};

    wc.hbrBackground =  (HBRUSH)COLOR_WINDOW ;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW) ;
    wc.hInstance = hInst;
    wc.lpszClassName = L"myWindowClass";                //defining main window template
    wc.lpfnWndProc = WindowProcedure;

    if(!RegisterClassW(&wc))
        return -1;

    registerDialogClass(hInst);

    CreateWindowW(L"myWindowClass",L"FP 2023 PBL",WS_OVERLAPPEDWINDOW | WS_VISIBLE,100,100,500,500
                  ,NULL,NULL,NULL,NULL);

    MSG msg = {0};

    while( GetMessage(&msg,NULL,NULL,NULL))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProcedure(HWND hWnd,UINT msg,WPARAM wp,LPARAM lp)         //handles all messages from the main parent window
{

    switch( msg)
    {
    case WM_COMMAND:

        switch(wp)
        {
        case FILE_MENU_EXIT:
            {int _val = MessageBoxW(hWnd,L"Are you sure?",L"Wait",MB_YESNO);
            if(_val==IDYES)
            {
                DestroyWindow(hWnd);
            }
            break;}
        case HELP:
            MessageBoxW(hWnd,L"This program was written for the Fundamentals of Programming subject's Project Based Learning assignment.",
                        L"Info",MB_HELP);
            break;
        case _SUBMIT:
            {
                wchar_t runs[5];
            GetWindowTextW(hSubmit,runs,sizeof(runs));           //converting string user input to integer for further processing
            int val = _wtoi(runs);
            switch(val)
            {
            default:
                displayDialog(hWnd,val);                         // particular dialog box for particular runs
                break;
            }
            break;
            }
        }
        break;
    case WM_CREATE:
        AddMenus(hWnd);
        AddControls(hWnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProcW(hWnd,msg,wp,lp);
    }
}

void AddMenus(HWND hWnd)                          //adds menu items
{
    HMENU hMenu = CreateMenu();
    HMENU hFileMenu = CreateMenu();
    AppendMenu(hFileMenu,MF_STRING,FILE_MENU_EXIT,"Exit");

    AppendMenu(hMenu,MF_POPUP,(UINT_PTR)hFileMenu,"File");
    AppendMenu(hMenu,MF_STRING,HELP,"Help");

    SetMenu(hWnd,hMenu);
}

void AddControls(HWND hWnd)                          //adds the initial windows to the parent window
{
    CreateWindowW(L"static",L"Enter Runs scored :",WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER,200,100,100,50,hWnd,NULL,NULL,NULL);
    hSubmit = CreateWindowW(L"edit",L"...",WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL | ES_NUMBER, 200,152,100,50,
                            hWnd,NULL,NULL,NULL);

    hstatus = CreateWindowW(L"static",L"",WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER,150,35,200,50,hWnd,NULL,NULL,NULL);
    CreateWindowW(L"static",L"Runs :",WS_VISIBLE | WS_CHILD | SS_CENTER,200,300,50,50,hWnd,NULL,NULL,NULL);
    hRuns = CreateWindowW(L"static",L"...",WS_VISIBLE | WS_CHILD | SS_CENTER,252,300,50,50,hWnd,NULL,NULL,NULL);
    CreateWindowW(L"static",L"Balls :",WS_VISIBLE | WS_CHILD | SS_CENTER,200,340,50,50,hWnd,NULL,NULL,NULL);
    hBalls = CreateWindowW(L"static",L"...",WS_VISIBLE | WS_CHILD | SS_CENTER,252,340,50,50,hWnd,NULL,NULL,NULL);
    CreateWindowW(L"Button",L"Submit runs",WS_VISIBLE | WS_CHILD,200,250,100,45,hWnd,(HMENU)_SUBMIT,NULL,NULL);
    CreateWindowW(L"static",L"Wickets :",WS_VISIBLE | WS_CHILD | SS_CENTER,200,380,60,50,hWnd,NULL,NULL,NULL);
    hWickets = CreateWindowW(L"static",L"...",WS_VISIBLE | WS_CHILD | SS_CENTER,252,380,50,50,hWnd,NULL,NULL,NULL);

}

LRESULT CALLBACK DialogProcedure(HWND hWnd,UINT msg, WPARAM wp, LPARAM lp )     //handles all messages from the dialog box
{
    switch(msg)
    {
    case WM_COMMAND:
        switch(wp)
        {
        case _WICKET:
            wicket += 1;
            ball += 1;
            break;
        case _DOT:
            ball += 1;
            break;
        case _SINGLE:
            run += 1;                                          //all SUBMIT cases from dialog
            ball += 1;                                         //should also add SUBMIT action to update display
            break;                                             //issue: user can select multiple radio buttons at once
        case _WIDE:
            run += 1;
            break;
        case _NOB:
            run += 1;
            ball -= 1;
            break;
        case _RO:
            run += 1;
            ball += 1;
            wicket -= 1;
            break;
        case _DOUBLE:
            run += 2;
            ball += 1;
            break;
        case _WIDE2:
            run += 2;
            break;
        case _NOB2:
            run += 2;
            ball -= 1;
            break;
        case _RO2:
            run += 2;
            ball += 1;
            wicket -= 1;
            break;
        case _TRIPLE:
            run += 3;
            ball += 1;
            break;
        case _WIDE3:
            run += 3;
            break;
        case _NOB3:
            run += 3;
            ball -= 1;
            break;
        case _RO3:
            run += 3;
            ball += 1;
            wicket += 1;
            break;
        case _FOUR:
            run += 4;
            ball += 1;
            break;
        case _WIDE4:
            run += 4;
            break;
        case _NOB4:
            run += 4;
            ball -= 1;
            break;
        case _RO4:
            run += 4;
            ball += 1;
            wicket += 1;
            break;
        case _WIDE5:
            run += 5;
            break;
        case _NOB5:
            run += 5;
            ball -= 1;
            break;
        case _SIX:
            run += 6;
            ball += 1;
            break;
        case _WIDE7:
            run += 7;
            break;
        case _NOB7:
            run += 7;
            ball -= 1;
            break;
        case _GIVECH:
            DestroyWindow(hWnd);
            wstring wideString1 = to_wstring(run);                  //conversion code for runs to be displayed
            const wchar_t* rundisplay = wideString1.c_str();      //should also add similar code for the other displays
            SetWindowTextW(hRuns,rundisplay);

            wstring wideString2 = to_wstring(ball);
            const wchar_t* balldisplay = wideString2.c_str();
            SetWindowTextW(hBalls,balldisplay);

            wstring wideString3 = to_wstring(wicket);
            const wchar_t* wicketdisplay = wideString3.c_str();
            SetWindowTextW(hWickets,wicketdisplay);

            if(ball == 6){
                over += 1;
                ball = 0;
            }

            if(wicket == 10){
                SetWindowTextW(hstatus, L"Innings Ended");
            }

            if(over == 50){
                SetWindowTextW(hstatus, L"Innings Ended");
            }

            break;
        }
        break;
    case WM_CLOSE:
        DestroyWindow(hWnd);
        break;
    default:
        return DefWindowProc(hWnd,msg,wp,lp);
        break;
    }
}

void registerDialogClass(HINSTANCE hInst)
{
    WNDCLASSW dialog = {0};

    dialog.hbrBackground =  (HBRUSH)COLOR_WINDOW ;
    dialog.hCursor = LoadCursor(NULL, IDC_CROSS) ;
    dialog.hInstance = hInst;                                      //register the dialog box template
    dialog.lpszClassName = L"myDialogClass";
    dialog.lpfnWndProc = DialogProcedure;

    RegisterClassW(&dialog);
}

void displayDialog(HWND hWnd, int runval)                          //function to display the right dialog box for the right user input
{
    HWND hDlg = CreateWindowW(L"myDialogClass",L"Dialog",WS_VISIBLE | WS_OVERLAPPEDWINDOW,400,400,300,300,hWnd,NULL,NULL,NULL);

    switch(runval)
    {
    case 0:
        hwicket = CreateWindowW(L"BUTTON",L"Wicket",WS_VISIBLE | WS_CHILD | WS_GROUP | BS_AUTORADIOBUTTON,100,10,100,10,hDlg,(HMENU)_WICKET,NULL,NULL);
        hdot = CreateWindowW(L"BUTTON",L"Dot Ball",WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,100,25,100,10,hDlg,(HMENU)_DOT,NULL,NULL);
        break;
    case 1:
        hsingle = CreateWindowW(L"BUTTON",L"Single",WS_VISIBLE | WS_CHILD | WS_GROUP | BS_AUTORADIOBUTTON,100,10,100,10,hDlg,(HMENU)_SINGLE,NULL,NULL);
        hwide = CreateWindowW(L"BUTTON",L"Wide",WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,100,25,100,10,hDlg,(HMENU)_WIDE,NULL,NULL);
        hnob = CreateWindowW(L"BUTTON",L"No Ball",WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,100,40,100,10,hDlg,(HMENU)_NOB,NULL,NULL);
        hrunout = CreateWindowW(L"BUTTON",L"Run Out",WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,100,55,100,10,hDlg,(HMENU)_RO,NULL,NULL);
        break;
    case 2:
        hdouble = CreateWindowW(L"BUTTON",L"Double",WS_VISIBLE | WS_CHILD | WS_GROUP | BS_AUTORADIOBUTTON,100,10,100,10,hDlg,(HMENU)_DOUBLE,NULL,NULL);
        hwide2 = CreateWindowW(L"BUTTON",L"Wide ball",WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,100,25,100,10,hDlg,(HMENU)_WIDE2,NULL,NULL);
        hnob2 = CreateWindowW(L"BUTTON",L"No ball",WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,100,40,100,10,hDlg,(HMENU)_NOB2,NULL,NULL);
        hrunout2 = CreateWindowW(L"BUTTON",L"Run Out",WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,100,55,100,10,hDlg,(HMENU)_RO2,NULL,NULL);
        break;
    case 3:
        htriple = CreateWindowW(L"BUTTON",L"Triple",WS_VISIBLE | WS_CHILD | WS_GROUP | BS_AUTORADIOBUTTON,100,10,100,10,hDlg,(HMENU)_TRIPLE,NULL,NULL);
        hwide3 = CreateWindowW(L"BUTTON",L"Wide ball",WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,100,25,100,10,hDlg,(HMENU)_WIDE3,NULL,NULL);
        hnob3 = CreateWindowW(L"BUTTON",L"No ball",WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,100,40,100,10,hDlg,(HMENU)_NOB3,NULL,NULL);
        hrunout3 = CreateWindowW(L"BUTTON",L"Run Out",WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,100,55,100,10,hDlg,(HMENU)_RO3,NULL,NULL);
        break;
    case 4:
        hfour = CreateWindowW(L"BUTTON",L"Four",WS_VISIBLE | WS_CHILD | WS_GROUP | BS_AUTORADIOBUTTON,100,10,100,10,hDlg,(HMENU)_FOUR,NULL,NULL);
        hwide4 = CreateWindowW(L"BUTTON",L"Wide ball",WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,100,25,100,10,hDlg,(HMENU)_WIDE4,NULL,NULL);
        hnob4 = CreateWindowW(L"BUTTON",L"No ball",WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,100,40,100,10,hDlg,(HMENU)_NOB4,NULL,NULL);
        hrunout4 = CreateWindowW(L"BUTTON",L"Run Out",WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,100,55,100,10,hDlg,(HMENU)_RO4,NULL,NULL);
        break;
    case 5:
        hwide5 = CreateWindowW(L"BUTTON",L"Wide ball",WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,100,25,100,10,hDlg,(HMENU)_WIDE5,NULL,NULL);
        hnob5 = CreateWindowW(L"BUTTON",L"No ball",WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,100,40,100,10,hDlg,(HMENU)_NOB5,NULL,NULL);
        break;
    case 6:
        hsix = CreateWindowW(L"BUTTON",L"Sixer",WS_VISIBLE | WS_CHILD | WS_GROUP | BS_AUTORADIOBUTTON,100,10,100,10,hDlg,(HMENU)_SIX,NULL,NULL);
        break;
    case 7:
        hwide7 = CreateWindowW(L"BUTTON",L"Wide ball",WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,100,25,100,10,hDlg,(HMENU)_WIDE7,NULL,NULL);
        hnob7 = CreateWindowW(L"BUTTON",L"No ball",WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,100,40,100,10,hDlg,(HMENU)_NOB7,NULL,NULL);
        break;
    default:
        hreason = CreateWindowW(L"static",L"Be reasonable!",WS_VISIBLE | WS_CHILD | SS_CENTER,90,30,80,50,hDlg,NULL,NULL,NULL);
        break;
    }

    CreateWindowW(L"Button",L"SUBMIT",WS_VISIBLE | WS_CHILD,20,180,100,40,hDlg, (HMENU)_GIVECH,NULL,NULL);

}
