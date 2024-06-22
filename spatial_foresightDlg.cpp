
// spatial_foresightDlg.cpp: 实现文件
//

#include "pch.h"
#include "afxdialogex.h"
#include "framework.h"
#include "spatial_foresight.h"
#include "spatial_foresightDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CspatialforesightDlg 对话框



CspatialforesightDlg::CspatialforesightDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SPATIAL_FORESIGHT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CspatialforesightDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, Listctl);
}

BEGIN_MESSAGE_MAP(CspatialforesightDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_32771, &CspatialforesightDlg::FileRead)
	ON_COMMAND(ID_32772, &CspatialforesightDlg::ExitFunc)
	ON_COMMAND(ID_32774, &CspatialforesightDlg::Calc_Auxiliary_Coordinates)
	ON_COMMAND(ID_32773, &CspatialforesightDlg::Calc_Project_Fac)
	ON_COMMAND(ID_32775, &CspatialforesightDlg::Calc_Photo_Coor)
	ON_COMMAND(ID_32776, &CspatialforesightDlg::TestCalc)
	ON_COMMAND(ID_32777, &CspatialforesightDlg::TestDataRead)
	ON_COMMAND(ID_32778, &CspatialforesightDlg::AboutFunc)
END_MESSAGE_MAP()


// CspatialforesightDlg 消息处理程序

