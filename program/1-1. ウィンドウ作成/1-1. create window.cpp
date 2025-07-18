//	ウィンドウのAPIを操作するのに必要
//	createWindowEx、ResisterClassなども入っている。
#include<Windows.h>


//	LRESULT :処理の結果の型（windows）が扱う整数型
//	CALLBACK :呼び出し規約（stdcall）OSから呼ばれる関数（他から呼んではいけないから）

//	HWND :ウィンドウハンドル
//	型：typedef void* HWMD (ポインタ的なモノ)
//	役割：OSが管理しているウィンドウ1つ1つに対して発行する識別子
//	描画などでも使用する

//	UINT :メッセージの種類の判定
//	型： unsigned int

//	WPARAM / LPARAM :OSが送ってくる補足情報
//	多くの場合: WPARAMにキーコード、LPARAMに座標などの追加情報が入る


//	PostQuitMessage(0)
//	メッセージループに終了を伝える関数
//	WM_QUITというメッセージを送ってくる
//	その後メッセージループの条件をfalseにして抜ける
//	０で正常終了　１で異常終了
//	winMainの戻り値やGetExitCodeProcess()で取得されてプログラムの終了を促す。


//	DefWindowProc(hwnd, uMsg, wParam, lparam)
//	デフォルトメッセージ処理をOSに任せるための関数
//	自分で処理をしなかったメッセージはこの関数に渡すのが基本ルール
//	送られてくるメッセージの例
//	WM_CLOSE	「×」ボタンが押された
//	WM_MOVE	ウィンドウが移動した
//	WM_GETMINMAXINFO	ウィンドウサイズ制限
//	WM_NCPAINT	枠やタイトルバーの描画など


//	WNDCLASS :OSに自分のウィンドウの仕様を教えるための登録処理
//	このテンプレートを使って実際のウィンドウを作る。
//	中身
//typedef struct _WNDCLASS {
//	UINT      style;         // スタイル（省略中）
//	WNDPROC   lpfnWndProc;   // メッセージ処理関数へのポインタ
//	int       cbClsExtra;    // 拡張データ（使わないなら0）
//	int       cbWndExtra;
//	HINSTANCE hInstance;     // アプリケーションのハンドル
//	HICON     hIcon;         // アイコン
//	HCURSOR   hCursor;       // カーソル
//	HBRUSH    hbrBackground; // 背景色
//	LPCWSTR   lpszMenuName;  // メニュー名（省略可）
//	LPCWSTR   lpszClassName; // クラス名
//} WNDCLASS;

//	Windowsのウィンドウへのイベント(メッセージ)を処理する関数
//	例えば「閉じるボタンが押された」などのイベントが通知される。(コールバック)
LRESULT CALLBACK windowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lparam) {

	switch (uMsg){
		//	アプリの終了状態
	case WM_DESTROY:	
		//	アプリの終了を通知する
		PostQuitMessage(0);
		return 0;

		//	他の通常メッセージはOSの標準処理に任せる
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lparam);
	}
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow) {
	//	ウィンドウクラスの作成（最初は全て0初期化）
	WNDCLASS wc = {};
	wc.lpfnWndProc = windowProc; //	メッセージ処理関数（さっき作った関数をメッセージ処理関数として登録する）
	wc.hInstance = hInstance;	//	アプリケーションのインスタンス（このウィンドウテンプレートを作ったアプリケーションをOSに伝えるためのアプリの識別ハンドル
	wc.lpszClassName = L"WindowClass";	//	クラス名（文字列はLプレフィックスを付けてワイド文字(UTF-16)で渡している）

	if (!RegisterClass(&wc)) {
		return 0;
	}

	
	//	登録済みのウィンドウクラスからウィンドウの実体を作成
	//	CreateWindowは、ウィンドウを作るメイン的な関数でこの関数を呼び出して実体を作成しないと何もウィンドウに表示できない
	HWND hwnd = CreateWindowEx(
		0,											//	拡張ウィンドウスタイル（拡張を導入するときしか使わない）
		wc.lpszClassName,							//	Windowクラスで登録した名前をここに入れる。（一致しないと使えない）
		L"My First Window",							//	タイトルバーに表示される文字列（ここを変更するとウィンドウの名前も変更できる。dxlibは多分この機能）
		WS_OVERLAPPEDWINDOW,						//	標準的なウィンドウのスタイル（最小化、最大化、閉じるボタン付き。たまに最小化できないやつはこれのせい）
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,		//	ウィンドウの初期座標を指定している。別に適当でいいのでOSに任せる。	//	ウィンドウの枠までを含めたサイズの指定
		nullptr, nullptr, hInstance, nullptr		//	親ウィンドウの登録(子じゃなければnullptr) // メニューのハンドル(今回はメニューを付けないので) 
	);												//	WinMainにわたってくるアプリケーションのインスタンスハンドルを渡す。ここを間違えるとなにも作れない // ウィンドウ生成時に初期データを渡せる。(使わないならnullptr)
}