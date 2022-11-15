// Client.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//
#include "pch.h"
#include "framework.h"
#include "Client.h"
#include "CEngine.h"

#define MAX_LOADSTRING 100

// 전역 변수:

//struct HINSTANCE__
//{
//    int unused;
//};
//
//typedef HINSTANCE__* HINSTANCE;

//App Title
const wchar_t* g_pTitle = L"MyGame";

HINSTANCE hInst;   // 현재 인스턴스입니다.
HWND g_hWnd = nullptr;
HWND g_hMapDlg = nullptr;

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT __stdcall    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR __stdcall    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    // 메모리 릭 체크
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    // 메모리 릭이 난 메모리 주소를 넣어준다 쓰고 나서 다시 주석 걸자
    //_CrtSetBreakAlloc(70974);
     
    // 윈도우, DC, Brush, Pen, AccelTable 등등 
    // Handle 로 다루는 오브젝트은 Kernel Object(OS가 관리하는 오브젝트)
   
    // 윈도우 설정
    MyRegisterClass(hInstance);

    // 윈도우 생성
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    // 엔진 초기화
    CEngine::GetInst()->Init(g_hWnd, 1020, 720);

    // 단축키 테이블 정보를 가져옴
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CLIENT));

    MSG msg = {};

    // 윈도우에 타이머 설정 ==> WM_TIMER 메세지 발생
    // SetTimer(g_hWnd, 100, 1000, nullptr);

    // GetMessage : 메시지 큐에서 메시지를 꺼내옴 - 느리고 비효율적이어서 게임 구현에는 적합하지 않음
    // 리턴값 bool이 false인 경우 프로그램이 종료됨
    // 꺼내온 message가 WM_QUIT 이면 GetMessage는 false를 반환한다

    // PeekMessage : Peek(훔쳐보다, 흘깃 보다)
    // 메세지 큐에 메세지가 있던 없던 무조건 함수가 반환된다.
    // PM_REMOVE 옵션과 조합할 경우, 메세지가 있으면 메세지 큐에서 메시지를 꺼내온다 (GetMessage와 동일해짐)
    // 리턴값 BOOL 이 true인 경우 메세지를 꺼냈다, false인 경우 메세지가 없었다
    while (true) 
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (WM_QUIT == msg.message)
                break;

            // 이쪽 코드는 건들지 않는다
            // 단축키 조합 확인
            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
            {
                TranslateMessage(&msg); // 분석
                DispatchMessage(&msg);  // 처리
            }
        }
        else
        {
            // Game Run
            CEngine::GetInst()->Progress();
        }
    }

    // 타이머 해제
    // KillTimer(g_hWnd, 100);

    return (int) msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex = {};

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.lpszClassName  = L"MySetting";
    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CLIENT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = nullptr; //MAKEINTRESOURCE(IDC_CLIENT);
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   g_hWnd = CreateWindowW(L"MySetting", g_pTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!g_hWnd)
   {
      return FALSE;
   }

   ShowWindow(g_hWnd, nCmdShow);
   UpdateWindow(g_hWnd);

   return TRUE;
}

INT_PTR CALLBACK TileCount(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

INT_PTR CALLBACK LevelEdit(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

INT_PTR CALLBACK AnimCreate(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

INT_PTR CALLBACK AnimEdit(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

// 메인 윈도우의 메세지 처리 함수
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            case CHANGE_TILECOUNT:
            {
                DialogBox(hInst, MAKEINTRESOURCE(IDD_TILECOUNT), hWnd, TileCount);
            }
                break;
            case EDIT_MAP:
            {
                if (!IsWindow(g_hMapDlg))
                {
                    g_hMapDlg = CreateDialog(hInst, MAKEINTRESOURCE(IDD_EDITMAP), hWnd, LevelEdit);
                    ShowWindow(g_hMapDlg, SW_SHOW);
                }
            }
                break;
            case CREATE_ANIM:
            {
                DialogBox(hInst, MAKEINTRESOURCE(IDD_CREATEANIM), hWnd, AnimCreate);
            }
                break;
            case EDIT_ANIM:
            {
                if (!IsWindow(g_hMapDlg))
                {
                    g_hMapDlg = CreateDialog(hInst, MAKEINTRESOURCE(IDD_EDITANIM), hWnd, AnimEdit);
                    ShowWindow(g_hMapDlg, SW_SHOW);
                }
            }
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
        // WM_PAINT
        // 윈도우에 Rendering이 다시 발생해야 할 때 발생 - 판단은 운영체제의 몫
        // 해당 윈도우에 무효화 영역이 생겼을 때
    case WM_PAINT:
        {
            PAINTSTRUCT ps;

            // Handle Device Context(장치 구문 핸들)
            // Rendering에 필요한 데이터 DC
            HDC hdc = BeginPaint(hWnd, &ps);

            // 그리기 종료
            EndPaint(hWnd, &ps);
        }
        break;
     // 왼쪽 버튼 클릭 확인
    case WM_LBUTTONDOWN:
        //PostQuitMessage(0);
        break;
    case WM_DESTROY:
        PostQuitMessage(0); // 윈도우 종료 버튼
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
