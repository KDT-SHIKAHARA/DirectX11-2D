//	�E�B���h�E��API�𑀍삷��̂ɕK�v
//	createWindowEx�AResisterClass�Ȃǂ������Ă���B
#include<Windows.h>


//	LRESULT :�����̌��ʂ̌^�iwindows�j�����������^
//	CALLBACK :�Ăяo���K��istdcall�jOS����Ă΂��֐��i������Ă�ł͂����Ȃ�����j

//	HWND :�E�B���h�E�n���h��
//	�^�Ftypedef void* HWMD (�|�C���^�I�ȃ��m)
//	�����FOS���Ǘ����Ă���E�B���h�E1��1�ɑ΂��Ĕ��s���鎯�ʎq
//	�`��Ȃǂł��g�p����

//	UINT :���b�Z�[�W�̎�ނ̔���
//	�^�F unsigned int

//	WPARAM / LPARAM :OS�������Ă���⑫���
//	�����̏ꍇ: WPARAM�ɃL�[�R�[�h�ALPARAM�ɍ��W�Ȃǂ̒ǉ���񂪓���


//	PostQuitMessage(0)
//	���b�Z�[�W���[�v�ɏI����`����֐�
//	WM_QUIT�Ƃ������b�Z�[�W�𑗂��Ă���
//	���̌チ�b�Z�[�W���[�v�̏�����false�ɂ��Ĕ�����
//	�O�Ő���I���@�P�ňُ�I��
//	winMain�̖߂�l��GetExitCodeProcess()�Ŏ擾����ăv���O�����̏I���𑣂��B


//	DefWindowProc(hwnd, uMsg, wParam, lparam)
//	�f�t�H���g���b�Z�[�W������OS�ɔC���邽�߂̊֐�
//	�����ŏ��������Ȃ��������b�Z�[�W�͂��̊֐��ɓn���̂���{���[��
//	�����Ă��郁�b�Z�[�W�̗�
//	WM_CLOSE	�u�~�v�{�^���������ꂽ
//	WM_MOVE	�E�B���h�E���ړ�����
//	WM_GETMINMAXINFO	�E�B���h�E�T�C�Y����
//	WM_NCPAINT	�g��^�C�g���o�[�̕`��Ȃ�


//	WNDCLASS :OS�Ɏ����̃E�B���h�E�̎d�l�������邽�߂̓o�^����
//	���̃e���v���[�g���g���Ď��ۂ̃E�B���h�E�����B
//	���g
//typedef struct _WNDCLASS {
//	UINT      style;         // �X�^�C���i�ȗ����j
//	WNDPROC   lpfnWndProc;   // ���b�Z�[�W�����֐��ւ̃|�C���^
//	int       cbClsExtra;    // �g���f�[�^�i�g��Ȃ��Ȃ�0�j
//	int       cbWndExtra;
//	HINSTANCE hInstance;     // �A�v���P�[�V�����̃n���h��
//	HICON     hIcon;         // �A�C�R��
//	HCURSOR   hCursor;       // �J�[�\��
//	HBRUSH    hbrBackground; // �w�i�F
//	LPCWSTR   lpszMenuName;  // ���j���[���i�ȗ��j
//	LPCWSTR   lpszClassName; // �N���X��
//} WNDCLASS;

//	Windows�̃E�B���h�E�ւ̃C�x���g(���b�Z�[�W)����������֐�
//	�Ⴆ�΁u����{�^���������ꂽ�v�Ȃǂ̃C�x���g���ʒm�����B(�R�[���o�b�N)
LRESULT CALLBACK windowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lparam) {

	switch (uMsg){
		//	�A�v���̏I�����
	case WM_DESTROY:	
		//	�A�v���̏I����ʒm����
		PostQuitMessage(0);
		return 0;

		//	���̒ʏ탁�b�Z�[�W��OS�̕W�������ɔC����
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lparam);
	}
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow) {
	//	�E�B���h�E�N���X�̍쐬�i�ŏ��͑S��0�������j
	WNDCLASS wc = {};
	wc.lpfnWndProc = windowProc; //	���b�Z�[�W�����֐��i������������֐������b�Z�[�W�����֐��Ƃ��ēo�^����j
	wc.hInstance = hInstance;	//	�A�v���P�[�V�����̃C���X�^���X�i���̃E�B���h�E�e���v���[�g��������A�v���P�[�V������OS�ɓ`���邽�߂̃A�v���̎��ʃn���h��
	wc.lpszClassName = L"WindowClass";	//	�N���X���i�������L�v���t�B�b�N�X��t���ă��C�h����(UTF-16)�œn���Ă���j

	if (!RegisterClass(&wc)) {
		return 0;
	}

	
	//	�o�^�ς݂̃E�B���h�E�N���X����E�B���h�E�̎��̂��쐬
	//	CreateWindow�́A�E�B���h�E����郁�C���I�Ȋ֐��ł��̊֐����Ăяo���Ď��̂��쐬���Ȃ��Ɖ����E�B���h�E�ɕ\���ł��Ȃ�
	HWND hwnd = CreateWindowEx(
		0,											//	�g���E�B���h�E�X�^�C���i�g���𓱓�����Ƃ������g��Ȃ��j
		wc.lpszClassName,							//	Window�N���X�œo�^�������O�������ɓ����B�i��v���Ȃ��Ǝg���Ȃ��j
		L"My First Window",							//	�^�C�g���o�[�ɕ\������镶����i������ύX����ƃE�B���h�E�̖��O���ύX�ł���Bdxlib�͑������̋@�\�j
		WS_OVERLAPPEDWINDOW,						//	�W���I�ȃE�B���h�E�̃X�^�C���i�ŏ����A�ő剻�A����{�^���t���B���܂ɍŏ����ł��Ȃ���͂���̂����j
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,		//	�E�B���h�E�̏������W���w�肵�Ă���B�ʂɓK���ł����̂�OS�ɔC����B	//	�E�B���h�E�̘g�܂ł��܂߂��T�C�Y�̎w��
		nullptr, nullptr, hInstance, nullptr		//	�e�E�B���h�E�̓o�^(�q����Ȃ����nullptr) // ���j���[�̃n���h��(����̓��j���[��t���Ȃ��̂�) 
	);												//	WinMain�ɂ킽���Ă���A�v���P�[�V�����̃C���X�^���X�n���h����n���B�������ԈႦ��ƂȂɂ����Ȃ� // �E�B���h�E�������ɏ����f�[�^��n����B(�g��Ȃ��Ȃ�nullptr)
}