BOOL CspatialforesightDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	menu.LoadMenuW(IDR_MENU1);
	SetMenu(&menu);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CspatialforesightDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CspatialforesightDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CspatialforesightDlg::FileRead()
{
	// TODO: 在此添加命令处理程序代码
	CFileDialog File(TRUE);
	File.DoModal();
	auto path = File.GetPathName();
	ifstream fin;
	fin.open(path);
	string line, word;
	stringstream tmp_line;
	if (fin.is_open())
	{
		data_vec.clear();
		Listctl.DeleteAllItems();
		auto cols = Listctl.GetHeaderCtrl()->GetItemCount();
		for (auto i = 0; i < cols; i++)
		{
			Listctl.DeleteColumn(0);
		}
		CString txt[9] = {
			TEXT("像片主距f"), TEXT("像点坐标x"), TEXT("像点坐标y"),
			TEXT("X_s"), TEXT("Y_s"), TEXT("Z_s"),
			TEXT("偏角"), TEXT("倾角"), TEXT("旋角")
		};
		CString X_s, Y_s, Z_s, Phi, Omega, Kaba, f, x, y;
		int i = 0;
		while (getline(fin, line, '\n'))
		{
			if (i == 0)
			{
				tmp_data.X_s = atof(line.c_str());
				i++;
				continue;
			}
			if (i == 1)
			{
				tmp_data.Y_s = atof(line.c_str());
				i++;
				continue;
			}
			if (i == 2)
			{
				tmp_data.Z_s = atof(line.c_str());
				i++;
				continue;
			}
			if (i == 3)
			{
				tmp_data.Phi = atof(line.c_str());
				i++;
				continue;
			}
			if (i == 4)
			{
				tmp_data.Omega = atof(line.c_str());
				i++;
				continue;
			}
			if (i == 5)
			{
				tmp_data.Kaba = atof(line.c_str());
				i++;
				continue;
			}
			if (i == 6)
			{
				tmp_data.x = atof(line.c_str());
				i++;
				continue;
			}
			if (i == 7)
			{
				tmp_data.y = atof(line.c_str());
				i++;
				continue;
			}
			if (i == 8)
			{
				tmp_data.f = atof(line.c_str());
				data_vec.push_back(tmp_data);
				i = 0;
				continue;
			}
		}
		for (auto i = 0; i < 9; i++)
		{
			Listctl.InsertColumn(i, txt[i], LVCFMT_CENTER, 100);
		}
		for (auto i = 0; i < data_vec.size(); i++)
		{
			f.Format(_T("%.8f"), data_vec[i].f);
			x.Format(_T("%.8f"), data_vec[i].x);
			y.Format(_T("%.8f"), data_vec[i].y);
			X_s.Format(_T("%.8f"), data_vec[i].X_s);
			Y_s.Format(_T("%.8f"), data_vec[i].Y_s);
			Z_s.Format(_T("%.8f"), data_vec[i].Z_s);
			Phi.Format(_T("%.8f"), data_vec[i].Phi);
			Omega.Format(_T("%.8f"), data_vec[i].Omega);
			Kaba.Format(_T("%.8f"), data_vec[i].Kaba);
			Listctl.InsertItem(i, f);
			Listctl.SetItemText(i, 1, x);
			Listctl.SetItemText(i, 2, y);
			Listctl.SetItemText(i, 3, X_s);
			Listctl.SetItemText(i, 4, Y_s);
			Listctl.SetItemText(i, 5, Z_s);
			Listctl.SetItemText(i, 6, Phi);
			Listctl.SetItemText(i, 7, Omega);
			Listctl.SetItemText(i, 8, Kaba);
		}
		Listctl.SetExtendedStyle(Listctl.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
		MessageBox(TEXT("文件已导入！"));
		fin.close();
	}
	else
	{
		MessageBox(TEXT("No File Selected!"));
	}
}


void CspatialforesightDlg::ExitFunc()
{
	// TODO: 在此添加命令处理程序代码
	OnCancel();
}

vector<vector<double>> CspatialforesightDlg::Trans_calc(double phi, double omega, double kaba)
{
	vector<double> tmp_vec;
	Trans_mat.clear();
	tmp_vec.push_back(cos(phi) * cos(kaba) - cos(phi) * sin(omega) * sin(kaba));
	tmp_vec.push_back((-cos(phi)) * sin(kaba) - sin(phi) * sin(omega) * sin(kaba));
	tmp_vec.push_back((-sin(phi)) * cos(omega));
	Trans_mat.push_back(tmp_vec);
	tmp_vec.clear();
	tmp_vec.push_back(cos(omega) * sin(kaba));
	tmp_vec.push_back(cos(omega) * cos(kaba));
	tmp_vec.push_back(-sin(omega));
	Trans_mat.push_back(tmp_vec);
	tmp_vec.clear();
	tmp_vec.push_back(sin(phi) * cos(kaba) + cos(phi) * sin(omega) * sin(kaba));
	tmp_vec.push_back((-sin(omega)) * cos(kaba) + cos(phi) * sin(omega) * sin(kaba));
	tmp_vec.push_back(cos(phi) * cos(omega));
	Trans_mat.push_back(tmp_vec);
	tmp_vec.clear();
	return Trans_mat;
}

void CspatialforesightDlg::Calc_Auxiliary_Coordinates()
{
	// TODO: 在此添加命令处理程序代码
	CFileDialog File(FALSE);
	File.DoModal();
	auto path = File.GetPathName();
	ofstream fout;
	fout.open(path);
	if (fout.is_open())
	{
		Trans_Mat_vec.clear();
		Trans_mat.clear();
		aux_data_vec.clear();
		fout << "像空间辅助坐标：\n";
		for (auto i = 0; i < data_vec.size(); i++)
		{
			fout << "像片 " << i + 1 << "\tu\tv\tw\n";
			auto mat = Trans_calc(data_vec[i].Phi, data_vec[i].Omega, data_vec[i].Kaba);
			Trans_Mat_vec.push_back(mat);
			for (auto j = 0; j < 3; j++)
			{
				if (j == 0)
				{
					auto u = mat[j][0] * data_vec[i].x + mat[j][1] * data_vec[i].y + mat[j][2] * (-data_vec[i].f);
					fout << u << '\t';
					tmp_aux_coor.u = u;
				}
				if (j == 1)
				{
					auto v = mat[j][0] * data_vec[i].x + mat[j][1] * data_vec[i].y + mat[j][2] * (-data_vec[i].f);
					fout << v << '\t';
					tmp_aux_coor.v = v;
				}
				if (j == 2)
				{
					auto w = mat[j][0] * data_vec[i].x + mat[j][1] * data_vec[i].y + mat[j][2] * (-data_vec[i].f);
					fout << w << '\n';
					tmp_aux_coor.w = w;
					aux_data_vec.push_back(tmp_aux_coor);
				}
			}
		}
		MessageBox(TEXT("Done!"));
		fout.close();
	}
	else
	{
		MessageBox(TEXT("No File!"));
	}
}


void CspatialforesightDlg::Calc_Project_Fac()
{
	// TODO: 在此添加命令处理程序代码
	if (data_vec.size() != 0 && aux_data_vec.size() != 0)
	{
		auto B_u = data_vec[1].X_s - data_vec[0].X_s;
		auto B_v = data_vec[1].Y_s - data_vec[0].Y_s;
		auto B_w = data_vec[1].Z_s - data_vec[0].Z_s;
		N1 = (B_u * aux_data_vec[1].w - B_w * aux_data_vec[1].u) / (aux_data_vec[0].u * aux_data_vec[1].w - aux_data_vec[1].u * aux_data_vec[0].w);
		N2 = (B_u * aux_data_vec[0].w - B_w * aux_data_vec[0].u) / (aux_data_vec[0].u * aux_data_vec[1].w - aux_data_vec[1].u * aux_data_vec[0].w);
		MessageBox(TEXT("投影系数计算完成"));
	}
	else
	{
		MessageBox(TEXT("未读取文件"));
	}
}

void CspatialforesightDlg::Calc_Photo_Coor()
{
	// TODO: 在此添加命令处理程序代码
	CFileDialog File(FALSE);
	File.DoModal();
	auto path = File.GetPathName();
	ofstream fout;
	fout.open(path);
	if (fout.is_open())
	{
		fout << "地面点坐标：\t" << "X\t" << "Y\t" << "Z\n";
		fout.setf(ios::fixed);
		fout.precision(3);
		fout << '\t' << data_vec[0].X_s + N1 * aux_data_vec[0].u;
		fout << '\t' << 0.5 * ((data_vec[0].Y_s + N1 * aux_data_vec[0].v) + (data_vec[1].Y_s + N2 * aux_data_vec[1].v));
		fout << '\t' << data_vec[0].Z_s + N1 * aux_data_vec[0].w;
		MessageBox(TEXT("Done!"));
	}
	else
	{
		MessageBox(TEXT("No File!"));
	}
}


void CspatialforesightDlg::TestCalc()
{
	// TODO: 在此添加命令处理程序代码
	CFileDialog File(FALSE);
	File.DoModal();
	auto path = File.GetPathName();
	ofstream fout(path);
	if (fout.is_open())
	{
		fout.setf(ios::fixed);
		fout.precision(3);
		aux_data_vec.clear();
		double u1 = 0, u2 = 0, v1 = 0, v2 = 0, w1 = 0, w2 = 0;
		auto& mat1 = Trans_Mat_vec[0];
		auto& mat2 = Trans_Mat_vec[1];
		for (auto i = 0; i < photoCoor_vec.size(); i++)
		{
			for (auto j = 0; j < 3; j++)
			{
				if (j == 0)
				{
					u1 = mat1[j][0] * photoCoor_vec[i].x1 + mat1[j][1] * photoCoor_vec[i].y1 + mat1[j][2] * (-data_vec[0].f);
					u2 = mat2[j][0] * photoCoor_vec[i].x2 + mat2[j][1] * photoCoor_vec[i].y2 + mat2[j][2] * (-data_vec[1].f);
					//fout << u << '\t';
					continue;
				}
				if (j == 1)
				{
					v1 = mat1[j][0] * photoCoor_vec[i].x1 + mat1[j][1] * photoCoor_vec[i].y1 + mat1[j][2] * (-data_vec[0].f);
					v2 = mat2[j][0] * photoCoor_vec[i].x2 + mat2[j][1] * photoCoor_vec[i].y2 + mat2[j][2] * (-data_vec[1].f);
					//fout << v << '\t';
					continue;
				}
				if (j == 2)
				{
					w1 = mat1[j][0] * photoCoor_vec[i].x1 + mat1[j][1] * photoCoor_vec[i].y1 + mat1[j][2] * (-data_vec[0].f);
					w2 = mat2[j][0] * photoCoor_vec[i].x2 + mat2[j][1] * photoCoor_vec[i].y2 + mat2[j][2] * (-data_vec[1].f);
					//fout << w << '\n';
					tmp_aux_coor.u = u1;
					tmp_aux_coor.v = v1;
					tmp_aux_coor.w = w1;
					aux_data_vec.push_back(tmp_aux_coor);
					tmp_aux_coor.u = u2;
					tmp_aux_coor.v = v2;
					tmp_aux_coor.w = w2;
					aux_data_vec.push_back(tmp_aux_coor);
					break;
				}
			}
		}
		for (auto i = 0; i < aux_data_vec.size() - 1; i += 2)
		{
			fout << "地面点坐标：\t" << "X\t" << "Y\t" << "Z\n";
			fout << '\t' << data_vec[0].X_s + N1 * aux_data_vec[i].u;
			fout << '\t' << 0.5 * ((data_vec[0].Y_s + N1 * aux_data_vec[i].v) + (data_vec[1].Y_s + N2 * aux_data_vec[i + 1].v));
			fout << '\t' << data_vec[0].Z_s + N1 * aux_data_vec[i].w;
			fout << '\n';
		}
		fout.close();
		MessageBox(TEXT("Done"));
	}
	else
	{
		MessageBox(TEXT("未选择文件"));
	}
}


void CspatialforesightDlg::TestDataRead()
{
	// TODO: 在此添加命令处理程序代码
	stringstream tmp_line;
	string line, word; int index = 0;
	CFileDialog File(TRUE);
	File.DoModal();
	auto path = File.GetPathName();
	ifstream fin(path);
	if (fin.is_open())
	{
		photoCoor_vec.clear();
		Listctl.DeleteAllItems();
		auto cols = Listctl.GetHeaderCtrl()->GetItemCount();
		for (auto i = 0; i < cols; i++)
		{
			Listctl.DeleteColumn(0);
		}
		CString txt[4] = {
			TEXT("X1"), TEXT("Y1"), TEXT("X2"), TEXT("Y2")
		};
		for (auto i = 0; i < 4; i++)
		{
			Listctl.InsertColumn(i, txt[i], LVCFMT_CENTER, 80);
		}
		while (getline(fin, line, '\n'))
		{
			tmp_line.str(line);
			while (getline(tmp_line, word, ','))
			{
				if (index == 0)
				{
					tmp_photo_coor.x1 = atof(word.c_str());
					index++;
					continue;
				}
				if (index == 1)
				{
					tmp_photo_coor.y1 = atof(word.c_str());
					index++;
					continue;
				}
				if (index == 2)
				{
					tmp_photo_coor.x2 = atof(word.c_str());
					index++;
					continue;
				}
				if (index == 3)
				{
					tmp_photo_coor.y2 = atof(word.c_str());
					photoCoor_vec.push_back(tmp_photo_coor);
					index = 0;
					break;
				}
			}
			tmp_line.clear();
		}
		CString txt1, txt2, txt3, txt4;
		for (auto i = 0; i < photoCoor_vec.size(); i++)
		{
			txt1.Format(_T("%.2f"), photoCoor_vec[i].x1);
			txt2.Format(_T("%.2f"), photoCoor_vec[i].y1);
			txt3.Format(_T("%.2f"), photoCoor_vec[i].x2);
			txt4.Format(_T("%.2f"), photoCoor_vec[i].y2);
			Listctl.InsertItem(i, txt1);
			Listctl.SetItemText(i, 1, txt2);
			Listctl.SetItemText(i, 2, txt3);
			Listctl.SetItemText(i, 3, txt4);
		}
		Listctl.SetExtendedStyle(Listctl.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
		fin.close();
		MessageBox(TEXT("文件已读入"));
	}
	else
	{
		MessageBox(TEXT("未选择文件"));
	}
}


void CspatialforesightDlg::AboutFunc()
{
	// TODO: 在此添加命令处理程序代码
	dlg.DoModal();
}
