
// MFCApplication3Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplication3.h"
#include "MFCApplication3Dlg.h"
#include "afxdialogex.h"
#include "DataBaseAccessor.h"
#include "CommonVariables.h"
#include "Singleton.h"
#include "MainXX.h"
#include "WebServiceClient.h"
#include "GetTinyXmlDocument.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication3Dlg �Ի���



CMFCApplication3Dlg::CMFCApplication3Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCApplication3Dlg::IDD, pParent)
	, m_EditPWDStr(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_ACCOUNT, m_EditAccount);
	DDX_Control(pDX, IDC_EDIT_PASSWORD, m_EditPwd);
	DDX_Text(pDX, IDC_EDIT_ACCOUNT, m_EditAccountStr);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_EditPWDStr);
	DDV_MaxChars(pDX, m_EditPWDStr, 20);
}

BEGIN_MESSAGE_MAP(CMFCApplication3Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCApplication3Dlg::OnBnClickedOk)
END_MESSAGE_MAP()

bool CMFCApplication3Dlg::m_bShutdownDialog = false;
CString CMFCApplication3Dlg::m_EditAccountStr = _T("");
std::mutex CMFCApplication3Dlg::m_mutex;
std::condition_variable CMFCApplication3Dlg::m_cv;
bool CMFCApplication3Dlg::m_ready = false;
bool CMFCApplication3Dlg::m_processed = false;
// CMFCApplication3Dlg ��Ϣ�������

BOOL CMFCApplication3Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMFCApplication3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMFCApplication3Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMFCApplication3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication3Dlg::OnBnClickedOk()
{
	//CString Account;
	//CString Password;
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	if (m_EditAccountStr == _T("") || m_EditPWDStr == _T(""))
	{
		AfxMessageBox(_T("�û��˺Ż�������Ϊ�գ�"));
		return;
	}
	DataBaseAccessor* dataBaseAccessor = DataBaseAccessor::GetInstance();
	//WebServiceClient* pWebClient = WebServiceClient::GetInstance();
	int ret = dataBaseAccessor->ConnectServer();
	if (ret == 0)
	{
		AfxMessageBox(_T("connect to server successfully\n"));
	}
	dataBaseAccessor->CreateReceiveMessageThread();
	Message message;
	message.Sequence = 1;
	message.sessionType = LOGIN;
	message.sessionChildType = CTS_LOGIN;
	
	message.messageData = CommonFunctions::GetInstance()->CStringToSTLstring(m_EditAccountStr + _T(",") + m_EditPWDStr);
	dataBaseAccessor->SendMessageStr(message.ToString());
	//string loginResult;
	//dataBaseAccessor->ReceiveMessage(loginResult);
	// Wait until main() sends data


	/*{
		std::lock_guard<std::mutex> lk(m_mutex);
		m_ready = true;
	}
	m_cv.notify_one();
	*/

	{
		std::unique_lock<std::mutex> lk(m_mutex);
		m_cv.wait(lk, []{return m_processed; });
	}

	if (m_bShutdownDialog)
	{
		CDialogEx::OnOK();
		UserLoginInfo* pInfo = new UserLoginInfo();
		pInfo->m_id = CommonFunctions::GetInstance()->CStringToSTLstring(m_EditAccountStr);
		MAINXX TQ_Main(pInfo);
		delete pInfo;
		TQ_Main.DoModal();
	}
	/*else
	{
		AfxMessageBox(_T("��¼��Ϣ���ԣ������������¼��Ϣ"));
	}*/
	//
}


void CMFCApplication3Dlg::DealWithReceiveMessageFunc(Message& receiveMsg)
{
	std::unique_lock<std::mutex> lk(m_mutex);
	//m_cv.wait(lk, []{return m_ready; });
	//string loginResult = pWebClient->SendAndReceiveMessage(message.ToString());
	if (receiveMsg.sessionType == LOGIN && receiveMsg.sessionChildType == STC_LOGIN_REPLY)
	{
		if (receiveMsg.messageData == "Success")
		{
			m_bShutdownDialog = true;

			m_processed = true;
			lk.unlock();
			m_cv.notify_one();
			//Sleep(2000);
		}
		else
		{
			vector<string> loginResultVect;
			CommonFunctions::GetInstance()->SplitString(receiveMsg.GetMessageDataToSTLString(), "#", loginResultVect);
			if (loginResultVect.size() >= 2)
			{
				AfxMessageBox(CString(loginResultVect[1].c_str()));
			}

		}
	}
	

}

